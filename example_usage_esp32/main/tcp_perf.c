/* tcp_perf Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <string.h>
#include <sys/socket.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_log.h"


#include "tcp_perf.h"
#include "adc_collector.h"

#include "nn4mp/neural_network.c"
#include "nn4mp/neural_network_params.h"
#include "nn4mp/neural_network.h"

/* FreeRTOS event group to signal when we are connected to wifi */
EventGroupHandle_t tcp_event_group;

/*socket*/
static int server_socket = 0;
static struct sockaddr_in server_addr;
static struct sockaddr_in client_addr;
static unsigned int socklen = sizeof(client_addr);
static int connect_socket = 0;
bool g_rxtx_need_restart = false;

int g_total_data = 0;

#if EXAMPLE_ESP_TCP_PERF_TX && EXAMPLE_ESP_TCP_DELAY_INFO

int g_total_pack = 0;
int g_send_success = 0;
int g_send_fail = 0;
int g_delay_classify[5] = { 0 };

#endif /*EXAMPLE_ESP_TCP_PERF_TX && EXAMPLE_ESP_TCP_DELAY_INFO*/


static esp_err_t event_handler(void *ctx, system_event_t *event)
{
    switch (event->event_id) {
    case SYSTEM_EVENT_STA_START:
        esp_wifi_connect();
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        esp_wifi_connect();
        xEventGroupClearBits(tcp_event_group, WIFI_CONNECTED_BIT);
        break;
    case SYSTEM_EVENT_STA_CONNECTED:
        break;
    case SYSTEM_EVENT_STA_GOT_IP:
        ESP_LOGI(TAG, "got ip:%s\n",
                 ip4addr_ntoa(&event->event_info.got_ip.ip_info.ip));
        xEventGroupSetBits(tcp_event_group, WIFI_CONNECTED_BIT);
        break;
    case SYSTEM_EVENT_AP_STACONNECTED:
        ESP_LOGI(TAG, "station:"MACSTR" join,AID=%d\n",
                 MAC2STR(event->event_info.sta_connected.mac),
                 event->event_info.sta_connected.aid);
        xEventGroupSetBits(tcp_event_group, WIFI_CONNECTED_BIT);
        break;
    case SYSTEM_EVENT_AP_STADISCONNECTED:
        ESP_LOGI(TAG, "station:"MACSTR"leave,AID=%d\n",
                 MAC2STR(event->event_info.sta_disconnected.mac),
                 event->event_info.sta_disconnected.aid);
        xEventGroupClearBits(tcp_event_group, WIFI_CONNECTED_BIT);
        break;
    default:
        break;
    }
    return ESP_OK;
}

void feed_forward(volatile float ** window){

    struct Conv1D L1; 
    set_conv1D(&L1, WINDOW_SIZE, NUM_ADC, 4, 8); 
    fwd_conv1D(&L1, 4, 2, 8, W_0, b_0, window);

    struct Conv1D L2; 
    set_conv1D(&L2, 47, 8, 4, 8); 
    fwd_conv1D(&L2, 4, 8, 8, W_1, b_1, L1.h);

    struct Flatten2D1D FL; 
    flatten2D1D(&FL, 44, 8, L2.h);

    struct Dense D1; 
    set_dense(&D1, FL.output_size, 64, 'r');
    fwd_dense(&D1, D1.input_size, D1.output_size, W_2, b_2, FL.h);

    struct Dense D2; 
    set_dense(&D2, D1.output_size, 32, 'r');
    fwd_dense(&D2, D2.input_size, D2.output_size, W_3, b_3, D1.h);

    struct Dense D3; 
    set_dense(&D3, D2.output_size, 16, 'r');
    fwd_dense(&D3, D3.input_size, D3.output_size, W_4, b_4, D2.h);

    struct Dense D4; 
    set_dense(&D4, D3.output_size, 8, 'r');
    fwd_dense(&D4, D4.input_size, D4.output_size, W_5, b_5, D3.h);

    struct Dense D5; 
    set_dense(&D5, D4.output_size, 3, 'l');
    fwd_dense(&D5, D5.input_size, D5.output_size, W_6, b_6, D4.h);

    for (int i=0; i<NUM_OUTPUT; i++){
        output[i]= D5.h[i];
    }
}

//send data
void send_data(void *pvParameters)
{
    int len = 0;
    vTaskDelay(100 / portTICK_RATE_MS);
    ESP_LOGI(TAG, "start sending...");

    while (1) {

        // Check if ready to send the terrain class
        if(packet_ready)
        {
            ESP_LOGI(TAG, "Sending Packet...");
            
            packet_ready = false;
            // How many bytes are left to send?
            int to_write = packet_size;
            for(int i=0; i<(int)WINDOW_SIZE/2;i++){
                for (int j=0; j<NUM_ADC; j++){
                    int idx= i*(int)WINDOW_SIZE/2+j;
                    window[i][j]= (float)packet[idx]/4096.0;
                }   
            }
            TickType_t start= xTaskGetTickCount();            
            feed_forward(window);
            TickType_t end= xTaskGetTickCount();
            uint32_t total_ticks= (uint32_t) end - start;
            ESP_LOGI(TAG, "#Ticks: %d ", total_ticks);
            ESP_LOGI(TAG, "pitch=%f", output[0]);
            ESP_LOGI(TAG, "roll=%f", output[1]);
            ESP_LOGI(TAG, "F=%f", output[2]);
            //send function
            while (to_write > 0) {
                len = send(connect_socket, output + (packet_size - to_write), to_write, 0);

                if (len > 0) {
                    to_write -= len;
                } else {
                    int err = get_socket_error_code(connect_socket);

                    if (err != ENOMEM) {
                        show_socket_error_reason("send_data", connect_socket);
                        g_rxtx_need_restart = true;
                        break;
                    }
                }  
            }
            ESP_LOGI(TAG, "Buffer Sent!");    

            packet_ready = false;
        }
        else
        {
            vTaskDelay(100);
        }

        if(g_rxtx_need_restart)
        {
            break;
        }
    }
    vTaskDelete(NULL);
}

//receive data
void recv_data(void *pvParameters)
{
    ESP_LOGI(TAG, "here in rcv");
    int len = 0;
    char *databuff = (char *)malloc(EXAMPLE_DEFAULT_PKTSIZE * sizeof(char));
    while (1) {
        int to_recv = EXAMPLE_DEFAULT_PKTSIZE;
        while (to_recv > 0) {
            len = recv(connect_socket, databuff + (EXAMPLE_DEFAULT_PKTSIZE - to_recv), to_recv, 0);
            if (len > 0) {
                g_total_data += len;
                to_recv -= len;
            } else {
                show_socket_error_reason("recv_data", connect_socket);
                break;
            }
        }
        if (g_total_data > 0) {
            continue;
        } else {
            break;
        }
    }

    g_rxtx_need_restart = true;
    free(databuff);
    vTaskDelete(NULL);
}


//use this esp32 as a tcp server. return ESP_OK:success ESP_FAIL:error
esp_err_t create_tcp_server()
{
    ESP_LOGI(TAG, "server socket....port=%d\n", EXAMPLE_DEFAULT_PORT);
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        show_socket_error_reason("create_server", server_socket);
        return ESP_FAIL;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(EXAMPLE_DEFAULT_PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        show_socket_error_reason("bind_server", server_socket);
        close(server_socket);
        return ESP_FAIL;
    }
    if (listen(server_socket, 5) < 0) {
        show_socket_error_reason("listen_server", server_socket);
        close(server_socket);
        return ESP_FAIL;
    }
    connect_socket = accept(server_socket, (struct sockaddr *)&client_addr, &socklen);
    if (connect_socket < 0) {
        show_socket_error_reason("accept_server", connect_socket);
        close(server_socket);
        return ESP_FAIL;
    }
    /*connection established，now can send/recv*/
    ESP_LOGI(TAG, "tcp connection established!");
    return ESP_OK;
}
//use this esp32 as a tcp client. return ESP_OK:success ESP_FAIL:error
esp_err_t create_tcp_client()
{
    ESP_LOGI(TAG, "client socket....serverip:port=%s:%d\n",
             EXAMPLE_DEFAULT_SERVER_IP, EXAMPLE_DEFAULT_PORT);
    connect_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (connect_socket < 0) {
        show_socket_error_reason("create client", connect_socket);
        return ESP_FAIL;
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(EXAMPLE_DEFAULT_PORT);
    server_addr.sin_addr.s_addr = inet_addr(EXAMPLE_DEFAULT_SERVER_IP);
    ESP_LOGI(TAG, "connecting to server...");
    if (connect(connect_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        show_socket_error_reason("client connect", connect_socket);
        return ESP_FAIL;
    }
    ESP_LOGI(TAG, "connect to server success!");
    return ESP_OK;
}

//wifi_init_sta
void wifi_init_sta()
{
    tcp_event_group = xEventGroupCreate();

    tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_init(event_handler, NULL) );

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    wifi_config_t wifi_config = {
        .sta = {
            .ssid = EXAMPLE_DEFAULT_SSID,
            .password = EXAMPLE_DEFAULT_PWD
        },
    };

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config) );
    ESP_ERROR_CHECK(esp_wifi_start() );

    ESP_LOGI(TAG, "wifi_init_sta finished.");
    ESP_LOGI(TAG, "connect to ap SSID:%s password:%s \n",
             EXAMPLE_DEFAULT_SSID, EXAMPLE_DEFAULT_PWD);
}
//wifi_init_softap
void wifi_init_softap()
{
    tcp_event_group = xEventGroupCreate();

    tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_init(event_handler, NULL));

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    wifi_config_t wifi_config = {
        .ap = {
            .ssid = EXAMPLE_DEFAULT_SSID,
            .ssid_len = 0,
            .max_connection = EXAMPLE_MAX_STA_CONN,
            .password = EXAMPLE_DEFAULT_PWD,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK
        },
    };
    if (strlen(EXAMPLE_DEFAULT_PWD) == 0) {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "wifi_init_softap finished.SSID:%s password:%s \n",
             EXAMPLE_DEFAULT_SSID, EXAMPLE_DEFAULT_PWD);
}




int get_socket_error_code(int socket)
{
    int result;
    u32_t optlen = sizeof(int);
    int err = getsockopt(socket, SOL_SOCKET, SO_ERROR, &result, &optlen);
    if (err == -1) {
        ESP_LOGE(TAG, "getsockopt failed:%s", strerror(err));
        return -1;
    }
    return result;
}

int show_socket_error_reason(const char *str, int socket)
{
    int err = get_socket_error_code(socket);

    if (err != 0) {
        ESP_LOGW(TAG, "%s socket error %d %s", str, err, strerror(err));
    }

    return err;
}

int check_working_socket()
{
    int ret;
#if EXAMPLE_ESP_TCP_MODE_SERVER
    ESP_LOGD(TAG, "check server_socket");
    ret = get_socket_error_code(server_socket);
    if (ret != 0) {
        ESP_LOGW(TAG, "server socket error %d %s", ret, strerror(ret));
    }
    if (ret == ECONNRESET) {
        return ret;
    }
#endif
    ESP_LOGD(TAG, "check connect_socket");
    ret = get_socket_error_code(connect_socket);
    if (ret != 0) {
        ESP_LOGW(TAG, "connect socket error %d %s", ret, strerror(ret));
    }
    if (ret != 0) {
        return ret;
    }
    return 0;
}

void close_socket()
{
    close(connect_socket);
    close(server_socket);
}


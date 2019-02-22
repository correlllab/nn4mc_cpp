#include <stddef.h>
#include "esp_intr_alloc.h"
#include "esp_attr.h"
#include "driver/timer.h" 
#include "esp_log.h"
#include "esp_err.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_system.h"

#include "esp_adc_cal.h"

#include "driver/gpio.h"
#include "driver/adc.h"
#include "adc_collector.h"

#include "esp_log.h"

// The data buffer will consist of 8 bytes of data for each entry in the buffer (4 sensors, 16-bit values)
// The data is stored ADC0, ADC1, ADC2, ADC3

#define ADC_0   (ADC1_CHANNEL_0)
#define ADC_1   (ADC1_CHANNEL_1)
#define TAG     "adc_collector.c:"

static void timer_isr(void* arg)
{
    // This resets the timer interrupt -- don't mess with this unless you
    // know what you're doing or want to break things
	TIMERG0.int_clr_timers.t0 = 1;
	TIMERG0.hw_timer[0].config.alarm_en = 1;

	measure_adcs();
}

// This is going to set up a hardware interrupt.  Again, don't mess with this
// unless you want to break things, or you know what you're doing.
void init_timer(int timer_period_us)
{
	timer_config_t config = {
		.alarm_en = true,
		.counter_en = false,
		.intr_type = TIMER_INTR_LEVEL,
		.counter_dir = TIMER_COUNT_UP,
		.auto_reload = true,
		.divider = 80			/* 1 us per tic */
	};

	timer_init(TIMER_GROUP_0, TIMER_0, &config);
	timer_set_counter_value(TIMER_GROUP_0, TIMER_0, 0);
	timer_set_alarm_value(TIMER_GROUP_0, TIMER_0, timer_period_us);
	timer_enable_intr(TIMER_GROUP_0, TIMER_0);
	timer_isr_register(TIMER_GROUP_0, TIMER_0, &timer_isr, NULL, 0, &s_timer_handle);

	timer_start(TIMER_GROUP_0, TIMER_0);
}


void init_buffer()
{
    // We start at index 0, and the buffer isn't full yet.
    // We are dynamically allocating the window of data that will be getting in the 
    // neural network. 
    window= (volatile float**)malloc(WINDOW_SIZE*sizeof(volatile float*));
    for (int i=0; i<WINDOW_SIZE; i++) window[i]= (volatile float*)malloc(1*sizeof(volatile float));
	buffer_idx = 0;
	buffer_full = false;

}

void init_adcs()
{
	adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC_0, ADC_ATTEN_DB_11); 
    adc1_config_channel_atten(ADC_1, ADC_ATTEN_DB_11);
    esp_adc_cal_get_characteristics(V_REF, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, &adc_characteristics);
}


void measure_adcs()
{
	int adc0_val, adc1_val;//, adc2_val, adc3_val, adc4_val, adc5_val, adc6_val, adc7_val;

	// Measure the ADCs
	adc0_val = adc1_get_raw(ADC_0);
    adc1_val = adc1_get_raw(ADC_1);
    buffer[buffer_idx++] = (uint16_t) adc0_val;
    buffer[buffer_idx++] = (uint16_t) adc1_val;

    // We collect the data with an extended buffer because 
    // in terms of data collection, there is certain delay
    // associated with having a single buffer
    if(buffer_idx == NUM_ADC * WINDOW_SIZE / 2)
    {
    	packet = (char*) buffer;
    	packet_size = sizeof(float) * NUM_OUTPUT; //This would be NUM_ADC*WINDOW_SIZE/2 if you are trying to send the full data
    	packet_ready = true;
    }

    if(buffer_idx >= NUM_ADC * WINDOW_SIZE)
    {
    	packet = (char*) (buffer + (NUM_ADC * WINDOW_SIZE / 2));
        packet_size = sizeof(float) * NUM_OUTPUT; //same. NUM_OUTPUT is the number of neurons in the output layer. 
    	packet_ready = true;

    	buffer_idx = 0;    	
    }

}



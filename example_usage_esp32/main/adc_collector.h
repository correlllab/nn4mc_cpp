#ifndef __ADC_COLLECTOR_H__
#define __ADC_COLLECTOR_H__

#ifdef __cplusplus
extern "C" {
#endif

#define WINDOW_SIZE	    100
#define NUM_ADC		    2
#define NUM_OUTPUT      2
#define V_REF			1100

#include "esp_adc_cal.h"
//uint16_t* buffer;

volatile uint16_t buffer[WINDOW_SIZE*NUM_ADC];
volatile float gradient;
volatile bool event_detected;
volatile float ** window;
float output[NUM_OUTPUT];
volatile int buffer_idx;
volatile bool buffer_full;
char* packet;
volatile int packet_size;
volatile bool packet_ready;

static intr_handle_t s_timer_handle;

volatile uint32_t timer_click_count;

esp_adc_cal_characteristics_t adc_characteristics;

void init_timer(int timer_period_us);
void init_buffer();
void init_adcs();
void measure_adcs();

#endif

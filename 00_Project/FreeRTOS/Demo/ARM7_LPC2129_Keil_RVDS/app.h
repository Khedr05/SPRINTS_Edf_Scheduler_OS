



#ifndef APP_H
#define APP_H

#include "GPIO.h"
#include "serial.h"
#define BTN1_PIN                PIN8
#define BTN2_PIN                PIN9
#define UART_TRANSMITTER_PIN    PIN2
#define RECIEVER_PIN            PIN3
#define T1_LOAD_PIN             PIN4
#define T2_LOAD_PIN             PIN5
#define IDLE_PIN                PIN6
#define TICK_PIN                PIN7
#define FALSE_VALUE             0

typedef unsigned int uint32_t;
/* variables to store in time for tasks*/
extern volatile uint32_t u32_gl_BTN1_in_time             ;
extern volatile uint32_t u32_gl_BTN2_in_time             ;
extern volatile uint32_t u32_gl_UART_TRANSMITTER_in_time ;
extern volatile uint32_t u32_gl_RECIEVER_in_time         ;
extern volatile uint32_t u32_gl_T1_LOAD_in_time          ;
extern volatile uint32_t u32_gl_T2_LOAD_in_time          ;
extern volatile uint32_t u32_gl_IDLE_TASK_in_time        ;

/* variables to store out time for tasks*/
extern volatile uint32_t u32_gl_BTN1_out_time             ;
extern volatile uint32_t u32_gl_BTN2_out_time             ;
extern volatile uint32_t u32_gl_UART_TRANSMITTER_out_time ;
extern volatile uint32_t u32_gl_RECIEVER_out_time         ;
extern volatile uint32_t u32_gl_T1_LOAD_out_time          ;
extern volatile uint32_t u32_gl_T2_LOAD_out_time          ;
extern volatile uint32_t u32_gl_IDLE_TASK_out_time        ;

/* variables to store total time for tasks*/
extern volatile uint32_t u32_gl_BTN1_total_time            ;
extern volatile uint32_t u32_gl_BTN2_total_time            ;
extern volatile uint32_t u32_gl_UART_TRANSMITTER_total_time;
extern volatile uint32_t u32_gl_RECIEVER_total_time        ;
extern volatile uint32_t u32_gl_T1_LOAD_total_time         ;
extern volatile uint32_t u32_gl_T2_LOAD_total_time         ;
extern volatile uint32_t u32_gl_IDLE_TASK_total_time       ;

extern volatile float CPULoad;
extern volatile unsigned int TotalSystemTime;

extern char taskStatuesBuffer[150];

extern void system_report(void);
#endif





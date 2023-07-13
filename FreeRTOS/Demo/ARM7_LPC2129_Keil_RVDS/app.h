



#ifndef APP_H
#define APP_H

#include "GPIO.h"
#define BTN1_PIN                24
#define BTN2_PIN                25
#define UART_TRANSMITTER_PIN    18
#define RECIEVER_PIN            19
#define T1_LOAD_PIN             20
#define T2_LOAD_PIN             21
#define IDLE_PIN                22
#define TICK_PIN                23
#define FALSE_VALUE             0

typedef unsigned int uint32_t;
/* variables to store in time for tasks*/
extern uint32_t u32_gl_BTN1_in_time             ;
extern uint32_t u32_gl_BTN2_in_time             ;
extern uint32_t u32_gl_UART_TRANSMITTER_in_time ;
extern uint32_t u32_gl_RECIEVER_in_time         ;
extern uint32_t u32_gl_T1_LOAD_in_time          ;
extern uint32_t u32_gl_T2_LOAD_in_time          ;

/* variables to store out time for tasks*/
extern uint32_t u32_gl_BTN1_out_time             ;
extern uint32_t u32_gl_BTN2_out_time             ;
extern uint32_t u32_gl_UART_TRANSMITTER_out_time ;
extern uint32_t u32_gl_RECIEVER_out_time         ;
extern uint32_t u32_gl_T1_LOAD_out_time          ;
extern uint32_t u32_gl_T2_LOAD_out_time          ;

/* variables to store total time for tasks*/
extern uint32_t u32_gl_BTN1_total_time            ;
extern uint32_t u32_gl_BTN2_total_time            ;
extern uint32_t u32_gl_UART_TRANSMITTER_total_time;
extern uint32_t u32_gl_RECIEVER_total_time        ;
extern uint32_t u32_gl_T1_LOAD_total_time         ;
extern uint32_t u32_gl_T2_LOAD_total_time         ;

#endif





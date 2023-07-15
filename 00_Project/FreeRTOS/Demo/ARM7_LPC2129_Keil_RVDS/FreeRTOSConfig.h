/*
 * FreeRTOS Kernel V10.3.0
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include <lpc21xx.h>

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE. 
 *
 * See http://www.freertos.org/a00110.html
 *----------------------------------------------------------*/
/*******************************EDF_Mowafey****************************************/
			/*Define the IDLE task deadline*/
			//INITIAL PERIOD FOR IDLE TASK
#define  INITIDLEPERIOD  				50
/*****************************END_EDF_Mowafey***************************************/

#define configUSE_PREEMPTION		1
#define configUSE_IDLE_HOOK			0
#define configUSE_TICK_HOOK			1
#define configCPU_CLOCK_HZ			( ( unsigned long ) 60000000 )	/* =12.0MHz xtal multiplied by 5 using the PLL. */
#define configTICK_RATE_HZ			( ( TickType_t ) 1000 )
#define configMAX_PRIORITIES		( 4 )
#define configMINIMAL_STACK_SIZE	( ( unsigned short ) 50 )
#define configTOTAL_HEAP_SIZE		( ( size_t ) 13 * 1024 )
#define configMAX_TASK_NAME_LEN		( 8 )
#define configUSE_16_BIT_TICKS		0
#define configIDLE_SHOULD_YIELD		1
#define configUSE_EDF_SCHEDULER   1
#define configUSE_APPLICATION_TASK_TAG 1

#define configQUEUE_REGISTRY_SIZE 	0

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES 		0
#define configMAX_CO_ROUTINE_PRIORITIES ( 2 )

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */

#define INCLUDE_vTaskPrioritySet		1
#define INCLUDE_uxTaskPriorityGet		1
#define INCLUDE_vTaskDelete				1
#define INCLUDE_vTaskCleanUpResources	0
#define INCLUDE_vTaskSuspend			1
#define INCLUDE_vTaskDelayUntil			1
#define INCLUDE_vTaskDelay				1



#define configUSE_MUTEXES           1


 // to use task state
#define configGENERATE_RUN_TIME_STATS           1
#define configUSE_TRACE_FACILITY                1
#define configUSE_STATS_FORMATTING_FUNCTIONS    1
#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()
#define portGET_RUN_TIME_COUNTER_VALUE() (T1TC)     //to convert

/* Define the traceTASK_SWITCHED_IN() macro to output the voltage associated
with the task being selected to run on port 0. */
#define traceTASK_SWITCHED_IN() {                                                                                 \
                                    if(BTN1_PIN == (int) pxCurrentTCB->pxTaskTag)                                 \
																		{                                                                             \
																			u32_gl_BTN1_in_time = T1TC;                                                 \
																		}                                                                             \
																		else if (BTN2_PIN == (int) pxCurrentTCB->pxTaskTag)                           \
																		{                                                                             \
																			u32_gl_BTN2_in_time = T1TC;                                                 \
																		}                                                                             \
																		else if (UART_TRANSMITTER_PIN == (int) pxCurrentTCB->pxTaskTag)               \
																		{                                                                      				\
																			u32_gl_UART_TRANSMITTER_in_time = T1TC;                                     \
																		}                                                                      				\
																		else if (RECIEVER_PIN == (int) pxCurrentTCB->pxTaskTag)                       \
																		{                                                                      				\
																			u32_gl_RECIEVER_in_time = T1TC;                                             \
																		}                                                                      				\
																		else if (T1_LOAD_PIN == (int) pxCurrentTCB->pxTaskTag)                        \
																		{                                                                      				\
																			u32_gl_T1_LOAD_in_time = T1TC;                                              \
																		}                                                                      				\
	                                  else if (T2_LOAD_PIN == (int) pxCurrentTCB->pxTaskTag)                        \
																		{                                                                      				\
																			u32_gl_T2_LOAD_in_time = T1TC;                                              \
																		}                                                                      				\
	                                  else if (IDLE_PIN == (int) pxCurrentTCB->pxTaskTag)                           \
																		{                                                                      				\
																			u32_gl_IDLE_TASK_in_time = T1TC;                                            \
																		} 																		                                        \
																		else                                                                          \
																		{                                                                             \
																			                                                                            \
																		}                                                                             \
																		GPIO_write(PORT_0,(int) pxCurrentTCB->pxTaskTag,PIN_IS_HIGH);                 \
																}										

																
																
																
#define traceTASK_SWITCHED_OUT() {                                                                                                               \
                                    if(BTN1_PIN == (int) pxCurrentTCB->pxTaskTag)                                                                \
																		{                                                                                                            \
																			u32_gl_BTN1_out_time    = T1TC;                                                                            \
																			u32_gl_BTN1_total_time += u32_gl_BTN1_out_time - u32_gl_BTN1_in_time;                                      \
																		}                                                                                                            \
																		else if (BTN2_PIN == (int) pxCurrentTCB->pxTaskTag)                                                          \
																		{                                                                                                            \
																			u32_gl_BTN2_out_time = T1TC;                                                                               \
																			u32_gl_BTN2_total_time += u32_gl_BTN2_out_time - u32_gl_BTN2_in_time;                                      \
																		}                                                                                                            \
																		else if (UART_TRANSMITTER_PIN == (int) pxCurrentTCB->pxTaskTag)                                              \
																		{                                                                      				                               \
																			u32_gl_UART_TRANSMITTER_out_time = T1TC;                                                                   \
																			u32_gl_UART_TRANSMITTER_total_time += u32_gl_UART_TRANSMITTER_out_time - u32_gl_UART_TRANSMITTER_in_time;  \
																		}                                                                      				                               \
																		else if (RECIEVER_PIN == (int) pxCurrentTCB->pxTaskTag)                                                      \
																		{                                                                      				                               \
																			u32_gl_RECIEVER_out_time     = T1TC;                                                                       \
																			u32_gl_RECIEVER_total_time  += u32_gl_RECIEVER_out_time - u32_gl_RECIEVER_in_time;                         \
																		}                                                                      				                               \
																		else if (T1_LOAD_PIN == (int) pxCurrentTCB->pxTaskTag)                                                       \
																		{                                                                      				                               \
																			u32_gl_T1_LOAD_out_time = T1TC;                                                                            \
																			u32_gl_T1_LOAD_total_time  += u32_gl_T1_LOAD_out_time - u32_gl_T1_LOAD_in_time;                            \
																		}                                                                      				                               \
	                                  else if (T2_LOAD_PIN == (int) pxCurrentTCB->pxTaskTag)                                                       \
																		{                                                                      				                               \
																			u32_gl_T2_LOAD_out_time = T1TC;                                                                            \
																			u32_gl_T2_LOAD_total_time  += u32_gl_T2_LOAD_out_time - u32_gl_T2_LOAD_in_time;                            \
																		}                                                                      				                               \
	                                  else if (IDLE_PIN == (int) pxCurrentTCB->pxTaskTag)                                                          \
																		{                                                                      				                               \
																			u32_gl_IDLE_TASK_out_time = T1TC;                                                                          \
																		  u32_gl_IDLE_TASK_total_time  += u32_gl_IDLE_TASK_out_time - u32_gl_IDLE_TASK_in_time;}                     \
																		else                                                                                                         \
																		{                                                                                                            \
																			                                                                                                           \
																		}                                                                                                            \
																		GPIO_write(PORT_0,(int) pxCurrentTCB->pxTaskTag,PIN_IS_LOW);                                                 \
																		TotalSystemTime = T1TC; \
									                  CPULoad = ((u32_gl_BTN1_total_time + u32_gl_BTN2_total_time +u32_gl_UART_TRANSMITTER_total_time +u32_gl_RECIEVER_total_time+u32_gl_T1_LOAD_total_time+u32_gl_T2_LOAD_total_time)/(float)TotalSystemTime)*100; \
																}

#endif /* FREERTOS_CONFIG_H */

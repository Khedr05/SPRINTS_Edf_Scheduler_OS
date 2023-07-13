/*
 * FreeRTOS Kernel V10.2.0
 * Copyright (C) 2019 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
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

/* 
	NOTE : Tasks run in system mode and the scheduler runs in Supervisor mode.
	The processor MUST be in supervisor mode when vTaskStartScheduler is 
	called.  The demo applications included in the FreeRTOS.org download switch
	to supervisor mode prior to main being called.  If you are not using one of
	these demo application projects then ensure Supervisor mode is used.
*/


/*
 * Creates all the demo application tasks, then starts the scheduler.  The WEB
 * documentation provides more details of the demo application tasks.
 * 
 * Main.c also creates a task called "Check".  This only executes every three 
 * seconds but has the highest priority so is guaranteed to get processor time.  
 * Its main function is to check that all the other tasks are still operational.
 * Each task (other than the "flash" tasks) maintains a unique count that is 
 * incremented each time the task successfully completes its function.  Should 
 * any error occur within such a task the count is permanently halted.  The 
 * check task inspects the count of each task to ensure it has changed since
 * the last time the check task executed.  If all the count variables have 
 * changed all the tasks are still executing error free, and the check task
 * toggles the onboard LED.  Should any task contain an error at any time 
 * the LED toggle rate will change from 3 seconds to 500ms.
 *
 */

/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "lpc21xx.h"
#include "semphr.h"
/* Peripheral includes. */
#include "serial.h"
#include "GPIO.h"


/*-----------------------------------------------------------*/

/* Constants to setup I/O and processor. */
#define mainBUS_CLK_FULL	( ( unsigned char ) 0x01 )

/* Constants for the ComTest demo application tasks. */
#define mainCOM_TEST_BAUD_RATE	( ( unsigned long ) 115200 )
	
void vApplicationIdleHook( void );
void vApplicationTickHook( void );

void vApplicationIdleHook( void )
{
	GPIO_write(PORT_0,PIN2,PIN_IS_HIGH);
}

void vApplicationTickHook( void )
{
	GPIO_toggle(PORT_0,PIN1);
}


TaskHandle_t LedTask_Handler=NULL;

/*
 * Configure the processor for use with the Keil demo board.  This is very
 * minimal as most of the setup is managed by the settings in the project
 * file.
 */
static void prvSetupHardware( void );
/*-----------------------------------------------------------*/
void UART_Task1 (void *pvParameter)
	 {

		 const char *message = "\n FIRST TASK IS SENDING A STRING\0";
  	 int i ;
		 int j;

    for(;;) 
	  {
	  }		
		
 }
	 
 
	 
 
 
 TaskHandle_t task1_Handler = NULL;
 TaskHandle_t task2_Handler = NULL;
 void task1 (void *pvParameter)
	 {

		TickType_t xLastWakeTime;
		const TickType_t xFrequency = 110;
     // Initialise the xLastWakeTime variable with the current time.
     xLastWakeTime = xTaskGetTickCount();

    for(;;) 
	  {
			GPIO_write(PORT_0,PIN2,PIN_IS_LOW);
			GPIO_toggle(PORT_0,PIN3);
			vTaskDelayUntil(&xLastWakeTime, xFrequency );
	  }		
		
 }
	 
 void task2 (void *pvParameter)
	 {

		TickType_t xLastWakeTime;
		const TickType_t xFrequency = 255;
     // Initialise the xLastWakeTime variable with the current time.
     xLastWakeTime = xTaskGetTickCount();

    for(;;) 
	  {
			GPIO_write(PORT_0,PIN2,PIN_IS_LOW);
			GPIO_toggle(PORT_0,PIN4);
			vTaskDelayUntil(&xLastWakeTime, xFrequency );
	  }		
		
 }
 
 
 
/*
 * Application entry point:
 * Starts all the other tasks, then starts the scheduler. 
 */
 TaskHandle_t Periodic_Transmitter_Handler = NULL;
TaskHandle_t Uart_Receiver_Handler        = NULL;
 void Uart_Receiver_task( void * pvParameters ) ; //consumer task
 void Periodic_Transmitter_task( void * pvParameters );
 
 /*************************TASK3*************************/
#define PT_TASK_PRIORITY 								    2
#define PT_TASK_STACK_SIZE         			    100
#define PT_TASK_NAME				       			    "Periodic_Transmitter"
/*************************TASK4*************************/
#define Uart_TASK_PRIORITY    						  3
#define Uart_TASK_STACK_SIZE  						  100
#define Uart_TASK_NAME										  "Uart_Receiver"
/* create a Queue */

#define   QueueLength      10
#define    ItemSize        20 * sizeof( unsigned char )
QueueHandle_t xUARTQueue;

int main( void )
{
	/* Setup the hardware for use with the Keil demo board. */
	prvSetupHardware();
xUARTQueue = xQueueCreate( QueueLength, ItemSize  );
	
    /* Create Tasks here */
xTaskPeriodicCreate(
	task1,
	"task1",
	configMINIMAL_STACK_SIZE,
	(void*) NULL,
		1,
	&task1_Handler,110);
xTaskPeriodicCreate(
	task2,
	"task2",
	configMINIMAL_STACK_SIZE,
	(void*) NULL,
		1,
	&task2_Handler,255);
	
	xTaskPeriodicCreate(Uart_Receiver_task,       Uart_TASK_NAME, Uart_TASK_STACK_SIZE, NULL, Uart_TASK_PRIORITY, &Uart_Receiver_Handler,20 );
	xTaskPeriodicCreate(Periodic_Transmitter_task,PT_TASK_NAME,   PT_TASK_STACK_SIZE,   NULL, PT_TASK_PRIORITY,   &Periodic_Transmitter_Handler,100 );
	/* Now all the tasks have been started - start the scheduler.

	NOTE : Tasks run in system mode and the scheduler runs in Supervisor mode.
	The processor MUST be in supervisor mode when vTaskStartScheduler is 
	called.  The demo applications included in the FreeRTOS.org download switch
	to supervisor mode prior to main being called.  If you are not using one of
	these demo application projects then ensure Supervisor mode is used here. */
	vTaskStartScheduler();

	/* Should never reach here!  If you do then there was not enough heap
	available for the idle task to be created. */
	for( ;; );
}
/*-----------------------------------------------------------*/

/* Function to reset timer 1 */
void timer1Reset(void)
{
	T1TCR |= 0x2;
	T1TCR &= ~0x2;
}

/* Function to initialize and start timer 1 */
static void configTimer1(void)
{
	T1PR = 1000;
	T1TCR |= 0x1;
}

static void prvSetupHardware( void )
{
	/* Perform the hardware setup required.  This is minimal as most of the
	setup is managed by the settings in the project file. */

	/* Configure UART */
	xSerialPortInitMinimal(mainCOM_TEST_BAUD_RATE);

	/* Configure GPIO */
	GPIO_init();
	
	/* Config trace timer 1 and read T1TC to get current tick */
	configTimer1();

	/* Setup the peripheral bus to be the same as the PLL output. */
	VPBDIV = mainBUS_CLK_FULL;
}
/*-----------------------------------------------------------*/
void Uart_Receiver_task( void * pvParameters )  //consumer task
{  
	
	   uint8_t UART_str[12];
			TickType_t Task2LastWakeTime;                   /* Local variable to save the last wake time of the task2. */
	Task2LastWakeTime =xTaskGetTickCount(); 
	
		
	
    for( ;; )
    {
				xQueueReceive(xUARTQueue, UART_str, portMAX_DELAY);
			  vSerialPutString((const signed char * const)UART_str, 12);
				vTaskDelayUntil(&Task2LastWakeTime, 20 );
				xSerialPutChar('\n');
		}
}

void Periodic_Transmitter_task( void * pvParameters )
{ 
		TickType_t Task2LastWakeTime;                   /* Local variable to save the last wake time of the task2. */
	Task2LastWakeTime =xTaskGetTickCount(); 
    for( ;; )
    {
				xQueueSend( xUARTQueue, ( unsigned char * )"PeriodicString" , portMAX_DELAY );
				vTaskDelayUntil(&Task2LastWakeTime, 100 );
		}
}




/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "lpc21xx.h"

/* Peripheral includes. */
#include "serial.h"
#include "GPIO.h"

#include <limits.h>
#include <semphr.h>
#include <string.h>
/*-----------------------------------------------------------*/

/* Constants to setup I/O and processor. */
#define mainBUS_CLK_FULL	( ( unsigned char ) 0x01 )

/* Constants for the ComTest demo application tasks. */
#define mainCOM_TEST_BAUD_RATE	( ( unsigned long ) 115200 )



static void prvSetupHardware( void );
/*-----------------------------------------------------------*/
/*-----------------------Macros------------------------------*/

 /*************************TASK3*************************/
#define PT_TASK_PRIORITY 								    1
#define PT_TASK_STACK_SIZE         			    100
#define PT_TASK_NAME				       			    "Periodic_Transmitter"
#define PERIODIC_TASK_PERIOD			100
/*************************TASK4*************************/
#define Uart_TASK_PRIORITY    						  1
#define Uart_TASK_STACK_SIZE  						  100
#define Uart_TASK_NAME	                  "UARTreceiver"
#define UART_RECEIVER_PERIOD			20




/*-----------------Task Handlers------------------------------*/

TaskHandle_t PeriodicTransmitterHandler = NULL;
TaskHandle_t UartReceiverHandler 				= NULL;



/*-----------------Queue Handler-------------------------------*/
QueueHandle_t xUARTQueue;

#define   QueueLength      10
#define    ItemSize        20 * sizeof( unsigned char )

/*-----------------Tasks implementation------------------------*/

void vApplicationIdleHook (void)
{
	GPIO_write (PORT_0, PIN4, PIN_IS_HIGH);
}

/*-----------------------------------------------------------*/


void Periodic_Transmitter(void *pvParameters) {
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
    for(;;) 
				{
					const char *UART_str = "ahmed_atef";
					xQueueSend(xUARTQueue, &UART_str, portMAX_DELAY);
					vTaskDelayUntil(&xLastWakeTime,PERIODIC_TASK_PERIOD);
					GPIO_write (PORT_0, PIN4, PIN_IS_LOW);
				}
}

/*--------------------------------------------------------------*/
void Uart_Receiver(void *pvParameters) {
    const char *UART_str;
		TickType_t xLastWakeTime;
		xLastWakeTime = xTaskGetTickCount();
    for(;;) 
			{
				if (xQueueReceive(xUARTQueue, &UART_str, portMAX_DELAY))  
				{
						vSerialPutString ((const signed char*)UART_str, strlen(UART_str));
				}
				vTaskDelayUntil(&xLastWakeTime,UART_RECEIVER_PERIOD);
				GPIO_write (PORT_0, PIN4, PIN_IS_LOW);
			}
}


/*--------------------------------------------------------------*/
/*
 * Application entry point:
 * Starts all the other tasks, then starts the scheduler. 
 */
int main( void )
{
	/* Setup the hardware for use with the Keil demo board. */
	prvSetupHardware();

	xUARTQueue = xQueueCreate(QueueLength, ItemSize);

    /* Create Tasks here */


								 
								 
								 
		xTaskPeriodicCreate( Periodic_Transmitter,
												 PT_TASK_NAME,
												 configMINIMAL_STACK_SIZE,
												 ( void * ) NULL,
												 PT_TASK_PRIORITY,
												 &PeriodicTransmitterHandler,
												 PERIODIC_TASK_PERIOD);	
								 
								 
		xTaskPeriodicCreate( Uart_Receiver,
												 Uart_TASK_NAME,
												 configMINIMAL_STACK_SIZE,
												 ( void * ) NULL,
												 Uart_TASK_PRIORITY,
												 &UartReceiverHandler,
												 UART_RECEIVER_PERIOD);

																 

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



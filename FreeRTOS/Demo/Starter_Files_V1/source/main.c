

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

/*GLOBAL TASKS TIME VARIABLES*/


static void prvSetupHardware( void );
/*-----------------------------------------------------------*/
/*-----------------------Macros------------------------------*/


/* variables to store in time for tasks*/
uint32_t u32_gl_BTN1_in_time                 = FALSE_VALUE;
uint32_t u32_gl_BTN2_in_time                 = FALSE_VALUE;
uint32_t u32_gl_UART_TRANSMITTER_in_time     = FALSE_VALUE;
uint32_t u32_gl_RECIEVER_in_time             = FALSE_VALUE;
uint32_t u32_gl_T1_LOAD_in_time              = FALSE_VALUE;
uint32_t u32_gl_T2_LOAD_in_time              = FALSE_VALUE;
uint32_t u32_gl_IDLE_TASK_in_time            = FALSE_VALUE;

/* variables to store out time for tasks*/
uint32_t u32_gl_BTN1_out_time                 = FALSE_VALUE;
uint32_t u32_gl_BTN2_out_time                 = FALSE_VALUE;
uint32_t u32_gl_UART_TRANSMITTER_out_time     = FALSE_VALUE;
uint32_t u32_gl_RECIEVER_out_time             = FALSE_VALUE;
uint32_t u32_gl_T1_LOAD_out_time              = FALSE_VALUE;
uint32_t u32_gl_T2_LOAD_out_time              = FALSE_VALUE;
uint32_t u32_gl_IDLE_TASK_out_time            = FALSE_VALUE;

/* variables to store total time for tasks*/
uint32_t u32_gl_BTN1_total_time               = FALSE_VALUE;
uint32_t u32_gl_BTN2_total_time               = FALSE_VALUE;
uint32_t u32_gl_UART_TRANSMITTER_total_time   = FALSE_VALUE;
uint32_t u32_gl_RECIEVER_total_time           = FALSE_VALUE;
uint32_t u32_gl_T1_LOAD_total_time            = FALSE_VALUE;
uint32_t u32_gl_T2_LOAD_total_time            = FALSE_VALUE;
uint32_t u32_gl_IDLE_TASK_total_time          = FALSE_VALUE;


/********************************************************/
 /**********  SHERIF_START *****************************/
 
/*********** TASK 1 **********************************/
 
 #define T1_TASK_PRIORITY         1
 #define T1_TASK_STACK_SIZE       250
 #define T1_TASK_NAME							"btnOneEdgeScanningTask"
 #define T1_Deadline_TIME					50
 #define T1_Periodicity_TIME      50
 
/*********** TASK 2 **********************************/
 
 #define T2_TASK_PRIORITY         1
 #define T2_TASK_STACK_SIZE       250
 #define T2_TASK_NAME							"btnTwoEdgeScanningTask"
 #define T2_Deadline_TIME					50
 #define T2_Periodicity_TIME      50
 
/******************** SHERIF_END ****************************/

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

/*********************** Mowafey ****************************/
					/** Load_1_Task5 **********************************/
#define LOAD_1_TASK_PRIORITY						1
#define LOAD_1_TASK_PERIOD				   		10
					/** Load_1_Task6 **********************************/
#define LOAD_2_TASK_PRIORITY						1
#define LOAD_2_TASK_PERIOD				   		100

					/**************************************************/
#define LOAD_5_MILLISECOND							37723
#define LOAD_12_MILLISECOND							90535
#define LOAD_5_FREQ										  10
#define LOAD_12_FREQ										100					
/********************** END_Mowafey ****************************/

/*-----------------Task Handlers------------------------------*/

TaskHandle_t PeriodicTransmitterHandler = NULL;
TaskHandle_t UartReceiverHandler 				= NULL;

 /**********  SHERIF_START *****************************/
 
TaskHandle_t btnOneEdgeScanningTask_Handler = NULL;
TaskHandle_t btnTwoEdgeScanningTask_Handler = NULL;

/**********  SHERIF_END *****************************/

/************* Mowafey ******************************/
			/*Load Simulation task_1 handler*/
TaskHandle_t Load_1_Task_Handler = NULL;
			/*Load Simulation task_2 handler*/
TaskHandle_t Load_2_Task_Handler = NULL;
/************ END_Mowafey ******************************/

/*-----------------Queue Handler-------------------------------*/
QueueHandle_t xUARTQueue;

#define   QueueLength      10
#define    ItemSize        20 * sizeof( unsigned char )

/*-----------------Tasks implementation------------------------*/

//void vApplicationIdleHook (void)
//{
//	GPIO_write (PORT_0, IDLE_PIN, PIN_IS_HIGH);
//}

/*-----------------------------------------------------------*/

/**********  SHERIF_START *****************************/
/******************** TASK 1 IMPLEMNTATION *************************/

void btnOneEdgeScanningTask(void * pvParameters)
{
	pinState_t preState = PIN_IS_LOW;
	pinState_t newState;
	TickType_t xLastTimeOfRunning;
	xLastTimeOfRunning = xTaskGetTickCount();
	/* This task is going to be represented by a voltage scale of 1. */
  vTaskSetApplicationTaskTag( NULL, ( void * ) BTN1_PIN );
	for(;;)
	{
		   //IDLE LOW
		   //GPIO_write (PORT_0, IDLE_PIN, PIN_IS_LOW);
	     newState = GPIO_read(PORT_0 , PIN0);
			 if((preState == PIN_IS_HIGH) && (newState == PIN_IS_LOW))
			 {
				   const char *UART_str = "\nBTN1 Sending Falling Edge";
					 xQueueSend( xUARTQueue,&UART_str, portMAX_DELAY);
			 }
			 else if((preState == PIN_IS_LOW) && (newState == PIN_IS_HIGH))
			 {
				   const char *UART_str = "\nBTN1 Sending Rising Edge";
					 xQueueSend( xUARTQueue,&UART_str, portMAX_DELAY);
			 }
			 else
			 {
				 /* Do Nothing */
			 }
			preState = newState; 
		  vTaskDelayUntil(&xLastTimeOfRunning,T1_Periodicity_TIME);
		 
	}	
}
/*********************** TASK 2 IMPLEMANTATION ***********************/
void btnTwoEdgeScanningTask(void * pvParameters)
{
	pinState_t preState = PIN_IS_LOW;
	pinState_t newState;
	TickType_t xLastTimeOfRunning;
	xLastTimeOfRunning = xTaskGetTickCount();
	/* This task is going to be represented by a voltage scale of 1. */
  vTaskSetApplicationTaskTag( NULL, ( void * ) BTN2_PIN );
	for(;;)
	{
		   // IDLE LOW
		   //GPIO_write (PORT_0, IDLE_PIN, PIN_IS_LOW);
	     newState = GPIO_read(PORT_0 , PIN1);
			 if((preState == PIN_IS_HIGH) && (newState == PIN_IS_LOW))
			 {
				   const char *UART_str = "\nBTN2 Sending Falling Edge";
					 xQueueSend( xUARTQueue,&UART_str, portMAX_DELAY);
			 }
			 else if((preState == PIN_IS_LOW) && (newState == PIN_IS_HIGH))
			 {
				   const char *UART_str = "\nBTN2 Sending Rising Edge";
					 xQueueSend( xUARTQueue,&UART_str, portMAX_DELAY);
			 }
			 else
			 {
				 /* Do Nothing */
			 }
			preState = newState; 
		  vTaskDelayUntil(&xLastTimeOfRunning,T1_Periodicity_TIME);					 
	}	
}
 
/**********  SHERIF_END *****************************/

void Periodic_Transmitter(void *pvParameters) {
	const char *UART_str = "\nahmed_atef";
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	/* This task is going to be represented by a voltage scale of 1. */
  vTaskSetApplicationTaskTag( NULL, ( void * ) UART_TRANSMITTER_PIN );
    for(;;) 
				{
					//idle_low
				  //GPIO_write (PORT_0, IDLE_PIN, PIN_IS_LOW);
					xQueueSend(xUARTQueue, &UART_str, portMAX_DELAY);
					vTaskDelayUntil(&xLastWakeTime,PERIODIC_TASK_PERIOD);
				}
}

/*--------------------------------------------------------------*/
void Uart_Receiver(void *pvParameters) {
    const char *UART_str;
		TickType_t xLastWakeTime;
		xLastWakeTime = xTaskGetTickCount();
	 /* This task is going to be represented by a voltage scale of 1. */
    vTaskSetApplicationTaskTag( NULL, ( void * ) RECIEVER_PIN );
    for(;;) 
			{
				//idle_low
				//GPIO_write (PORT_0, IDLE_PIN, PIN_IS_LOW);
				if (xQueueReceive(xUARTQueue, &UART_str, portMAX_DELAY))  
				{
						vSerialPutString ((const signed char*)UART_str, strlen(UART_str));
				}
				vTaskDelayUntil(&xLastWakeTime,UART_RECEIVER_PERIOD);
				
			}
}

/*************** Mowafey ********************************************/
/*  Load_1_Task to be created */
void Load_1_Task(void * pvParameters)
{
	
	uint32_t loopCounter = pdFALSE;
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = LOAD_5_FREQ;
  // Initialise the xLastWakeTime variable with the current time.
  xLastWakeTime = xTaskGetTickCount ();
	/* This task is going to be represented by a voltage scale of 1. */
  vTaskSetApplicationTaskTag( NULL, ( void * ) T1_LOAD_PIN );
 for(;;)
	{
		//idle_low
		//GPIO_write (PORT_0, IDLE_PIN, PIN_IS_LOW);
		for(loopCounter = pdFALSE; loopCounter <= LOAD_5_MILLISECOND; loopCounter++)
		{
			//Do nothing
			//loopCounter = loopCounter;
		}
		/*Provide a delay to give the cpu access*/		
		vTaskDelayUntil( &xLastWakeTime, xFrequency );		
	 }		
	 vTaskDelete(Load_1_Task_Handler);
}



/*  Load_2_Task to be created */
void Load_2_Task(void * pvParameters)
{
	
	uint32_t loopCounter = pdFALSE;
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = LOAD_12_FREQ;
  // Initialise the xLastWakeTime variable with the current time.
  xLastWakeTime = xTaskGetTickCount ();
	/* This task is going to be represented by a voltage scale of 1. */
  vTaskSetApplicationTaskTag( NULL, ( void * ) T2_LOAD_PIN );
 for(;;)
	{
		//idle_low
		//GPIO_write (PORT_0, IDLE_PIN, PIN_IS_LOW);
		for(loopCounter = pdFALSE; loopCounter <= LOAD_12_MILLISECOND; loopCounter++)
		{
			//Do nothing
		}
		/*Provide a delay to give the cpu access*/		
		vTaskDelayUntil( &xLastWakeTime, xFrequency );		
	 }		
	 vTaskDelete(Load_2_Task_Handler);
}
/*************** END_Mowafey*****************************************/

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
	
	/****************** SHERIF START ****************************/
	/***************** Create Task 1 ****************/
	xTaskPeriodicCreate
	(
			btnOneEdgeScanningTask,
			T1_TASK_NAME,
			T1_TASK_STACK_SIZE,
			(void*) NULL,
				T1_TASK_PRIORITY,
			&btnOneEdgeScanningTask_Handler,
			T1_Periodicity_TIME
	);
  /***************** Create Task 2 ****************/			
		xTaskPeriodicCreate
	(
			btnTwoEdgeScanningTask,
			T2_TASK_NAME,
			T2_TASK_STACK_SIZE,
			(void*) NULL,
			T2_TASK_PRIORITY,
			&btnTwoEdgeScanningTask_Handler,
			T2_Periodicity_TIME
	);		

	/**************** SHERIF END *************************/								 
	
	
	
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


/************ Mowafey ************************************/
		xTaskPeriodicCreate( 
									Load_1_Task,
									"Load_1_Task",
									configMINIMAL_STACK_SIZE,
									(void *) 1,
									LOAD_1_TASK_PRIORITY,												
									&Load_1_Task_Handler,
									LOAD_1_TASK_PERIOD	);
									
		xTaskPeriodicCreate( 
									Load_2_Task,
									"Load_2_Task",
									configMINIMAL_STACK_SIZE,
									(void *) 1,
									LOAD_2_TASK_PRIORITY,												
									&Load_2_Task_Handler,
									LOAD_2_TASK_PERIOD	);
/************ END_Mowafey********************************/												 

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



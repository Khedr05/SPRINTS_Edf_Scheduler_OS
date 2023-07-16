
#include "proj_tasks.h"

/* Tasks Handlers */
TaskHandle_t Button1Task_Handler          = NULL;
TaskHandle_t Button2Task_Handler          = NULL;
TaskHandle_t Periodic_Transmitter_Handler = NULL;
TaskHandle_t Uart_Receiver_Handler        = NULL;
TaskHandle_t Load_1_Simulation_Handler    = NULL;
TaskHandle_t Load_2_Simulation_Handler    = NULL;


static void Button1_task( void * pvParameters );
static void Button2_task( void * pvParameters );
static void Periodic_Transmitter_task( void * pvParameters );
static void Uart_Receiver_task( void * pvParameters );
static void Load_1_Simulation_task( void * pvParameters );
static void Load_2_Simulation_task( void * pvParameters );
/* Global Variables */ 




/* create a Queue */
QueueHandle_t xUARTQueue;

void A2_Task3create(void)
{
	xUARTQueue = xQueueCreate( QueueLength, ItemSize  ); 
	
	xTaskCreate(Button1_task,             BTN1_TASK_NAME,  BTN1_TASK_STACK_SIZE, NULL, BTN1_TASK_PRIORITY, &Button1Task_Handler );
	xTaskCreate(Button2_task,             BTN2_TASK_NAME, BTN2_TASK_STACK_SIZE, NULL, BTN2_TASK_PRIORITY, &Button2Task_Handler );
	xTaskCreate(Uart_Receiver_task,       Uart_TASK_NAME, Uart_TASK_STACK_SIZE, NULL, Uart_TASK_PRIORITY, &Uart_Receiver_Handler );
	xTaskCreate(Periodic_Transmitter_task,PT_TASK_NAME,   PT_TASK_STACK_SIZE,   NULL, PT_TASK_PRIORITY,   &Periodic_Transmitter_Handler );
	xTaskCreate(Load_1_Simulation_task,   TASK5_NAME,     TASK5_STACK_SIZE,     NULL, TASK5_PRIORITY,     &Load_1_Simulation_Handler );
  xTaskCreate(Load_2_Simulation_task,   TASK6_NAME,     TASK6_STACK_SIZE,     NULL, TASK6_PRIORITY,     &Load_2_Simulation_Handler );
}

void Button1_task( void * pvParameters )
{
		pinState_t BTN1OldState = PIN_IS_LOW;
		pinState_t BTN1NewState;
    for( ;; )
    {
				BTN1NewState = GPIO_read(BTN1_PORT, BTN1_PIN);
			  /* Case Rising Edge */
				if(BTN1OldState == PIN_IS_LOW && BTN1NewState == PIN_IS_HIGH)
				{
						xQueueSend( xUARTQueue, ( unsigned char * )"BTN1 RISING" , portMAX_DELAY );
				}
				/* Case Falling Edge */
				else if(BTN1OldState == PIN_IS_HIGH && BTN1NewState == PIN_IS_LOW)
				{
						xQueueSend( xUARTQueue, ( unsigned char * )"BTN1 FALLING" , portMAX_DELAY );
				}
				BTN1OldState = BTN1NewState;
				vTaskDelay(100);
    }
}

void Button2_task( void * pvParameters )
{
	  pinState_t BTN2OldState = PIN_IS_LOW;
    pinState_t BTN2NewState;
    for( ;; )
    {
				BTN2NewState = GPIO_read(BTN2_PORT, BTN2_PIN);
			  /* Case Rising Edge */
				if(BTN2OldState == PIN_IS_LOW && BTN2NewState == PIN_IS_HIGH)
				{
						xQueueSend( xUARTQueue, ( unsigned char * )"BTN2  RISING" , portMAX_DELAY );
				}
				/* Case Falling Edge */
				else if(BTN2OldState == PIN_IS_HIGH && BTN2NewState == PIN_IS_LOW)
				{
						xQueueSend( xUARTQueue, ( unsigned char * )"BTN2 FALLING" , portMAX_DELAY );
				}
				BTN2OldState = BTN2NewState;
				vTaskDelay(100);
		}
}

void Uart_Receiver_task( void * pvParameters )  //consumer task
{
		uint8_t UART_str[12];
    for( ;; )
    {
				xQueueReceive(xUARTQueue, UART_str, portMAX_DELAY);
			  vSerialPutString((const signed char * const)UART_str, 12);
				vTaskDelay(100);
				xSerialPutChar('\n');
		}
}

void Periodic_Transmitter_task( void * pvParameters )
{
    for( ;; )
    {
				xQueueSend( xUARTQueue, ( unsigned char * )"PeriodicString" , portMAX_DELAY );
				vTaskDelay(100);
		}
}

void Load_1_Simulation_task( void * Task1_Parameters )
{
	  uint32_t i=0,X=100000;
		TickType_t Task1LastWakeTime;										/* Local variable to save the last wake time of the task1. */
	

	
	for( ;; )
	{	
		for(i=0;i<X;i++) 											    	/* Loop to increase the execution time of task1 */
		{
			i=i;
		}
		
	}
}

void Load_2_Simulation_task( void * Task1_Parameters )
{
	  uint32_t i=0,X=100000;
		TickType_t Task1LastWakeTime;										/* Local variable to save the last wake time of the task1. */
	

	
	for( ;; )
	{	
		for(i=0;i<X;i++) 											    	/* Loop to increase the execution time of task1 */
		{
			i=i;
		}
		
	}
}
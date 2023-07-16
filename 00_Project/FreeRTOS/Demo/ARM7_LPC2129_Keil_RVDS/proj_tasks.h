
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

/*************************TASK1*************************/
#define BTN1_PORT												   PORT_0
#define BTN1_PIN 											   	 PIN0

#define BTN1_TASK_PRIORITY 							   1
#define BTN1_TASK_STACK_SIZE         		   100
#define BTN1_TASK_NAME				       			 "Button_1_Monitor"
/*************************TASK2*************************/
#define BTN2_PORT												    PORT_0
#define BTN2_PIN 												    PIN1

#define BTN2_TASK_PRIORITY 							    3
#define BTN2_TASK_STACK_SIZE         		    100
#define BTN2_TASK_NAME				       			  "Button_2_Monitor"
/*************************TASK3*************************/
#define PT_TASK_PRIORITY 								    1
#define PT_TASK_STACK_SIZE         			    100
#define PT_TASK_NAME				       			    "Periodic_Transmitter"
/*************************TASK4*************************/
#define Uart_TASK_PRIORITY    						  1
#define Uart_TASK_STACK_SIZE  						  100
#define Uart_TASK_NAME										  "Uart_Receiver"
/*************************TASK5*************************/
#define TASK5_PRIORITY    						      1
#define TASK5_STACK_SIZE  						      100
#define TASK5_NAME										      "Load_1_Simulation"
/*************************TASK6*************************/		
#define TASK6_PRIORITY    						      1
#define TASK6_STACK_SIZE  						      100
#define TASK6_NAME										      "Load_1_Simulation"


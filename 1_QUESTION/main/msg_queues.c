//1. Create 3 realtime tasks each with the periodcity T1=1000ms, T2=2000ms, T3=5000ms. Also create two additional task T4 and T5 where T4 sends integer data to T5 using Messsage Queues.

#include <stdio.h>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>


QueueHandle_t QUEUES;

void Task_1(void *sens)
{
	while(1)
	{
		printf("Task_1 is Functioning\n");
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
	vTaskDelete(Task_1);
}

void Task_2(void *sens)
{
	while(1)
	{
		printf("Task_2 is Functioning\n");
		vTaskDelay(2000 / portTICK_PERIOD_MS);
	}
	vTaskDelete(Task_2);
}


void Task_3(void *sens)
{
	while(1)
	{
		printf("Task_3 is Functioning\n");
		vTaskDelay(5000 / portTICK_PERIOD_MS);
	}
	vTaskDelete(Task_3);
}


void Task_4(void *sens)
{
	int send_data = 0
	while(1)
	{
		send_data++;
		printf("Task_4 is Functioning: Sending Data\n");
		xQueueSend(sensor_queue, &send_data, portMAX_DELAY);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
	vTaskDelete(Task_4);
}


void Task_5(void *sens)
{
	int receive_data = 0
	while(1)
	{
		printf("Task_5 is Functioning: Receiving Data\n");
		xQueueReceive(sensor_queue, &receive_data, portMAX_DELAY);
		vTaskDelay(5000 / portTICK_PERIOD_MS);
	}
	vTaskDelete(Task_5);
}


void app_main()
{
//	BaseType_t result;
	QUEUES = xQueueCreate(10, sizeof(int));
	result = xTaskCreate(Task_1, "Task_1", 2048, NULL, 5, NULL);
	if(result != pdPASS)
	{
		printf("TASK_1 NOT CREATED\n");
		exit(-1);
	}

	result = xTaskCreate(Task_2, "Task_2", 2048, NULL, 6, NULL);
	if(result != pdPASS)
	{
		printf("TASK_2 NOT CREATED\n");
		exit(-1);
	}
	

	result = xTaskCreate(Task_3, "Task_3", 2048, NULL, 7, NULL);
	if(result != pdPASS)
	{
		printf("TASK_3 NOT CREATED\n");
		exit(-1);
	}
	

	result = xTaskCreate(Task_4, "Task_4", 2048, NULL, 8, NULL);
	if(result != pdPASS)
	{
		printf("TASK_4 NOT CREATED\n");
		exit(-1);
	}
	

	result = xTaskCreate(Task_5, "Task_5", 2048, NULL, 9, NULL);
	if(result != pdPASS)
	{
		printf("TASK_5 NOT CREATED\n");
		exit(-1);
	}

	printf("\nDONE\n");
}

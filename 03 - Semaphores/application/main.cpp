#include "FreeRTOS.h"
#include "portmacro.h"
#include "projdefs.h"
#include "semphr.h"
#include "stm32f411xe.h"
#include "task.h"
#include <stdlib.h>

#include "communication/usart.cpp"

#define BUFFER_SIZE 10
int buffer[BUFFER_SIZE];
int head = 0, tail = 0;

SemaphoreHandle_t semaphore_empty;
SemaphoreHandle_t semaphore_full;

char endOfLine[3] = "\r\n";
int endOfLine_size = 2;

/******************************************************************************
  Helper Function: Convert Integers to ASCII
******************************************************************************/
int intToAscii(int value, char* buffer) {
    if (value < 0) {
        buffer[0] = '-';
        buffer++;
        value = -value;
    }

    // Count digits
    int temp = value;
    int digits = 0;
    do {
        temp /= 10;
        digits++;
    } while (temp != 0);

    // Fill buffer from the end
    buffer[digits] = '\0'; // null-terminator if needed
    for (int i = digits - 1; i >= 0; i--) {
        buffer[i] = (value % 10) + '0';
        value /= 10;
    }

    return digits;
}

/******************************************************************************
  Function: Proucer Task [Constantly adds data]
******************************************************************************/
void producer_task(void* parms) {
    static int count = 0;
    while (true) {
        xSemaphoreTake(semaphore_full, portMAX_DELAY);

        buffer[tail] = rand() % 1000;
        tail = (tail + 1) % BUFFER_SIZE;

        char buffer_value[16];
        int size_buff = intToAscii(count++, buffer_value);

        char produced[] = "Producer sent value #";
        int size = sizeof(produced) / sizeof(char);

        sendData(produced, size);
        sendData(buffer_value, size_buff);
        sendData(endOfLine, endOfLine_size);

        xSemaphoreGive(semaphore_empty);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

/******************************************************************************
  Function: Consumer Task [Constantly removes data at variable intervals
******************************************************************************/
void consumer_task(void* parms) {
    while (true) {
        xSemaphoreTake(semaphore_empty, portMAX_DELAY);

        char taken_sem[] = "Consumer acquired value: ";
        int size_sem = sizeof(taken_sem) / sizeof(char);

        char buffer_value[16];
        int size_buff = intToAscii(buffer[head], buffer_value);

        head = (head + 1) % BUFFER_SIZE;

        sendData(taken_sem, size_sem);
        sendData(buffer_value, size_buff);
        sendData(endOfLine, endOfLine_size);

        xSemaphoreGive(semaphore_full);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

/******************************************************************************
  Function: Main
******************************************************************************/
int main(void) {
    init_uart(); // Initialize UART2

    semaphore_empty = xSemaphoreCreateCounting(BUFFER_SIZE, 0);
    semaphore_full = xSemaphoreCreateCounting(BUFFER_SIZE, BUFFER_SIZE);
    xTaskCreate(producer_task, "Producer", 128, NULL, 1, NULL);
    xTaskCreate(consumer_task, "Consumer", 128, NULL, 1, NULL);

    vTaskStartScheduler();
    while (1);
}

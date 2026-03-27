#include "FreeRTOS.h"
#include "portmacro.h"
#include "projdefs.h"
#include "semphr.h"
#include "stm32f411xe.h"
#include "task.h"

SemaphoreHandle_t xMutex;

void init_leds() {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    GPIOC->MODER &= ~(3 << (13 * 2));
    GPIOC->MODER |= 1 << (13 * 2);
    GPIOC->ODR |= (1 << 13);

    // Set PA5 as general purpose output
    GPIOA->MODER &= ~(3 << (5 * 2)); // Clear mode bits
    GPIOA->MODER |= (1 << (5 * 2));  // Set to output
    GPIOA->ODR &= ~GPIO_ODR_OD5_Msk; // Turn LED off initially
}

void general_task(void* parms) {
    while (true) {
        if (xSemaphoreTake(xMutex, portMAX_DELAY) == pdTRUE) {

            GPIOA->ODR ^= (1 << 5); // Toggle PA5
            vTaskDelay(pdMS_TO_TICKS(500));
            xSemaphoreGive(xMutex);
        }
        vTaskDelay(pdMS_TO_TICKS(500)); // Small delay to let other tasks run
    }
}

void mutex_dependent_task(void* parms) {
    while (true) {
        if (xSemaphoreTake(xMutex, portMAX_DELAY) == pdTRUE) {

            GPIOC->ODR ^= (1 << 13);
            xSemaphoreGive(xMutex); // Give it back!
        }
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

int main(void) {
    init_leds();

    xMutex = xSemaphoreCreateMutex();
    xTaskCreate(general_task, "Generic_Task", 128, NULL, 1, NULL);
    xTaskCreate(mutex_dependent_task, "Mutex_Task", 128, NULL, 1, NULL);

    vTaskStartScheduler();
    while (1);
}

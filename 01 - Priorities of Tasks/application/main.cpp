#include "FreeRTOS.h"
#include "stm32f411xe.h"
#include "task.h"

// LED Task: toggles PC13 every 500 ms
void LedTask(void* params) {
    (void)params; // unused
    while (1) {
        GPIOC->ODR ^= (1 << 13); // Toggle PC13
    }
}

void LedAlternateTask(void* parms) {
    (void)parms;
    while (1) {
        GPIOA->ODR ^= (1 << 5); // Toggle PC13
    }
}

// Initialize onboard LED (PC13)
void init_builtin_led() {
    // Enable GPIOC clock
    RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIOAEN);

    // Set PC13 as general purpose output
    GPIOC->MODER &= ~(3 << (13 * 2)); // Clear mode bits
    GPIOC->MODER |= (1 << (13 * 2));  // Set to output
    GPIOC->ODR |= (1 << 13);          // Turn LED off initially

    // Set PA5 as general purpose output
    GPIOA->MODER &= ~(3 << (5 * 2)); // Clear mode bits
    GPIOA->MODER |= (1 << (5 * 2));  // Set to output
    GPIOA->ODR &= ~GPIO_ODR_OD5_Msk; // Turn LED off initially
}

int main(void) {
    init_builtin_led();

    // Create LED task
    xTaskCreate(LedTask, "LED_A", 128, NULL, 2, NULL);
    xTaskCreate(LedAlternateTask, "LED_B", 128, NULL, 2, NULL);

    // Start FreeRTOS scheduler
    vTaskStartScheduler();

    // Should never reach here
    while (1);
}

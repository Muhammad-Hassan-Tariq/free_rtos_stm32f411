# 02 - Mutexes

## Overview
- This project demonstrates  **Mutex Locks** on the STM32F411 MCU.

## Working  
- Even though mutex dependent task wants to toggle pin every 50ms but due to mutex lock by general task it stops for 500ms.

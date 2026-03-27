![STM32](https://img.shields.io/badge/STM32-F411-blue)
![ARM](https://img.shields.io/badge/ARM-Cortex--M4-orange)
![FreeRTOS](https://img.shields.io/badge/FreeRTOS-OS-brightgreen)
![Language](https://img.shields.io/badge/Language-C%2B%2B-green)
![Build](https://img.shields.io/badge/Build-Make-red)
![Build Status](https://img.shields.io/badge/Build-Passing-brightgreen)
![License](https://img.shields.io/badge/License-MIT-green)
<img align="center" width="413" height="157" alt="image" src="https://github.com/user-attachments/assets/b39cebb7-3df2-441f-bced-baf93e638e2a" />

## 📌 STM32 FreeRTOS Learning Labs

This repository contains a collection of **FreeRTOS experiments on STM32F411**
mostly implemented using **CMSIS**. 

Each subdirectory is a self-contained lab focused on **features and applications of FreeRTOS**

Target MCU: **STM32F411 (Cortex-M4) aka The Black Pill**

---

## 🎯 Goals of This Repository

- Understand FreeRTOS and it's working
- Learn how peripheral usage can be optimized with **FreeRTOS**
- How to use best practices in **c++** for maximum efficiency

This is not production firmware — it is a **silicon exploration lab**.

---

## 🗂 Projects [This Repo is not complete yet]
- [01 - Priorities of Tasks](https://github.com/Muhammad-Hassan-Tariq/free_rtos_stm32f411/tree/main/01%20-%20Priorities%20of%20Tasks)
- [02 - Mutexes](https://github.com/Muhammad-Hassan-Tariq/free_rtos_stm32f411/tree/main/02%20-%20Mutexes) 

### 📁 Project Directories 
.  
├── 📱 application/        High-level logic (Tasks, Control Loops, Utilities)  
│   ├── 📡 communication/  UART/I2C/SPI Task implementations   
│   ├── 🎮 control/        PID loops or logic controllers    
│   └── 🛠️ utils/          Helper functions and C++ wrappers  
├── 🔌 bsp/                Board Support Package (Hardware abstractions)  
├── 🧠 core/               RTOS Config & Low-level System handlers  
│   ├── 📂 inc/            FreeRTOSConfig.h (The heart of the kernel 🫀)  
│   └── 📂 src/            Syscalls, Fault Handlers, and Sysmem  
├── 🏎️ drivers/            Headers (CMSIS & STM32F4xx)  
├── 📦 middlewares/        The Engine: FreeRTOS Kernel Source ⚙️  
├── 🏁 startup/            Vector Table (.s) & Linker Script (.ld)  
├── 🏗️ build/              Compiled objects & Final Binaries (Git Ignored 🚫)  
├── 📜 makefile            The Magic Script that builds it all 🪄  
└── 🔧 compile_commands.json # Neovim/LSP support for that elite dev experience 💻  

## ⚙️ Toolchain Used

All projects use the same base toolchain:

- Compiler: `arm-none-eabi-gcc`
- Assembler: `arm-none-eabi-as`
- Linker script: `startup/STM32F411CEU6_FLASH.ld`
- Startup code: `startup/startup_stm32f411xe.s`

Flashing via:

- `OpenOCD`
- `dfu-util`

Build system: simple `makefile` per project

---

## ▶️ Getting Started

- **Install Tools**  
  *-> For **Debian** based OS*
  - `sudo apt install gcc-arm-none-eabi binutils-arm-none-eabi libnewlib-arm-none-eabi git make openocd dfu-util`
  
  *-> For **Red Hat** based OS*
  - `sudo dnf install arm-none-eabi-gcc-cs arm-none-eabi-binutils-cs arm-none-eabi-newlib git make openocd dfu-util`
  
  *-> For **Arch** based OS*
  - `sudo pacman -S arm-none-eabi-gcc arm-none-eabi-binutils arm-none-eabi-newlib git make openocd dfu-util`
  
- **Verify Installation**
  - `arm-none-eabi-g++ --version`
  
- **Clone this repository to local system**
  - `git clone https://github.com/Muhammad-Hassan-Tariq/free_rtos_stm32f411.git`
    

- **Build & Flash**
    - Change directory to any project listed
    - `sudo make openocd_flash`
    -   OR
    - `sudo make dfu`

---

## 💻 My Development Environment

- **OS:** Arch Linux
- **Editor:** Neovim + clangd LSP
- **Build:** GNU Make
- **Debug:** GDB + ST-Link V2
- **Language:** C++ (with C-style register access)

**Why C++ for embedded?**
- Type safety without performance overhead
- constexpr for compile-time optimization
- Templates for zero-cost abstractions
- Better than C for large firmware projects


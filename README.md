
# FreeRTOS #1 - EmbarcaTech 2025

Author: **Luana Menezes**

Course: Technological Residency in Embedded Systems

Institution: EmbarcaTech - HBr

Campinas, June 2025

---

# FreeRTOS Task Management System

This project implements a multi-task system using FreeRTOS on the Raspberry Pi Pico, demonstrating **task scheduling**, **task control**, and **concurrent execution** with hardware peripherals.

## Objective

Create an interactive demonstration of FreeRTOS features including:

- Task creation and scheduling
- Task control mechanisms (suspend/resume)
- Real-time task management
- RGB LED visual feedback
- Buzzer audio notifications

## Bill of Materials

| Component             | BitDogLab Connection      |
|-----------------------|---------------------------|
| BitDogLab (RP2040)    | -                         |
| RGB LED               | GPIO 11, 12, 13           |
| Buzzer                | GPIO 21                   |
| Buttons               | GPIO 5, 6                 |

## Setup and Execution

1. Open the project in VS Code with Raspberry Pi Pico SDK environment (CMake + ARM compiler);
2. Build the project normally (Ctrl+Shift+B in VS Code or via terminal with cmake and make);
3. Connect your BitDogLab via USB cable and put the Pico in boot mode (press BOOTSEL button and connect cable);
4. Copy the generated .uf2 file to the storage unit that appears (RPI-RP2);
5. The Pico will automatically restart and begin executing the code;
6. RGB LED will provide visual feedback and buzzer will give audio notifications based on task states.

## System Logic

- **LED Task**: Cycles RGB LED through Red→Green→Blue colors every 500ms
- **Buzzer Task**: Plays 700Hz tone for 500ms every 1.5 seconds  
- **Button Task**: 
  - Button A (GPIO 5): Suspend/Resume LED task
  - Button B (GPIO 6): Suspend/Resume Buzzer task
- **Task Priorities**: LED and Buzzer tasks (priority 1), Button task (priority 2)

## Project Files

- `src/main.c`: Main project code with FreeRTOS implementation;
- `CMakeLists.txt`: Build configuration file;
- Additional source files as per project structure.

## Features Demonstrated

- **Task Scheduling**: Three concurrent tasks with different priorities
- **Task Control**: Suspend and resume operations via button input
- **Hardware Control**: RGB LED cycling and PWM buzzer control
- **Real-time Execution**: Non-blocking task delays using vTaskDelay()

## 🖼️ Project Images


## 📜 Licença
GNU GPL-3.0.

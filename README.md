
# Task: FreeRTOS #1 - EmbarcaTech 2025

Author: **Luana Menezes**

Course: Technological Residency in Embedded Systems

Institution: EmbarcaTech - HBr

Campinas, June 2025

---

# FreeRTOS Basic Multi-Task

This project develops an embedded multi-task system using the BitDogLab board, programmed with FreeRTOS in C language on VSCode. The system concurrently controls three board peripherals:

- **RGB LED**: Cyclically alternates between red, green, and blue colors
- **Buzzer**: Emits periodic beeps 
- **Two Buttons**: 
  - Button A: Suspends or resumes the LED task
  - Button B: Suspends or resumes the buzzer task

The implementation demonstrates **concurrent task execution**, **task control mechanisms**, and **real-time peripheral management** using FreeRTOS scheduling capabilities.

## Reflection and Analysis

**What happens if all tasks have the same priority?**
Answer: When all tasks have equal priority (priority 1), FreeRTOS uses time-slicing to share CPU time between them. However, since your tasks spend most of their time sleeping (`vTaskDelay()`), they don't compete for CPU simultaneously. The system works fine because tasks naturally coordinate through their different sleep intervals - LED changes every 500ms, buzzer beeps every 1500ms, and buttons check every 50ms. The equal priority doesn't cause issues because tasks are rarely active at the same time. Equal priorities matter only when multiple tasks are **ready to run** simultaneously, not when they're sleeping.

**Which task consumes more CPU time?**
Answer: About the question **Which task consumes more CPU time?** 
The button monitoring task consumes the most CPU time since it runs continuously checking button states, while LED and buzzer tasks spend most of their time in sleep state using vTaskDelay().


**What would be the risks of using polling without priorities?**
Answer: Without priorities, polling-based systems risk missing critical events, experiencing unpredictable response times, and potential system blocking if one task enters an infinite loop or takes too long to execute.


## Objective

Develop practical skills in embedded multi-task programming using FreeRTOS. Upon completion, you will be able to:

- Create and manage multiple tasks with FreeRTOS
- Understand scheduling and priorities in RTOS
- Use vTaskCreate(), vTaskSuspend() and vTaskResume() commands
- Control GPIOs with FreeRTOS
- Organize projects in VSCode with pico-sdk and FreeRTOS

## Bill of Materials

| Component             | BitDogLab Connection      |
|-----------------------|---------------------------|
| BitDogLab (RP2040)    | -                         |
| RGB LED               | GPIO 11, 12, 13           |
| Buzzer                | GPIO 21                   |
| Buttons               | GPIO 5, 6                 |

## Setup and Execution

1. Clone the FreeRTOS kernel with:
   ```bash
   git clone https://github.com/FreeRTOS/FreeRTOS-Kernel.git FreeRTOS-Kernel
   ```
2. Open the project in VS Code with Raspberry Pi Pico SDK environment (CMake + ARM compiler);
3. Build the project normally (Ctrl+Shift+B in VS Code or via terminal with cmake and make);
4. Connect your BitDogLab via USB cable and put the Pico in boot mode (press BOOTSEL button and connect cable);
5. Copy the generated .uf2 file to the storage unit that appears (RPI-RP2);
6. The Pico will automatically restart and begin executing the code;
7. The system will run automatically: the RGB LED will cycle through colors (red, green, blue), the buzzer will beep periodically, and you can use Button A to start/stop the LED and Button B to start/stop the buzzer.


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

## Features Demonstrated

- **Task Scheduling**: Three concurrent tasks with different priorities
- **Task Control**: Suspend and resume operations via button input
- **Hardware Control**: RGB LED cycling and PWM buzzer control
- **Real-time Execution**: Non-blocking task delays using vTaskDelay()

## 🖼️ Project Images/Videos

- Video
  
https://github.com/user-attachments/assets/7e446de4-132e-489f-a87d-59754baa0d30

## 📜 License
GNU GPL-3.0.

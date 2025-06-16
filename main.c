#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/clocks.h"
#include "hardware/pwm.h"
#include "FreeRTOS.h"
#include "task.h"

#define LED_GREEN_PIN 11
#define LED_RED_PIN 12
#define LED_BLUE_PIN 13

#define BUTTON_A_PIN 5
#define BUTTON_B_PIN 6

#define BUZZER_PIN 21

TaskHandle_t led_task_handle = NULL;
TaskHandle_t buzzer_task_handle = NULL;

bool led_task_suspended = false;
bool buzzer_task_suspended = false;

void init_rgb_led() {
  gpio_init(LED_GREEN_PIN);
  gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);

  gpio_init(LED_RED_PIN);
  gpio_set_dir(LED_RED_PIN, GPIO_OUT);

  gpio_init(LED_BLUE_PIN);
  gpio_set_dir(LED_BLUE_PIN, GPIO_OUT);
}

void set_rgb_led(uint red, uint green, uint blue) {
  gpio_put(LED_RED_PIN, red);
  gpio_put(LED_GREEN_PIN, green);
  gpio_put(LED_BLUE_PIN, blue);
}

void led_rgb_task(void *pvParameters) {
  init_rgb_led();

  while (true) {

    set_rgb_led(1, 0, 0);
    vTaskDelay(pdMS_TO_TICKS(500));

    set_rgb_led(0, 1, 0);
    vTaskDelay(pdMS_TO_TICKS(500));

    set_rgb_led(0, 0, 1);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void init_buttons() {
  gpio_init(BUTTON_A_PIN);
  gpio_set_dir(BUTTON_A_PIN, GPIO_IN);
  gpio_pull_up(BUTTON_A_PIN);

  gpio_init(BUTTON_B_PIN);
  gpio_set_dir(BUTTON_B_PIN, GPIO_IN);
  gpio_pull_up(BUTTON_B_PIN);
}

void init_buzzer() {
  gpio_set_function(BUZZER_PIN, GPIO_FUNC_PWM);
  uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);
  pwm_set_gpio_level(BUZZER_PIN, 0);
  pwm_set_enabled(slice_num, true);
}

void play_buzzer(uint frequency, uint duration_ms) {
  uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);
  uint clock_freq = clock_get_hz(clk_sys);
  uint clock_div = 1;

  uint32_t wrap = clock_freq / (frequency * clock_div);
    
  while (wrap > 65535 && clock_div < 256) {
    clock_div *= 2;
    wrap = clock_freq / (frequency * clock_div);
  }

  pwm_set_clkdiv(slice_num, clock_div);
  pwm_set_wrap(slice_num, wrap);
  pwm_set_gpio_level(BUZZER_PIN, wrap / 2);
  vTaskDelay(pdMS_TO_TICKS(duration_ms));
  pwm_set_gpio_level(BUZZER_PIN, 0);
  vTaskDelay(pdMS_TO_TICKS(50));
}

void buzzer_task(void *pvParameters) {
  init_buzzer();
  while (true) {
    play_buzzer(700, 500);
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void buttons_task(void *pvParameters) {
  init_buttons();
  bool button_a_pressed_last_state = true;
  bool button_b_pressed_last_state = true;

  while (true) {
    bool button_a_pressed = !gpio_get(BUTTON_A_PIN);
    bool button_b_pressed = !gpio_get(BUTTON_B_PIN);

    if (button_a_pressed && !button_a_pressed_last_state) {
      if (!led_task_suspended) {
        vTaskSuspend(led_task_handle);
        led_task_suspended = true;
      } else {
        vTaskResume(led_task_handle);
        led_task_suspended = false;
      }
    }

    if (button_b_pressed && !button_b_pressed_last_state) {
      if (!buzzer_task_suspended) {
        vTaskSuspend(buzzer_task_handle);
        buzzer_task_suspended = true;
      } else {
        vTaskResume(buzzer_task_handle);
        buzzer_task_suspended = false;
      }
    }

    button_a_pressed_last_state = button_a_pressed;
    button_b_pressed_last_state = button_b_pressed;

    vTaskDelay(pdMS_TO_TICKS(50));
  }
}

int main() {
  stdio_init_all();

  xTaskCreate(led_rgb_task, "LED_Task", 256, NULL, 1, &led_task_handle);
  xTaskCreate(buzzer_task, "Buzzer", 256, NULL, 1, &buzzer_task_handle);
  xTaskCreate(buttons_task, "Buttons", 256, NULL, 2, NULL);

  vTaskStartScheduler();

  while(1){};
}
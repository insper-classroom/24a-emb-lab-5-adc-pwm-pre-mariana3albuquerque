#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <queue.h>

#include "pico/stdlib.h"
#include <stdio.h>
#include "hardware/pwm.h"

const int PWM_0_PIN = 4;

void led_task(void *p) {
    gpio_set_function(PWM_0_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(PWM_0_PIN);
    pwm_set_clkdiv(slice_num, 125);
    pwm_set_wrap(slice_num, 100);
    
    // Configurar o Duty Cycle para 20%
    int duty_cycle = 20; // 20% de Duty Cycle
    pwm_set_chan_level(slice_num, PWM_CHAN_A, duty_cycle * pwm_get_wrap(slice_num) / 100);
    
    pwm_set_enabled(slice_num, true);

    while (true) {
        vTaskDelay(pdMS_TO_TICKS(1000)); // Adicione um pequeno atraso para manter a tarefa ativa
    }
}

int main() {
    stdio_init_all();
    printf("Start RTOS \n");

    xTaskCreate(led_task, "LED_Task 1", 256, NULL, 1, NULL);

    vTaskStartScheduler();

    while (true)
        ;
}

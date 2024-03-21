#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <queue.h>

#include "pico/stdlib.h"
#include <stdio.h>

#include "hardware/gpio.h"
#include "hardware/adc.h"

void adc_task(void *p) {
    adc_init();
    adc_gpio_init(27);
    adc_gpio_init(26);

    // Fator de conversão para 12 bits, assumindo valor máximo == ADC_VREF == 3.3 V
    const float conversion_factor = 3.3f / (1 << 12);

    uint16_t result_1, result_2;
    while (1) {
        // Leitura do potenciômetro no ADC 1 (GP27)
        adc_select_input(1);
        result_1 = adc_read();
        printf("voltage 1: %f V\n", result_1 * conversion_factor);

        // Leitura do potenciômetro no ADC 0 (GP26)
        adc_select_input(0);
        result_2 = adc_read();
        printf("voltage 2: %f V\n", result_2 * conversion_factor);

        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

int main() {
    stdio_init_all();
    printf("Iniciando RTOS\n");
    adc_init();

    xTaskCreate(adc_task, "ADC_Task", 4096, NULL, 1, NULL);
    vTaskStartScheduler();
    
    while (true) {
    }
}

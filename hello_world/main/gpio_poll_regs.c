/*
 * Ejemplo: conmutar un LED periódicamente por polling usando acceso a registros
 * Este ejemplo usa la HAL de bajo nivel `gpio_ll.h` (acceso a registros/bit-fields)
 * para demostrar cómo set/clear/toggle de un GPIO directamente.
 *
 * Nota: Ajusta LED_GPIO_NUM al pin que corresponda en tu placa.
 */

#include <stdint.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"

/* Incluir la HAL de bajo nivel para GPIO (usa las definiciones por SOC) */
#include "hal/gpio_ll.h"

#ifndef LED_GPIO_NUM
// Asumir GPIO2 por defecto (común en muchas placas ESP32)
#define LED_GPIO_NUM 2
#endif

// Delay en ms entre cambios
#define BLINK_DELAY_MS 500

void app_main(void)
{
    // Obtener puntero al periférico GPIO del chip (macro por SOC)
    gpio_dev_t *gpio = GPIO_LL_GET_HW(0);

    // Configurar pin como función GPIO y activarlo como salida usando funciones de bajo nivel
    gpio_ll_func_sel(gpio, LED_GPIO_NUM, PIN_FUNC_GPIO);
    gpio_ll_output_enable(gpio, LED_GPIO_NUM);

    // Asegurarse de que el pin esté inicialmente en 0
    gpio_ll_set_level(gpio, LED_GPIO_NUM, 0);

    while (1) {
        // Leer nivel actual usando la HAL de bajo nivel (portátil entre SOC)
        int level = gpio_ll_get_level(gpio, LED_GPIO_NUM);

        // Conmutar el nivel
        gpio_ll_set_level(gpio, LED_GPIO_NUM, !level);

        // Delay por polling (no recomendado para aplicaciones reales, pero simple para demo)
        vTaskDelay(BLINK_DELAY_MS / portTICK_PERIOD_MS);
    }
}

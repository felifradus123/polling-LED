Ejemplo: Conmutar LED por polling usando registros (gpio_ll)

Descripción
-----------
Este pequeño ejemplo muestra cómo alternar (toggle) un LED periódicamente usando acceso de bajo nivel a los registros GPIO del microcontrolador mediante la HAL `gpio_ll.h`.

Archivos añadidos
- `main/gpio_poll_regs.c`: Código que configura un pin como salida y lo conmuta periódicamente usando registros (W1TS/W1TC si están disponibles).
- `main/CMakeLists.txt`: actualizado para compilar el nuevo archivo.

Uso
---
1. Ajusta el pin del LED en `main/gpio_poll_regs.c` modificando la macro `LED_GPIO_NUM` si tu placa usa otro pin (por ejemplo, 2, 5, 21, etc.).
2. Compilar con el flujo normal de ESP-IDF (por ejemplo, `idf.py build`) desde la carpeta raíz del proyecto.
3. Flashear y abrir monitor serie (`idf.py -p /dev/ttyUSB0 flash monitor`).

Notas técnicas
--------------
- El ejemplo utiliza `gpio_ll.h` y la macro `GPIO_LL_GET_HW(0)` para obtener acceso al periférico de registros GPIO. Esto deja la implementación dependiente del SOC (ESP32/ESP32-Sx/Cx), pero evita hardcodear direcciones absolutas.
- Si el SOC expone registros W1TS/W1TC (`GPIO.out_w1ts`/`GPIO.out_w1tc`), el ejemplo los usa para realizar operaciones atómicas de set/clear. Si no están definidos, hace una lectura-modifica-escritura del registro `out`.
- Este método es didáctico. En aplicaciones reales se recomienda usar las APIs públicas (`driver/gpio.h`) o la HAL con wrappers apropiados, y evitar busy-waiting para conservar energía y permitir multitarea.

Advertencias
-----------
- Acceder directamente a registros puede causar comportamientos no portables si se cambia de SOC o versión de ROM. Asegúrate de revisar las macros disponibles en tu versión de ESP-IDF.
- Siempre respeta las capacidades y restricciones del pin usado (por ejemplo, si es compartido con funciones internas o no disponible al boot).

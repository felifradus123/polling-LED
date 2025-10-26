polling-LED
===========

Demostración simple de conmutación (toggle) de un LED por polling usando ESP‑IDF.
El ejemplo usa acceso de bajo nivel a GPIO a través de `gpio_ll.h` y está
integrado en el proyecto `hello_world/` con el archivo `main/gpio_poll_regs.c`.

Contenido clave
- `hello_world/main/gpio_poll_regs.c`: configura un GPIO como salida y conmuta
	periódicamente su nivel con `vTaskDelay`. Cambia el pin con la macro
	`LED_GPIO_NUM` (por defecto 2).
- `hello_world/main/CMakeLists.txt`: registra el componente para compilar el
	ejemplo de polling.

Requisitos
- ESP‑IDF 5.x/6.x instalado (Windows, Linux o macOS).
- Cable USB de datos y driver USB‑UART de tu placa (CP210x/CH340/FTDI).
- Placa ESP32 (target por defecto del repo: ESP32‑C3; puedes cambiarlo con
	`idf.py set-target`).

Pasos rápidos por plataforma

Windows (recomendado si usas WSL)
1) Abre “ESP‑IDF Command Prompt” (instalado por el setup de ESP‑IDF).
2) Conecta la placa y busca el puerto en el Administrador de dispositivos
	 (ej. CP210x en COM4).
3) Ve al proyecto:
	 - Si el código está en WSL: `cd "\\wsl$\\Ubuntu\\home\\f\\esp\\hello_world"`
	 - Si está en Windows: `cd C:\ruta\al\proyecto\hello_world`
4) (Una sola vez, si tu chip no es el predeterminado) `idf.py set-target esp32c3`
5) Compila y flashea:
	 - `idf.py -p COM4 flash`
	 - `idf.py -p COM4 monitor` para ver la salida. Salir: `Ctrl+]`.

Linux/macOS
1) Exporta el entorno de ESP‑IDF: `. $IDF_PATH/export.sh`
2) Entra en `hello_world/` y compila: `idf.py build`
3) Identifica el puerto serie (ej. `/dev/ttyUSB0` o `/dev/ttyACM0` en Linux;
	 `/dev/cu.usbserial*` o `/dev/cu.usbmodem*` en macOS).
4) Flashea y monitoriza:
	 - `idf.py -p /dev/ttyUSB0 flash monitor`

WSL (si quieres flashear desde WSL)
Por defecto WSL no accede a los puertos COM. Reenvía el USB desde Windows con
`usbipd-win`:
1) En Windows (PowerShell como admin):
	 - `usbipd list` → toma el BUSID del dispositivo (ej. `1-5`).
	 - `usbipd wsl attach --busid <BUSID>`
2) En WSL: verifica `ls /dev/ttyUSB*` (deberías ver `/dev/ttyUSB0`).
3) Flashea: `idf.py -p /dev/ttyUSB0 flash monitor`.

Cambiar el pin del LED
- Edita `hello_world/main/gpio_poll_regs.c` y ajusta `#define LED_GPIO_NUM 2`
	al pin de tu placa (p. ej. 2, 5, 8, 21…). Vuelve a compilar y flashear.

Problemas comunes
- No aparece ningún puerto:
	- Prueba otro cable USB (algunos son solo carga) y otro puerto.
	- Instala el driver del USB‑UART (CP210x/CH340/FTDI) y reinicia.
- “Could not open port / port busy”: cierra otras apps que usan el puerto
	(Arduino IDE, PuTTY, minicom) y vuelve a intentar.
- “Failed to connect” al flashear: entra en modo boot manual (mantén BOOT,
	pulsa RESET, suelta RESET y luego BOOT) y reintenta `idf.py flash`.

Estructura del repo (resumen)
- `hello_world/` → proyecto ESP‑IDF listo para compilar y flashear.
	- `main/gpio_poll_regs.c` → ejemplo de polling del LED.
	- `README_GPIO_POLL.md` → detalles del ejemplo.

Licencia
- Basado en plantillas de ESP‑IDF (ver archivos de licencia dentro de `esp-idf/`).


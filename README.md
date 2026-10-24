# semiautomatic-drone-firmware
This is the ESP32 firmware code for a semi-autonomous guided flying drone, built for the purpose of spraying pesticides/fertilizers for Arecanut tree. The Code is written using C++. Its ESP32-based four-motor control system using Bluetooth gamepad input via Dabble. The system supports manual throttle control, automatic acceleration and deceleration, arecanut detection through serial communication, and pump activation based on detection signals.


## How the code works

**Setup**
- Starts Bluetooth (Dabble) with the name `ESP32_MOTOR`.
- Opens UART2 (9600 baud, RX = GPIO 16, TX = GPIO 17) to receive detection results from the Raspberry Pi 4.
- Attaches 4 ESCs (GPIO 25, 26, 14, 12) at 50 Hz, 1000-2000 µs, and arms them at minimum throttle for 3 seconds.
- Sets the pump pin (GPIO 18) as output, initially LOW.

**Main loop**
1. **Gamepad input (Dabble):**
   - Up / Down: throttle +5 / -5
   - Triangle: emergency stop (throttle to minimum)
   - Cross: starts auto ramp-up (+50 µs every 1 s, up to 1600 µs)
2. **Detection input (UART2):** the Raspberry Pi 4 sends `1` (arecanut detected) or `0` (not detected).
   - On `1`: auto ramp-up stops, the pump turns ON, then the throttle steps down by 50 µs every second.
   - On `0`: nothing happens, only a serial log.
3. **Output:** throttle is clamped to 1000-2000 µs and the same value is written to all 4 ESCs every 20 ms.

## Hardware
ESP32, 4 ESCs + brushless motors, pump with MOSFET/relay, Raspberry Pi 4 (vision/detection, UART link to ESP32).

## Build
Arduino IDE with the ESP32 board package. Libraries: `DabbleESP32`, `ESP32Servo`. Board: ESP32 Dev Module. Test with propellers removed.

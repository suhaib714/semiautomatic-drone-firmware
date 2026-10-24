# semiautomatic-drone-firmware
This is the ESP32 firmware code for a semi-autonomous guided flying drone, built for the purpose of spraying pesticides/fertilizers for Arecanut tree. The Code is written using C++. Its ESP32-based four-motor control system using Bluetooth gamepad input via Dabble. The system supports manual throttle control, automatic acceleration and deceleration, arecanut detection through serial communication, and pump activation based on detection signals.


## How the code works

**Auto climb (Cross).** Pressing Cross button on gamepad starts an automatic ascent. Throttle rises by 50 µs every second, so the drone keeps gaining height without further input. The climb is capped at 1600 µs, which corresponds to the maximum height (the pole height).

**Detection.** A Raspberry Pi 4 runs the automatic arecanut detection and sends `1` (detected) or `0` (not detected) to the ESP32 over UART2 while the drone climbs.

**Spray and auto descent.** When the ESP32 receives `1`:
1. The climb stops immediately, wherever the drone is. The throttle is frozen at its current value, so the drone holds that height and stays stable at that one location.
2. The pump turns on and sprays for 10 seconds.
3. After 10 seconds, the pump turns off and the throttle drops by 50 µs every second, so the drone descends smoothly by itself.
4. The descent ends at minimum throttle (1000 µs).

**Manual control.** The drone can be controlled from a phone using the Dabble Gamepad app over Bluetooth. The ESP32 keeps one shared `throttle` value (1000-2000 µs) and sends it to all four ESCs every loop.
- Up / Down: increase or decrease throttle manually
- Triangle: emergency stop, drops throttle to 1000 µs

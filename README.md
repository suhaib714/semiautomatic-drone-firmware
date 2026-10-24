# semiautomatic-drone-firmware
This is the ESP32 firmware code for a semi-autonomous guided flying drone, built for the purpose of spraying pesticides/fertilizers for Arecanut tree. The Code is written using C++. Its ESP32-based four-motor control system using Bluetooth gamepad input via Dabble. The system supports manual throttle control, automatic acceleration and deceleration, arecanut detection through serial communication, and pump activation based on detection signals.

How it works
Manual flight: a phone running the Dabble Gamepad app connects to the ESP32 (ESP32_MOTOR). Up/Down change throttle, Triangle is the emergency stop, and Cross starts an auto ramp-up (+50 µs every second, up to 1600 µs).
Detection: a separate vision module sends 1 (arecanut detected) or 0 (not detected) over UART2 (9600 baud, RX=GPIO16, TX=GPIO17).
On detection (1): auto ramp-up stops, the pump (GPIO 18) turns on, and then throttle steps down by 50 µs every second.
Motors: all four ESCs (GPIO 25, 26, 14, 12) get the same throttle, 1000-2000 µs at 50 Hz. They are armed at minimum throttle for 3 s on boot.

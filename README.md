# Smart Thermal-Regulating Roller Shade

This project is a closed-loop embedded control system that automatically raises or lowers a roller shade to reduce solar heat gain through a window.

The system uses an ESP32-C3 microcontroller, a DHT11 temperature sensor, a ULN2003A stepper motor driver, and a 28BYJ-48 stepper motor. A custom PCB was designed in KiCad to organize the microcontroller, motor driver, sensor connections, and power wiring.

The goal was to build a practical embedded system that combines sensing, actuation, PCB design, mechanical design, and experimental validation.

---

## Project Overview

The roller shade controller reads the internal air temperature near the window and compares it against a user-defined temperature setpoint.

For this test, the setpoint was:

```text
75°F

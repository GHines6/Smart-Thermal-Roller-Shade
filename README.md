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
```
## Skills Demonstrated

- Embedded C++ firmware development
- ESP32-C3 microcontroller programming
- DHT11 temperature sensor integration
- Stepper motor control with a ULN2003A driver
- Closed-loop thermostat-style control
- KiCad schematic/PCB design
- 3D-printed mechanical mechanism design
- Hardware debugging and validation testing
- Experimental A/B thermal comparison
- Basic controls performance analysis

---

## Hardware Used

| Component | Purpose |
|---|---|
| ESP32-C3 | Main microcontroller |
| DHT11 | Temperature sensor |
| ULN2003A | Stepper motor driver |
| 28BYJ-48 | Stepper motor used to raise/lower the shade |
| Custom PCB | Organizes controller, driver, sensor, and power wiring |
| 3D-printed roller mechanism | Mechanical shade actuation |
| External power supply | Powers the motor/controller system |

---

## Control Logic

The firmware uses a thermostat-style feedback loop.

1. Read temperature from the DHT11 sensor.
2. Compare the measured temperature to the 75°F setpoint.
3. If the temperature is above the setpoint, lower the shade.
4. If the temperature is below the setpoint, raise the shade.
5. Use confirmation counters to avoid reacting to a single noisy reading.

Simplified logic:

```text
if temperature >= setpoint:
    increment lower counter

if temperature < setpoint:
    increment raise counter

if lower counter > 3:
    lower shade

if raise counter > 3:
    raise shade
```

---

## Experimental Validation

The system was tested using a side-by-side A/B comparison.

One enclosure used the active roller shade controller.  
The other enclosure was left unshaded as a baseline.

Setpoint:

```text
75°F
```

### Controlled shaded run

| Metric | Temperature |
|---|---:|
| Start temperature | 76.10°F |
| Average temperature | 75.34°F |
| End temperature | 74.84°F |

### Setpoint tracking

| Metric | Calculation | Result |
|---|---|---:|
| Mean deviation from setpoint | 75.34°F - 75.00°F | +0.34°F |
| Worst-case deviation | 76.10°F - 75.00°F | +1.10°F |
| End-of-run deviation | 74.84°F - 75.00°F | -0.16°F |

The controller held the shaded enclosure within approximately 0.34°F of the setpoint on average and converged to within 0.2°F of the target by the end of the test.

---

## Disturbance Rejection

Percent accuracy based on Fahrenheit temperature was not used because Fahrenheit has an arbitrary zero point. A more meaningful controls metric is disturbance rejection.

The unshaded baseline reached:

```text
88.16°F
```

The uncontrolled excursion above the 75°F target was:

```text
88.16°F - 75.00°F = 13.16°F
```

The controlled average excursion was:

```text
75.34°F - 75.00°F = 0.34°F
```

Average disturbance rejection:

```text
(13.16°F - 0.34°F) / 13.16°F = 0.974
```

So the controller rejected approximately:

```text
97.4%
```

of the measured thermal disturbance on an average-temperature basis.

Using the worst-case controlled deviation:

```text
(13.16°F - 1.10°F) / 13.16°F = 0.916
```

the controller still rejected approximately:

```text
91.6%
```

of the disturbance.

---

## Key Results

- Maintained a 75°F setpoint with an average deviation of +0.34°F.
- Ended the test within -0.16°F of the setpoint.
- Reduced the uncontrolled thermal excursion from 13.16°F to 0.34°F on average.
- Rejected approximately 91.6–97.4% of the measured heat disturbance.
- Demonstrated closed-loop embedded control using real sensor feedback and motorized actuation.

---


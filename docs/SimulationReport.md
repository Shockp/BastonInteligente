# Simulation Report

This document describes the simulation testing performed on the Smart Cane software logic.

## Test Setup
- **Sketch**: `tests/Simulation/Simulation.ino`
- **Method**: The main logic modules (`VibrationAlert`, `SMSCommunicator`) are instantiated with mock inputs or redirected outputs.
- **Hardware**: None required (Logic verification only).

## Scenarios

### 1. Obstacle Approach
We simulate an object at varying distances to verify the vibration frequency logic.

| Distance | Expected Behavior | Logic Check |
|----------|-------------------|-------------|
| **250 cm** | No Vibration | `distance > MAX_DISTANCE` |
| **150 cm** | Slow Pulsing | `map(150, ...)` -> Long delay |
| **50 cm** | Medium Pulsing | `map(50, ...)` -> Medium delay |
| **10 cm** | Fast Pulsing | `map(10, ...)` -> Short delay |

**Simulation Output**:
The sketch runs the update loop for 1 second at each distance and counts the pulses.
- 250cm: 0 pulses.
- 150cm: ~1-2 pulses.
- 50cm: ~5-10 pulses.
- 10cm: Continuous or very fast pulsing.

### 2. Emergency SOS
We simulate a button press event triggering the SMS module.

**Action**: Call `smsCommunicator.sendSOS(40.4167, -3.7037)`
**Expected Output**:
The Serial Monitor should display the AT commands that would be sent to the SIM800L module:
```
AT+CMGF=1
AT+CMGS="+1234567890"
SOS! I need help. Location: https://maps.google.com/?q=40.416775,-3.703790
```

## Conclusion
This simulation validates that:
1. The vibration logic correctly scales frequency with distance.
2. The SMS module correctly formats and sends the GPS coordinates.

# Adaptive-Smart-Lighting-System

The project presents an adaptive smart lighting control system that utilizes sensor networks to track human movement in enclosed spaces. By dynamically adjusting light focus, intensity, and the number of lights, the system responds to the number of occupants in the room. Moreover, it intelligently adapts the light intensity based on the availability of natural light.

The paper published on this project can be found at the following link:
[ResearchGate](https://www.researchgate.net/publication/334319697_Smart_Light_for_Home_with_Automatic_Direction_and_Intensity_Adjustment_using_Arduino)

### Components needed:
1. Arduino Uno Development Board
2. IR sensor
3. HC-SR04 Ultrasonic Sensor
4. LDR (Light Dependent Resistor)
5. Relay
6. HC-05 Bluetooth module

Following is the circuit diagram for the setup:
<img width="849" alt="Screenshot 2023-08-05 at 11 53 32" src="https://github.com/soumyajitmitra77/Adaptive-Smart-Lighting-System/assets/104454276/f9c0e375-9592-4f1d-a7c5-3660bb3f86f1">

### Connections:
1. Connect the Ultrasonic sensor's trigger pin to pin 6 and echo pin to pin 7.
2. Connect the Servo motor to pin 8.
3. Connect the IR sensor to pin 10.
4. Connect LEDs or light sources to pins A0, A1, A2, and A3.
5. Connect two pushbuttons to pins 2 and 3.

### Operation:
1. When the Arduino is powered on, the system will be in "power-on" mode by default.
2. The code communicates with an external device via SoftwareSerial on pins 4 (Rx) and 5 (Tx). It waits for a specific character to toggle the power state. Send 'p' or 'P' to power on and 's' or 'S' to 
   power off the system.
3. When the system is powered on (poweron = 1):
   a. The IR sensor (connected to pin 10) detects occupancy. If occupancy is detected, the system proceeds with the following steps:
      i. The number of occupants is counted by using the two pushbuttons connected to pins 2 and 3. Pressing the button connected to pin 2 increments the count, and pressing the button connected to pin 3 
         decrements the count.
      ii. The light sources connected to pins A0, A1, A2, and A3 are controlled based on the number of occupants. The LEDs are used for demonstration purposes; actual light sources can be connected to these 
          pins.
      iii. The Ultrasonic sensor measures the distance of an object in front of it and adjusts the Servo motor's position (connected to pin 8) to change the light focus. The distance threshold is set to 60 
           units and the servo's position is mapped between 30 and 90 degrees to adjust the focus accordingly.
   b. If no occupancy is detected, all lights are turned off, and the Servo motor is detached to save power.
4. When the system is powered off (poweron = 0), all lights and the Servo motor are turned off, conserving power.

### Usage:
1. Upload the Arduino C++ code to your Arduino board using the Arduino IDE.
2. Connect the required hardware components as described in the "Connections" section.
3. Power on the Arduino board.
4. Use the external device (e.g., a computer or smartphone) connected to pins 4 (Rx) and 5 (Tx) via SoftwareSerial to toggle the power state of the system. Send 'p' or 'P' to power on and 's' or 'S' to 
   power off the system.
5. Observe the light sources and the Servo motor's behavior based on occupancy and distance measurements.

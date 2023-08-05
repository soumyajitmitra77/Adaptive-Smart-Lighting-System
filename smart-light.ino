// Note: This code is a demonstration of the smart lighting control system and is provided without warranty of any kind. To use it in real-world applications, you may need to modify the code and connect actual light sources and sensors as per your requirements.

// Instructions for the Arduino C++ Smart Lighting Control Code:

// Purpose:
// This Arduino code implements a smart lighting control system. The system utilizes various sensors and a servo motor to adjust the light intensity and focus dynamically based on human presence in a confined space. The code also responds to natural light availability and optimizes power consumption to ensure efficient illumination.

// Hardware Requirements:

// Arduino board (e.g., Arduino Uno)
// Ultrasonic sensor (HC-SR04) to measure distance
// Infrared (IR) sensor for occupancy detection
// Servo motor to control light focus
// LEDs or other light sources (connected to pins A0, A1, A2, A3) for demonstration purposes

// Connections:

// Connect the Ultrasonic sensor's trigger pin to pin 6 and echo pin to pin 7.
// Connect the Servo motor to pin 8.
// Connect the IR sensor to pin 10.
// Connect LEDs or light sources to pins A0, A1, A2, and A3.
// Connect two pushbuttons to pins 2 and 3.

// Operation:

// When the Arduino is powered on, the system will be in "power-on" mode by default.
// The code communicates with an external device via SoftwareSerial on pins 4 (Rx) and 5 (Tx). It waits for a specific character to toggle the power state. Send 'p' or 'P' to power on and 's' or 'S' to power off the system.
// When the system is powered on (poweron = 1):
// The IR sensor (connected to pin 10) detects occupancy. If occupancy is detected, the system proceeds with the following steps:
// The number of occupants is counted by using the two pushbuttons connected to pins 2 and 3. Pressing the button connected to pin 2 increments the count, and pressing the button connected to pin 3 decrements the count.
// The light sources connected to pins A0, A1, A2, and A3 are controlled based on the number of occupants. The LEDs are used for demonstration purposes; actual light sources can be connected to these pins.
// The Ultrasonic sensor measures the distance of an object in front of it and adjusts the Servo motor's position (connected to pin 8) to change the light focus. The distance threshold is set to 60 units, and the servo's position is mapped between 30 and 90 degrees to adjust the focus accordingly.
// If no occupancy is detected, all lights are turned off, and the Servo motor is detached to save power.
// When the system is powered off (poweron = 0), all lights and the Servo motor are turned off, conserving power.

// Usage:

// Upload the Arduino C++ code to your Arduino board using the Arduino IDE.
// Connect the required hardware components as described in the "Connections" section.
// Power on the Arduino board.
// Use the external device (e.g., a computer or smartphone) connected to pins 4 (Rx) and 5 (Tx) via SoftwareSerial to toggle the power state of the system. Send 'p' or 'P' to power on and 's' or 'S' to power off the system.
// Observe the light sources and the Servo motor's behavior based on occupancy and distance measurements.


#include<SoftwareSerial.h>
#include<Servo.h>

#define pin2 2
#define pin3 3
#define trigPin 6
#define echoPin 7
#define servo 8
#define gndOutPin 9
#define IR 10
#define highOutPin 11

SoftwareSerial myserial(4,5); /* (Rx,Tx) */
Servo myservo;
volatile boolean IR1;
volatile boolean IR2;
int IR_val = 1;
int pos = 0;
long duration, distance;
int count=0;
int poweron=1;
int pdistance=0;
void myserial_collect();
void ultrasonic_collect();
void IR_check();
void setup()
{
 pinMode(trigPin, OUTPUT); //Ultrasonic
 pinMode(echoPin, INPUT);
 myservo.attach(servo); //Servo
 pinMode(pin2, INPUT);
 pinMode(pin3, INPUT);
 pinMode(13, OUTPUT);
 pinMode(gndOutPin, OUTPUT);
 pinMode(IR, INPUT);
 myserial.begin(9600);
 Serial.begin(9600);
pinMode(A0, OUTPUT);
 pinMode(A1, OUTPUT);
 pinMode(A2, OUTPUT);
 pinMode(A3, OUTPUT);
 pinMode(highOutPin,OUTPUT);
 attachInterrupt(digitalPinToInterrupt(pin2), ISR1,
RISING);
 attachInterrupt(digitalPinToInterrupt(pin3), ISR2,
FALLING);
 digitalWrite(A0,0);
 digitalWrite(A1,0);
 digitalWrite(A2,0);
 digitalWrite(A3,0);
 digitalWrite(highOutPin,0);
 digitalWrite(gndOutPin,1);
}
void loop()
{
 myserial_collect();
 Serial.print("poweron :");
 Serial.println(poweron);
 if(poweron==1)
 {
 Serial.print("cunt :");
 Serial.println(count);
 IR_val=digitalRead(IR);
 IR_check();
 Serial.print("IR :");
 Serial.println(IR_val);
 // digitalWrite(gndOutPin,1);
 //count=1;
 if(count==1)
 {
 digitalWrite(A0,1);
 digitalWrite(A1,0);
 digitalWrite(A2,0);
 digitalWrite(A3,0);
 digitalWrite(gndOutPin,1);
 digitalWrite(highOutPin,1);
 ultrasonic_collect();
 if(distance<60)
 {
 distance = map(distance, 0, 60, 30, 90);
 if(((distance < pdistance+3)&&(distance > pdistance2)))
   {
 myservo.attach(servo);
 myservo.write(distance);
 Serial.println(distance);
 delay(500);
 //myservo.detach();
 }
 pdistance=distance;
 }
 }
 else if((count>1)||(IR_val==1))
 {
 myservo.detach();
 digitalWrite(gndOutPin,0);
 digitalWrite(highOutPin,0);
 if(count==2)
 {
 digitalWrite(A0,1);
 digitalWrite(A1,1);
 digitalWrite(A2,0);
 digitalWrite(A3,0);
 }
else if(count==3)
 {
 digitalWrite(A0,1);
 digitalWrite(A1,1);
 digitalWrite(A2,1);
 digitalWrite(A3,0);
 }
 else if(count==4)
 {
 digitalWrite(A0,1);
 digitalWrite(A1,1);
 digitalWrite(A2,1);
 digitalWrite(A3,1);
 }
 }
 else
 {
 myservo.detach();
 digitalWrite(A0,0);
 digitalWrite(A1,0);
 digitalWrite(A2,0);
 digitalWrite(A3,0);
 digitalWrite(gndOutPin,1);
 digitalWrite(highOutPin,0);
 }
 }
 else
 {
 myservo.detach();
 digitalWrite(A0,0);
 digitalWrite(A1,0);
 digitalWrite(A2,0);
 digitalWrite(A3,0);
 digitalWrite(gndOutPin,1);
 digitalWrite(highOutPin,0);
 }
 //delay(1000);
}
void ultrasonic_collect()
{
 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 distance = (duration/2) / 29.1;
 Serial.println(distance);
 //Serial.println("--------------");
}
void myserial_collect()
{
 if (myserial.available())
 {
 //Serial.println(myserial.read());
 //while(1);
 int x=0;
 char c=myserial.read();
 do
 {
 x=myserial.read();
 }while(x>0);

 if(c=='p' || c=='P')
 poweron=1;
 else if(c=='s' || c=='S')
 poweron=0;
 }
}void ISR1(){
 IR1=1;
 Serial.println("-------ISR1-------");
 delay(2000);
}
void ISR2(){
 IR2=1;
 Serial.println("------ISR2--------");
// IR_check();
 delay(2000);
}
void IR_check()
{
 if(IR1 && (count<4))
 {
 int cnt=50;
 while(!IR2 && cnt-- ){delay(1000);}
 if(IR2)
 {
 count=count+1;
 IR1=0;
 IR2=0;
}
 else
 {
 IR1=0;
 }
 }
 else if(IR2 && (count>0))
 {
 int cnt=50;
 while(!IR1 && cnt--){delay(1000);}
 if(IR1)
 {
 count=count-1;
 IR1=0;
 IR2=0;
 }
 else
 {
 IR2=0;
 }
 }
}

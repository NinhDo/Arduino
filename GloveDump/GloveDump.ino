#include <Servo.h>
#define servo0port 2
#define servo1port 3
#define servo2port 4
#define servo3port 5
#define servo4port 6
#define servo5port 7

#define pot0port A0
#define pot1port A1
#define pot2port A2
#define pot3port A3
#define pot4port A4
#define pot5port A5

#define pot0min 100
#define pot1min 100
#define pot2min 100
#define pot3min 100
#define pot4min 500
#define pot5min 100

#define pot0max 900
#define pot1max 900
#define pot2max 900
#define pot3max 900
#define pot4max 600
#define pot5max 900

Servo servo0;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

int pot0Value = 0;
int pot1Value = 0;
int pot2Value = 0;
int pot3Value = 0;
int pot4Value = 0;
int pot5Value = 0;

void setup() {
  servo0.attach(servo0port);
  servo1.attach(servo1port);
  servo2.attach(servo2port);
  servo3.attach(servo3port);
  servo4.attach(servo4port);
  servo5.attach(servo5port);
  Serial.begin(9600);
}

void loop() {
	// Read values of potentiometers
	pot0Value = analogRead(pot0port);
	pot1Value = analogRead(pot1port);
	pot2Value = analogRead(pot2port);
	pot3Value = analogRead(pot3port);
	pot4Value = analogRead(pot4port);
	pot5Value = analogRead(pot5port);

	// Map potentiovalues to servo degrees
	pot0Value = map(pot0Value, pot0min, pot0max, 10, 170);
	pot1Value = map(pot1Value, pot1min, pot1max, 10, 170);
	pot2Value = map(pot2Value, pot2min, pot2max, 10, 170);
	pot3Value = map(pot3Value, pot3min, pot3max, 10, 170);
	pot4Value = map(pot4Value, pot4min, pot4max, 10, 170);
	pot5Value = map(pot5Value, pot5min, pot5max, 10, 170);

	// Constrain potentiovalues to servo degrees
	pot0Value = constrain(pot0Value, 10, 170);
	pot1Value = constrain(pot1Value, 10, 170);
	pot2Value = constrain(pot2Value, 10, 170);
	pot3Value = constrain(pot3Value, 10, 170);
	pot4Value = constrain(pot4Value, 10, 170);
	pot5Value = constrain(pot5Value, 10, 170);
	// Write servoes
	servo0.write(pot0Value);
	servo1.write(pot1Value);
	servo2.write(pot2Value);
	servo3.write(pot3Value);
	servo4.write(pot4Value);
	servo5.write(pot5Value);

	Serial.print(pot0Value);
	Serial.print(" ");
	Serial.print(pot1Value);
	Serial.print(" ");
	Serial.print(pot2Value);
	Serial.print(" ");
	Serial.print(pot3Value);
	Serial.print(" ");
	Serial.print(pot4Value);
	Serial.print(" ");
	Serial.print(pot5Value);
	Serial.println();

	delay(10);
}

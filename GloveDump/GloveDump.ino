#include <Servo.h>
#define servo0port 2
#define servo1port 3
#define servo2port 4
#define servo3port 5
#define servo4port 6
#define servo5port 7

#define pot0port A0
#define pot0port A1
#define pot0port A2
#define pot0port A3
#define pot0port A4
#define pot0port A5

#define pot0min 100
#define pot1min 100
#define pot2min 100
#define pot3min 100
#define pot4min 100
#define pot5min 100

#define pot0max 900
#define pot1max 900
#define pot2max 900
#define pot3max 900
#define pot4max 900
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
	pot0Value = map(pot0Value, pot0min, pot0max, 0, 180);
	pot1Value = map(pot1Value, pot1min, pot1max, 0, 180);
	pot2Value = map(pot2Value, pot2min, pot2max, 0, 180);
	pot3Value = map(pot3Value, pot3min, pot3max, 0, 180);
	pot4Value = map(pot4Value, pot4min, pot4max, 0, 180);
	pot5Value = map(pot5Value, pot5min, pot5max, 0, 180);
	
	// Write servoes
	servo0.write(pot0Value);
	servo1.write(pot1Value);
	servo2.write(pot2Value);
	servo3.write(pot3Value);
	servo4.write(pot4Value);
	servo5.write(pot5Value);
	delay(10);
}

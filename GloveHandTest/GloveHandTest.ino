#include <Servo.h>

Servo servo;
Servo servo2;

const int servoPort = 12;
const int servoPort2 = 13;
const int potPort = A0;

int val;

void setup() {
	Serial.begin(9600);
	servo.attach(servoPort);
	servo2.attach(servoPort2);
}

void loop() {
	val = analogRead(potPort);
	Serial.println(val);
	val = constrain(val, 200, 1000);
	val = map(val, 200, 1000, 0, 180);
	val = constrain(val, 0, 180);
	servo.write(val);
	servo2.write(180-val);
	delay(15);
}
#include <Servo.h>

Servo servo;
const int servoport = 4;
const int potport = A0;

int potValue = 0;

void setup() {
  servo.attach(servoport);
}

void loop() {
	potValue = analogRead(potport);
	potValue = map(potValue, 100, 900, 0, 180);
	potValue = constrain(potValue, 0, 180);
	servo.write(potValue);
	delay(10);
}

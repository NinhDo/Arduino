#include <Servo.h>


// Constant Variables
const int wG = 2;
const int wR = 3;
const int cG = 4;
const int cY = 5;
const int cR = 6;
const int button = 7;
const int servoPort = 8;
const int one = 1000;
const int buzzer = 9;

// Variables
boolean buttonState = false;
int angle = 0;
Servo servo;


void setup() {
	for (int i = 2; i < 7; i++) {
		pinMode(i, OUTPUT);
		digitalWrite(i, LOW);
	}
	pinMode(button, INPUT);
	pinMode(buzzer, OUTPUT);
	digitalWrite(cG, HIGH);
	digitalWrite(wR, HIGH);
	servo.attach(servoPort);
	servo.write(0);
}

void loop() {
	buttonState = digitalRead(button);
	
	/*
	// DELOPPGAVE A
	for (int i = 2; i < 7; i++) {
		digitalWrite(i, HIGH);
		delay(500);
		digitalWrite(i, LOW);
		delay(100);
	}
	*/
	/*
	// DELOPPGAVE B
	if (buttonState) {
		for(int i = 2; i < 7; i++) {
			digitalWrite(i, HIGH);
		}
	} else {
		for (int i = 2; i < 7; i++) {
			digitalWrite(i, LOW);
		}
	}
	*/
	/*
	// DELOPPGAVE C
	if(buttonState) {
		carToRed();
		walkToGreen();
		walkToRed();
		carToGreen();
	}
	*/

	// Deloppgave D
	if(buttonState) {
		carToRed();
		walkToGreen();
		arm(true);
		walkToRedBuzzer();
		arm(false);
		carToGreen();
	}
}

void carToGreen() {
	delay(one * 2);
	digitalWrite(cY, HIGH);
	delay(one);
	digitalWrite(cR, LOW);
	digitalWrite(cY, LOW);
	digitalWrite(cG, HIGH);
}

void carToRed() {
	delay(one);
	digitalWrite(cG, LOW);
	digitalWrite(cY, HIGH);
	delay(one);
	digitalWrite(cY, LOW);
	digitalWrite(cR, HIGH);
}

void walkToRed() {
	delay(one * 5);
	digitalWrite(wR, HIGH);
	digitalWrite(wG, LOW);
}

void walkToRedBuzzer() {
	for(int i = 0; i < 50; i++) {
		buzz(100);
	}
	digitalWrite(wR, HIGH);
	digitalWrite(wG, LOW);
}

void walkToGreen() {
	delay(one * 2);
	digitalWrite(wR, LOW);
	digitalWrite(wG, HIGH);
}

void arm(boolean lift) {
	lift?servo.write(90):servo.write(0);
}

void buzz(int time) {
	tone(buzzer, 440, time);
	delay(time * 1.5);
	noTone(buzzer);
}
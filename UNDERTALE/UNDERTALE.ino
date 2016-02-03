#include <Wire.h>
#include <pitches.h>

// Constant variables
const int buzzer = 4;

void setup() {
	Serial.begin(9600);
	Wire.begin(8);
	Wire.onReceive(receiveEvent);
	pinMode(buzzer, OUTPUT);
	noTone(buzzer);
}

void loop() {

	delay(150);
}

void receiveEvent(int howMany) {
	unsigned int note = Wire.read();
	Serial.println(note);
	noTone(buzzer);
	if(note != 0) tone(buzzer, note);
}

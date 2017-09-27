#include <HID.h>
#include <Keyboard.h>

#define input 2
#define PAUSE 207

boolean button;

void setup() {
	pinMode(2, INPUT);
	Keyboard.end();	
	Keyboard.begin();
}

void loop() {
	button = digitalRead(input);
	Serial.println(button);
	if (button) {
		Keyboard.press(PAUSE);
	} else {
		Keyboard.release(PAUSE);
	}
	delay(10);
}
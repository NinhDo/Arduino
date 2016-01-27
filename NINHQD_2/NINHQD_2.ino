#include <pitches.h>

// Constant variables
const int speaker = 2;
const int trigPin = 4;
const int echoPin = 3;

// Variables

// NOTES
int C[] = { NOTE_C1, NOTE_C2, NOTE_C3, NOTE_C4, NOTE_C5, NOTE_C6, NOTE_C7 };
int D[] = { NOTE_D1, NOTE_D2, NOTE_D3, NOTE_D4, NOTE_D5, NOTE_D6, NOTE_D7 };
int E[] = { NOTE_E1, NOTE_E2, NOTE_E3, NOTE_E4, NOTE_E5, NOTE_E6, NOTE_E7 };
int F[] = { NOTE_F1, NOTE_F2, NOTE_F3, NOTE_F4, NOTE_F5, NOTE_F6, NOTE_F7 };
int G[] = { NOTE_G1, NOTE_G2, NOTE_G3, NOTE_G4, NOTE_G5, NOTE_G6, NOTE_G7 };
int A[] = { NOTE_A1, NOTE_A2, NOTE_A3, NOTE_A4, NOTE_A5, NOTE_A6, NOTE_A7 };
int B[] = { NOTE_B1, NOTE_B2, NOTE_B3, NOTE_B4, NOTE_B5, NOTE_B6, NOTE_B7 };

int CS[] = { NOTE_CS1, NOTE_CS2, NOTE_CS3, NOTE_CS4, NOTE_CS5, NOTE_CS6, NOTE_CS7 };
int DS[] = { NOTE_DS1, NOTE_DS2, NOTE_DS3, NOTE_DS4, NOTE_DS5, NOTE_DS6, NOTE_DS7 };
int FS[] = { NOTE_FS1, NOTE_FS2, NOTE_FS3, NOTE_FS4, NOTE_FS5, NOTE_FS6, NOTE_FS7 };
int GS[] = { NOTE_GS1, NOTE_GS2, NOTE_GS3, NOTE_GS4, NOTE_GS5, NOTE_GS6, NOTE_GS7 };
int AS[] = { NOTE_AS1, NOTE_AS2, NOTE_AS3, NOTE_AS4, NOTE_AS5, NOTE_AS6, NOTE_AS7 };

int notes[] = { NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4, 
	NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, NOTE_B5 };

int maximumRange = 50; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance
int dMap = 0;
int counter = 0;
int five[5];
int avg;
int lastNote;

void setup() {
	pinMode(speaker, OUTPUT);
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
	Serial.begin(9600);
	for(int i = 0; i < 5; i++) {
		five[i] = 0;
	}
}

void loop() { 
	digitalWrite(trigPin, LOW); 
	delay(2); 

	digitalWrite(trigPin, HIGH);
	delay(10); 

	digitalWrite(trigPin, LOW);
	duration = pulseIn(echoPin, HIGH);

	distance = duration/58.2;

	if (distance >= maximumRange || distance <= minimumRange){
		Serial.println("-1");
		noTone(speaker);
	}
	else {
		Serial.println(distance);
		dMap = map(distance, 0, 47, 0, sizeof(notes));
		dMap = constrain(distance, 0, 23);
		five[counter % 5] = dMap;
		for(int i = 0; i < 5; i++) {
			avg += five[i];
		}
		avg /= 5;
		if (lastNote != notes[avg]) playNote(notes[avg]);
		counter++;
	}
}

void playNote(int note) {
	noTone(speaker);
	tone(speaker, note);
	//delay(1000 / length * 1.3);
	//noTone(speaker);
	lastNote = note;
}
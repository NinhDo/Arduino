#include <pitches.h>

// Constant variables
const int speaker = 2;

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

void setup() {
	pinMode(speaker, OUTPUT);
}

void loop() {
	for(int i = 0; i < 2; i++) {
		playNote(AS[3], 4);
		playNote(F[4], 4);
		playNote(DS[4], 4);
		playNote(AS[3], 4);
		playNote(D[4], 3);
		playNote(D[4], 3);
		playNote(DS[4], 2);

		playNote(AS[3], 4);
		playNote(DS[4], 4);
		playNote(AS[3], 4);
		playNote(D[4], 3);
		playNote(D[4], 3);
		playNote(DS[4], 4);

		playNote(AS[3], 4);
		playNote(F[4], 4);
		playNote(DS[4], 4);
		playNote(AS[3], 4);
		playNote(D[4], 3);
		playNote(D[4], 3);
		playNote(DS[4], 2);

		playNote(AS[3], 4);
		playNote(DS[4], 4);
		playNote(G[4], 4);
		playNote(F[4], 3);
		playNote(DS[4], 3);
		playNote(F[4], 4);
	}

	delay(1000);
}

void playNote(int note, float length) {
	tone(speaker, note, 1000/ length);
	delay(1000 / length * 1.3);
	noTone(speaker);
}
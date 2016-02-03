#include <Wire.h>
#include <pitches.h>

// Constant variables
const int speaker = 2;

const int full = 4000;
const int half = 2000;
const int halfDotted = 3000;
const int fourth = 1000;
const int fourthDotted = 1500;
const int fourthDoubleDotted = 1750;
const int eighth = 500;
const int eighthDotted = 750;
const int sixteenth = 250;
const int thirthysecond = 125;

// NOTES
const unsigned int rest = 0;

const unsigned int speakerNotes[] = {
	C4, C5, G4, 
	F4, C5, C4, 
	C4, F4, C5, D5, 
	C5, G4, F4,
	C4, C5, G4,
	F4, C5, C4,
	C4, F4, C5, D5,
	C5, G4, F4, A3, AS3
};

const int speakerRhythm[] = {
	fourth, fourth, half, 
	fourth, fourth, half, 
	fourth, fourth, fourth, fourth, 
	fourth, fourth, half, 
	fourth, fourth, half,
	fourth, fourth, half,
	fourth, fourth, fourth, fourth, 
	fourth, fourth, fourthDoubleDotted, thirthysecond, thirthysecond
};

const unsigned int blueNotes[] = {
	F3, A3,
	GS3, G3,
	F3, A3,
	GS3, G3,
	F3, A3,
	GS3, G3,
	F3, A3,
	GS3, G3, rest
};

const unsigned int blueRhythm[] = {
	half, half, 
	half, half, 
	half, half, 
	half, half, 
	half, half, 
	half, half, 
	half, half, 
	half, fourthDoubleDotted, sixteenth
};

// Variables
int speakerPlayingLength = eighth;
int bluePlayingLength = 0;

int speakerPlayingDuration = 0;
int bluePlayingDuration = 0;

uint8_t speakerCounter = 0;
uint8_t blueCounter = 0;

boolean start = false;

void setup() {
	Serial.begin(9600);
	pinMode(speaker, OUTPUT);
	Wire.begin(8);
}

void loop() {
	/*playSpeaker(speakerNotes[speakerCounter], speakerRhythm[speakerCounter]);
	playBlue(blueNotes[blueCounter], blueRhythm[blueCounter]);
	delay(thirthysecond);
	speakerPlayingDuration += thirthysecond;
	bluePlayingDuration += thirthysecond;*/

	playAndSend(C4, F3);
	delay(fourth);
	
	playAndSend(C5, 0, true, false);
	delay(fourth);

	playAndSend(G4, A3);
	delay(half);
	/*1*/

	playAndSend(F4, GS3);
	delay(fourth);

	playAndSend(C5, 0, true, false);
	delay(fourth);

	playAndSend(C4, G3);
	delay(half);
	/*2*/

	playAndSend(C4, F3);
	delay(fourth);

	playAndSend(F4, 0, true, false);
	delay(fourth);

	playAndSend(C5, A3);
	delay(fourth);

	playAndSend(D5, 0, true, false);
	delay(fourth);
	/*3*/

	playAndSend(C5, GS3);
	delay(fourth);

	playAndSend(G4, 0, true, false);
	delay(fourth);

	playAndSend(F4, G3);
	delay(fourthDoubleDotted);

	playAndSend(rest, rest);
	delay(sixteenth);
	/*4*/

	playAndSend(C4, F3);
	delay(fourth);

	playAndSend(C5, 0, true, false);
	delay(fourth);

	playAndSend(G4, A3);
	delay(half);
	/*5*/

	playAndSend(F4, GS3);
	delay(fourth);

	playAndSend(C5, 0, true, false);
	delay(fourth);

	playAndSend(C4, G3);
	delay(half);
	/*6*/

	playAndSend(C4, F3);
	delay(fourth);

	playAndSend(F4, 0, true, false);
	delay(fourth);

	playAndSend(C5, A3);
	delay(fourth);

	playAndSend(D5, 0, true, false);
	delay(fourth);
	/*7*/

	playAndSend(C5, GS3);
	delay(fourth);

	playAndSend(G4, 0, true, false);
	delay(fourth);

	playAndSend(F4, G3);
	delay(fourthDoubleDotted);

	playAndSend(A3, rest);
	delay(thirthysecond);

	playAndSend(AS3, 0, true, false);
	delay(thirthysecond);
	/*8*/

	playAndSend(C4, A2); //????
	delay(eighth);

	playAndSend(0, F3, false, true);
	delay(eighth);

	playAndSend(C5, G3);
	delay(eighth);

	playAndSend(A4, F3);
	delay(eighth);

	playAndSend(G4, A2); //????
	delay(eighth);

	playAndSend(F4, F3);
	delay(eighth);
	
	playAndSend(E4, G3);
	delay(eighth);
	
	playAndSend(F4, F3);
	delay(eighth);
	/*9*/

	playAndSend(G4, G2); //????
	delay(eighth);

	playAndSend(0, F3, false, true);
	delay(eighth);

	playAndSend(E5, G3);
	delay(eighth);

	playAndSend(DS5, F3);
	delay(sixteenth);

	playAndSend(D5, 0, true, false);
	delay(sixteenth);

	playAndSend(C5, FS2); //????
	delay(eighth);

	playAndSend(0, F3, false, true);
	delay(eighth);

	playAndSend(0, G3, false, true);
	delay(eighth);

	playAndSend(0, F3, false, true);
	delay(eighth);
	/*10*/

	playAndSend(D4, 0);
	delay(eighth);

	playAndSend(0, 0, false, true);
	delay(eighth);

	playAndSend(C5, 0);
	delay(eighth);

	playAndSend(A4, 0);
	delay(eighth);

	playAndSend(G4, 0);
	delay(eighth);

	playAndSend(F4, 0);
	delay(eighth);

	playAndSend(G4, 0);
	delay(eighth);

	playAndSend(A4, 0);
	delay(eighth);
	/*11*/

	playAndSend(E4, 0);
	delay(eighth);

	playAndSend(0, 0, false, true);
	delay(eighth);

	playAndSend(G4, 0);
	delay(eighth);

	playAndSend(0, 0);
	delay(eighth);

	playAndSend(G4, 0);
	delay(eighth);

	playAndSend(F4, 0);
	delay(eighth);

	playAndSend(E4, 0);
	delay(eighth);

	playAndSend(F4, 0);
	delay(eighth);
	/*12*/

	playAndSend(C4, 0);
	delay(eighth);

	playAndSend(0, 0, false, true);
	delay(eighth);

	playAndSend(C5, 0);
	delay(eighth);

	playAndSend(A4, 0);
	delay(eighth);

	playAndSend(G4, 0);
	delay(eighth);

	playAndSend(F4, 0);
	delay(eighth);

	playAndSend(E4, 0);
	delay(eighth);

	playAndSend(F4, 0);
	delay(eighth);
	/*13*/

	playAndSend(G4, G2); //????
	delay(eighth);

	playAndSend(0, F3, false, true);
	delay(eighth);

	playAndSend(E5, G3);
	delay(eighth);

	playAndSend(DS5, F3);
	delay(sixteenth);

	playAndSend(D5, 0, true, false);
	delay(sixteenth);

	playAndSend(C5, FS2); //????
	delay(eighth);

	playAndSend(0, F3, false, true);
	delay(eighth);

	playAndSend(0, G3, false, true);
	delay(eighth);

	playAndSend(0, F3, false, true);
	delay(eighth);
	/*14*/

	playAndSend(D4, 0);
	delay(eighth);

	playAndSend(0, 0, false, true);
	delay(eighth);

	playAndSend(C5, 0);
	delay(eighth);

	playAndSend(A4, 0);
	delay(eighth);

	playAndSend(G4, 0);
	delay(eighth);

	playAndSend(F4, 0);
	delay(eighth);

	playAndSend(G4, 0);
	delay(eighth);

	playAndSend(A4, 0);
	delay(eighth);
	/*15*/

	playAndSend(E4, 0);
	delay(eighth);

	playAndSend(0, 0, false, true);
	delay(eighth);

	playAndSend(G4, 0);
	delay(eighth);

	playAndSend(0, 0, false, true);
	delay(eighth);

	playAndSend(G4, 0);
	delay(eighth);

	playAndSend(F4, 0);
	delay(eighth);

	playAndSend(E4, 0);
	delay(eighth);

	playAndSend(F4, 0);
	delay(eighth);
	/*16*/


}

void playSpeaker(unsigned int note, unsigned int length) {
	if (speakerPlayingDuration >= speakerPlayingLength) {
		Serial.println(note);
		speakerCounter++;
		noTone(speaker);
		tone(speaker, note);
		speakerPlayingDuration = 0;
		speakerPlayingLength = length;
	}
}

void playBlue(unsigned int note, unsigned int length) {
	if (bluePlayingDuration >= bluePlayingLength) {
		blueCounter++;
		Serial.println("SENDING");
		Wire.beginTransmission(8);
		Wire.write(note);
		Wire.endTransmission();
		bluePlayingDuration = 0;
		bluePlayingLength = length;
	}
}

void playAndSend(unsigned int playNote, unsigned int sendNote, boolean playB, boolean sendB) {
	if (playB) play(playNote);
	if (sendB) send(sendNote);
}

void playAndSend(unsigned int playNote, unsigned int sendNote) {
	play(playNote);
	send(sendNote);
}


void play(unsigned int note) {
	noTone(speaker);
	tone(speaker, note);
}

void send(unsigned int note) {
	Wire.beginTransmission(8);
	Wire.write(note);
	Wire.endTransmission(8);
}

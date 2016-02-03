//** ReacXion Source Code **//
//** www.jeremyblum.com **//

#include <pitches.h>

/* Timer reload value, globally available */
unsigned int tcnt2;

/* Toggle HIGH or LOW digital write */
int toggle1 = 0;
int toggle2 = 0;
int toggle3 = 0;

/* Keep track of when each note needs to be switched */
int count1 = 0;
int count2 = 0;
int count3 = 0;

/* Frequency Output Pins */
#define FREQ1 2
#define FREQ2 4
#define FREQ3 7


// Constant variables
const int speaker = 2;
const int buzzerBlue = 7;
const int buzzerYellow = 4;

const int full = 2400;
const int half = 1200;
const int halfDotted = 1800;
const int fourth = 600;
const int fourthDotted = 900;
const int eighth = 300;
const int eighthDotted = 450;
const int sixteenth = 150;

// NOTES
const int C[] = { 0, NOTE_C1, NOTE_C2, NOTE_C3, NOTE_C4, NOTE_C5, NOTE_C6, NOTE_C7 };
const int D[] = { 0, NOTE_D1, NOTE_D2, NOTE_D3, NOTE_D4, NOTE_D5, NOTE_D6, NOTE_D7 };
const int E[] = { 0, NOTE_E1, NOTE_E2, NOTE_E3, NOTE_E4, NOTE_E5, NOTE_E6, NOTE_E7 };
const int F[] = { 0, NOTE_F1, NOTE_F2, NOTE_F3, NOTE_F4, NOTE_F5, NOTE_F6, NOTE_F7 };
const int G[] = { 0, NOTE_G1, NOTE_G2, NOTE_G3, NOTE_G4, NOTE_G5, NOTE_G6, NOTE_G7 };
const int A[] = { 0, NOTE_A1, NOTE_A2, NOTE_A3, NOTE_A4, NOTE_A5, NOTE_A6, NOTE_A7 };
const int B[] = { 0, NOTE_B1, NOTE_B2, NOTE_B3, NOTE_B4, NOTE_B5, NOTE_B6, NOTE_B7 };

const int CS[] = { 0, NOTE_CS1, NOTE_CS2, NOTE_CS3, NOTE_CS4, NOTE_CS5, NOTE_CS6, NOTE_CS7 };
const int DS[] = { 0, NOTE_DS1, NOTE_DS2, NOTE_DS3, NOTE_DS4, NOTE_DS5, NOTE_DS6, NOTE_DS7 };
const int FS[] = { 0, NOTE_FS1, NOTE_FS2, NOTE_FS3, NOTE_FS4, NOTE_FS5, NOTE_FS6, NOTE_FS7 };
const int GS[] = { 0, NOTE_GS1, NOTE_GS2, NOTE_GS3, NOTE_GS4, NOTE_GS5, NOTE_GS6, NOTE_GS7 };
const int AS[] = { 0, NOTE_AS1, NOTE_AS2, NOTE_AS3, NOTE_AS4, NOTE_AS5, NOTE_AS6, NOTE_AS7 };
const int rest = 0;

const int speakerNotes[] = {
	AS[4], F[5], DS[5], AS[4], D[5], D[5], DS[5],
	AS[4], DS[5], AS[4], D[5], D[5], DS[5],
	AS[4], F[5], DS[5], AS[4], D[5], D[5], DS[5],
	AS[4], DS[5], G[5], F[5], DS[5], F[5],
	AS[4], F[5], DS[5], AS[4], D[5], D[5], DS[5],
	AS[4], DS[5], AS[4], D[5], D[5], DS[5],
	AS[4], F[5], DS[5], AS[4], D[5], D[5], DS[5],
	AS[4], DS[5], G[5], F[5], DS[5], F[5],

	AS[4], F[5], DS[5], AS[4], D[5], D[5], DS[5],
	AS[4], DS[5], AS[4], D[5], D[5], DS[5],
	AS[4], F[5], DS[5], AS[4], D[5], D[5], DS[5],
	AS[4], DS[5], G[5], F[5], DS[5], F[5],
	AS[4], F[5], DS[5], AS[4], D[5], D[5], DS[5],
	AS[4], DS[5], AS[4], D[5], D[5], DS[5],
	AS[4], F[5], DS[5], AS[4], D[5], D[5], DS[5],
	AS[4], DS[5], G[5], F[5], DS[5], F[5],

	AS[4], F[5], DS[5], AS[4], D[5], D[5], DS[5],
	AS[4], DS[5], AS[4], D[5], D[5], DS[5],
	AS[4], F[5], DS[5], AS[4], D[5], D[5], DS[5],
	AS[4], DS[5], G[5], F[5], DS[5], F[5],
	AS[4], F[5], DS[5], AS[4], D[5], D[5], DS[5],
	AS[4], DS[5], AS[4], D[5], D[5], DS[5],
	AS[4], F[5], DS[5], AS[4], D[5], D[5], DS[5],
	AS[4], DS[5], G[5], F[5], DS[5], F[5],

	AS[4], F[5], DS[5], AS[4], D[5], D[5], DS[5],
	AS[4], DS[5], AS[4], D[5], D[5], DS[5],
	AS[4], F[5], DS[5], AS[4], D[5], D[5], DS[5],
	AS[4], DS[5], G[5], F[5], DS[5], F[5],
	AS[4], F[5], DS[5], AS[4], D[5], D[5], DS[5],
	AS[4], DS[5], AS[4], D[5], D[5], DS[5],
	AS[4], F[5], DS[5], AS[4], D[5], D[5], DS[5],
	AS[4], DS[5], G[5], F[5], DS[5], F[5]
};

const int speakerRhythm[] = {
	eighth, eighth, eighth, eighth, eighthDotted, eighthDotted, fourth,
	eighth, eighth, eighth, eighthDotted, eighthDotted, eighth,
	eighth, eighth, eighth, eighth, eighthDotted, eighthDotted, fourth,
	eighth, eighth, eighth, eighthDotted, eighthDotted, eighth,
	eighth, eighth, eighth, eighth, eighthDotted, eighthDotted, fourth,
	eighth, eighth, eighth, eighthDotted, eighthDotted, eighth,
	eighth, eighth, eighth, eighth, eighthDotted, eighthDotted, fourth,
	eighth, eighth, eighth, eighthDotted, eighthDotted, eighth,

	eighth, eighth, eighth, eighth, eighthDotted, eighthDotted, fourth,
	eighth, eighth, eighth, eighthDotted, eighthDotted, eighth,
	eighth, eighth, eighth, eighth, eighthDotted, eighthDotted, fourth,
	eighth, eighth, eighth, eighthDotted, eighthDotted, eighth,
	eighth, eighth, eighth, eighth, eighthDotted, eighthDotted, fourth,
	eighth, eighth, eighth, eighthDotted, eighthDotted, eighth,
	eighth, eighth, eighth, eighth, eighthDotted, eighthDotted, fourth,
	eighth, eighth, eighth, eighthDotted, eighthDotted, eighth,


	eighth, eighth, eighth, eighth, eighthDotted, eighthDotted, fourth,
	eighth, eighth, eighth, eighthDotted, eighthDotted, eighth,
	eighth, eighth, eighth, eighth, eighthDotted, eighthDotted, fourth,
	eighth, eighth, eighth, eighthDotted, eighthDotted, eighth,
	eighth, eighth, eighth, eighth, eighthDotted, eighthDotted, fourth,
	eighth, eighth, eighth, eighthDotted, eighthDotted, eighth,
	eighth, eighth, eighth, eighth, eighthDotted, eighthDotted, fourth,
	eighth, eighth, eighth, eighthDotted, eighthDotted, eighth,

	eighth, eighth, eighth, eighth, eighthDotted, eighthDotted, fourth,
	eighth, eighth, eighth, eighthDotted, eighthDotted, eighth,
	eighth, eighth, eighth, eighth, eighthDotted, eighthDotted, fourth,
	eighth, eighth, eighth, eighthDotted, eighthDotted, eighth,
	eighth, eighth, eighth, eighth, eighthDotted, eighthDotted, fourth,
	eighth, eighth, eighth, eighthDotted, eighthDotted, eighth,
	eighth, eighth, eighth, eighth, eighthDotted, eighthDotted, fourth,
	eighth, eighth, eighth, eighthDotted, eighthDotted, eighth
};

const int blueNotes[] = {
	rest, DS[2], DS[2], DS[2], DS[2], DS[2], DS[2], DS[2], DS[2],
	DS[2], DS[2], DS[2], DS[2], DS[2], DS[2], DS[2], DS[2],
	DS[2], DS[2], DS[2], DS[2], DS[2], DS[2], DS[2], DS[2], DS[2],
	DS[2], DS[2], DS[2], DS[2], DS[2], DS[2], DS[2], DS[2],
};

const int blueRhythm[] = {
	eighth, fourth, fourth, fourth, fourth, fourth, fourth, fourth, fourth,
	fourth, fourth, fourth, fourth, fourth, fourth, fourth, eighth,
	eighth, fourth, fourth, fourth, fourth, fourth, fourth, fourth, fourth,
	fourth, fourth, fourth, fourth, fourth, fourth, fourth, eighth,

};

const int yellowNotes[] = {
	rest, rest, rest, rest, rest, rest, rest, rest,
	rest, rest, rest, rest, rest, rest, rest, rest,

};

const int yellowRhythm[] = {
	full, full, full, full, full, full, full, full,
	full, full, full, full, full, full, full, full,

};

// Variables
int speakerPlayingLength = eighth;
int bluePlayingLength = 0;
int yellowPlayingLength = 0;

int speakerPlayingDuration = 0;
int bluePlayingDuration = 0;
int yellowPlayingDuration = 0;

int speakerPlayingNote = 0;
int bluePlayingNote = 0;
int yellowPlayingNote = 0;

uint8_t speakerCounter = 0;
uint8_t blueCounter = 0;
uint8_t yellowCounter = 0;

//Setup Function will run once at initialization
void setup() {

	/* First disable the timer overflow interrupt*/
	TIMSK2 &= ~(1 << TOIE2);

	/* Configure timer2 in normal mode (no PWM) */
	TCCR2A &= ~((1 << WGM21) | (1 << WGM20));
	TCCR2B &= ~(1 << WGM22);

	/* Select clock source: internal I/O clock */
	ASSR &= ~(1 << AS2);

	/* Disable Compare Match A interrupt (only overflow) */
	TIMSK2 &= ~(1 << OCIE2A);

	/* Configure the prescaler to CPU clock divided by 128 */
	TCCR2B |= (1 << CS22) | (1 << CS20); // Set bits
	TCCR2B &= ~(1 << CS21);             // Clear bit

										/* We need to calculate a proper value to load the counter.
										* The following loads the value 248 into the Timer 2 counter
										* The math behind this is:
										* (Desired period) = 64us.
										* (CPU frequency) / (prescaler value) = 125000 Hz -> 8us.
										* (desired period) / 8us = 8.
										* MAX(uint8) - 8 = 248;
										*/
										/* Save value globally for later reload in ISR */
	tcnt2 = 248;

	/* Finally load end enable the timer */
	TCNT2 = tcnt2;
	TIMSK2 |= (1 << TOIE2);

	//Configure I/O Pin Directions
	pinMode(FREQ1, OUTPUT);
	pinMode(FREQ2, OUTPUT);
	pinMode(FREQ3, OUTPUT);

}

/* Install the Interrupt Service Routine (ISR) for Timer2.  */
ISR(TIMER2_OVF_vect) {
	/* Reload the timer */
	TCNT2 = tcnt2;

	count1++; count2++; count3++;

	if (count1 == 60) {
		digitalWrite(FREQ1, toggle1 == 0 ? HIGH : LOW);
		toggle1 = ~toggle1;
		count1 = 0;
	}
	if (count2 == 53) {
		digitalWrite(FREQ2, toggle2 == 0 ? HIGH : LOW);
		toggle2 = ~toggle2;
		count2 = 0;
	}
	if (count3 == 47) {
		digitalWrite(FREQ3, toggle3 == 0 ? HIGH : LOW);
		toggle3 = ~toggle3;
		count3 = 0;
	}
}

void loop() {



}
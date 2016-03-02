#define datapin 8
#define clockpin 9
#define latchpin 10
#define LEDpin 5

#define COFF 0
#define CON 1
#define ROFF 1
#define RON 0
#define LISTEN 0
#define DONTLISTEN 1

byte data = 0;
byte data2 = 0;

boolean board[8][8];

void setup() {
	pinMode(latchpin, OUTPUT);
	pinMode(LEDpin, OUTPUT);
	Serial.begin(9600);
}

void loop() {
	//smile();
	//blinkAll();
	test();
}

void smile() {
	board[2][2] = 1;
	board[2][5] = 1;
	board[4][2] = 1;
	board[4][5] = 1;
	board[5][3] = 1;
	board[5][4] = 1;
	refreshBoard();
}

void blinkAll() {
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			board[row][col] = 1;
		}
	}
	digitalWrite(LEDpin, HIGH);
	refreshBoard();
	delay(100);
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			board[row][col] = 0;
		}
	}
	digitalWrite(LEDpin, LOW);
	refreshBoard();
	delay(100);
}

void test() {
	data = 0;
	for(int i = 0; i < 256; i++) {
		data++;
		Serial.println(data, BIN);
		shiftOut(datapin, clockpin, data);
		delay(100);
	}
}

void wipeBoard() {
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			board[row][col] = 0;
		}
	}
}

void refreshBoard() {
	wipeBoard();
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			if (board[row][col] == 0) continue;
			columns(col, board[row][col]);
		} 
		rows(row, RON);

		// Sets LED ON
		digitalWrite(latchpin, LISTEN);
		shiftAll();
		digitalWrite(latchpin, DONTLISTEN);
		
		// Sets all LEDs OFF
		digitalWrite(latchpin, LISTEN);
		for (int i = 0; i < 8; i++) {
			rows(i, ROFF);
			columns(i, COFF);
		}
		shiftAll();
		digitalWrite(latchpin, DONTLISTEN);
	}
}

// STUFF FOR SHIFT REGISTERS
void rows(int desiredPin, boolean desiredState) {
	bitWrite(data, desiredPin, desiredState);
}

void columns(int desiredPin, boolean desiredState) {
	bitWrite(data2, desiredPin, desiredState);
}

void shiftAll() {
	Serial.print(data, BIN);
	Serial.print("\t");
	Serial.print(data2, BIN);
	Serial.println();
	shiftOut(datapin, clockpin, data2);
	shiftOut(datapin, clockpin, data);
}
void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
	int pinState;
	pinMode(myClockPin, OUTPUT);
	pinMode(myDataPin, OUTPUT);
	
	digitalWrite(myDataPin, 0);
	digitalWrite(myClockPin, 0);
	
	for (int i = 7; i >= 0; i--) {
		digitalWrite(myClockPin, 0);
	
		if (myDataOut & (1 << i) ) {
			pinState = 1;
		} else {
			pinState = 0;
		}
	
		digitalWrite(myDataPin, pinState);
		digitalWrite(myClockPin, 1);
		digitalWrite(myDataPin, 0);
	}
	//stop shifting
	digitalWrite(myClockPin, 0);
}
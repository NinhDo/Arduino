const int DATAPIN = 2;
const int LATCHPIN = 3;
const int CLOCKPIN = 4;

byte dataL;
byte dataR;
short refreshRate = 500;
short rewindRate = 1000;

void setup()  {
  pinMode(DATAPIN, OUTPUT);
  pinMode(LATCHPIN, OUTPUT);
  pinMode(CLOCKPIN, OUTPUT);
}

void loop() {
  for (int i = 0; i < 8; i++) {
    updateEye(i, HIGH);
    delay(refreshRate);
  }
  delay(rewindRate);
  for (int i = 0; i < 8; i++) {
    updateEye(i, LOW);
    delay(refreshRate);
  }
  delay(rewindRate);
}

void updateEye(int i, boolean state) {
  digitalWrite(LATCHPIN, 0);
  leftEye(i, state);
  rightEye(7 - i, state);
  shiftAll();
  digitalWrite(LATCHPIN, 1);
}

void leftEye(int desiredPin, boolean state) {
  bitWrite(dataL, desiredPin, state);
}

void rightEye(int desiredPin, boolean state) {
  bitWrite(dataR, desiredPin, state);
}

void shiftAll() {
  shiftOut(DATAPIN, CLOCKPIN, dataL);
  shiftOut(DATAPIN, CLOCKPIN, dataR);
}

void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);
  int pinState;

  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);

  for (int i = 7; i >= 0; i--) {
    digitalWrite(myClockPin, 0);

    if (myDataOut & (1 << i) ) {
      pinState = 1;
    }
    else {
      pinState = 0;
    }
    digitalWrite(myDataPin, pinState);
    digitalWrite(myClockPin, 1);
    digitalWrite(myDataPin, 0);
  }

  //stop shifting
  digitalWrite(myClockPin, 0);
}


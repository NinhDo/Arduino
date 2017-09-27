 #include <SevenSeg.h>         // Inkluderer bibliotek for syvtalls-display
/* Lydfiler kommandoer
 *  bomb = bombe tikker ned fort
 *  correct = riktig lyd
 *  count = klokkelyd
 *  jamesbond = intromusikk
 *  padlock = koffert åpnes
 *  
 *  
 *  
 *  
 *  
 */
int interruptPin = 2;         // Interrupter programmet, og resetter det til Fase1
const int laserPin = 13;      // Outputs 
const int magnetPin = 11;
const int redPin = 10;
const int greenPin = 9;
const int bluePin = 8;
const int inSignal = 7;   // Sjekker høyt signal inn
const int outSignal = 6;  // Sender høyt eller lavt signal ut
int wrongtime = 0;
const int buzzer = 5;   // Buzzer-lyd for riktig/galt
int buzztime = 0;
const int ldrPin = A5;      // Input Lysmåler
// Countere for riktig/galt
int a = 0;    //counter for riktig1
int b = 0;    //counter for riktig2
int c = 0;    //counter for riktig3
int d = 0;    //counter for riktig4
int e = 0;    //counter for forrige feil
int f = 0;    //counter for feil
int g = 0;    //counter for ledTime
int p = 0;
// Tidsfunksjoner
bool hasReducedTime = false;
const int A = 53 ; // 2
const int B = 51;  // 3
const int C = 49;   // 4
const int D = 47;   //5 
const int E = 45;   //6
const int F = 43;   // 7
const int G = 41;   // 8
const int punktum = 39;   //9
const int t1 = 37;    //10
const int t2 = 35;    //11
const int t3 = 33;    //12
const int t4 = 31;    //13
unsigned long lasttime = 0; //Unsigned long er en variabel som ikke blir negativ og som kan utvide seg til å bli veldig høye tall
unsigned long timenow;
int minutes = 0;
int seconds = 0;
int totalSecondsLeft = 120; // Antall sekunder spillerene har
bool start = false;
//denne blokken må med for å aktivere leddisplayet:
SevenSeg disp(53, 51, 49, 47, 45, 43, 41); // fra venstre til høyre -> A, B, C, D, E, F, G pins
const int numberOfDigits = 4;
int digitPins [numberOfDigits] = { t1, t2, t3, t4 };
// Countere for LED
int ledColor = 0;
long ledTime = 0;
int normValue = 300;          //Normalverdien for lyssensoren
const int STAGE_1 = 1;    // Fase 1 av program
const int STAGE_2 = 2;    // Fase 2 av program
int state = STAGE_1;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(interruptPin, INPUT);
  pinMode(laserPin, OUTPUT); 
  pinMode(ldrPin, INPUT);
  pinMode(magnetPin, OUTPUT);
  pinMode(inSignal, INPUT);
  pinMode(outSignal, OUTPUT);
  pinMode(buzzer, OUTPUT);
  // Setter LED output
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  
  // Setter Wire input
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  // Attach interupt signal from control system to a digitial pin (https://www.arduino.cc/en/Reference/attachInterrupt)
  attachInterrupt(digitalPinToInterrupt(interruptPin), reset, HIGH);
  // Tidsfunksjoner
  disp.setDigitPins(numberOfDigits, digitPins); // Si til display at digitpins er pinnene til hvert segment
  disp.setDPPin(9); // Punktum i midten. Funker ikke?
  disp.setRefreshRate(50);
  
  minutes = totalSecondsLeft / 60;
  seconds = totalSecondsLeft % 60;
  start = true; // For å teste timeren. Skal være false ellers!
  normValue = 500;
}
void loop() {
  // if ( inSignal == HIGH) {
  if (state == STAGE_1) {
    // Skru på laser
    digitalWrite(laserPin, HIGH);
    // Serial.println("jamesbond");
    
  
    // Skru på magnet
    digitalWrite(magnetPin, HIGH);
      // Lasermåler sjekker lysstyrke
    int ldrStatus = analogRead(ldrPin);         //leser verdien av lysmåleren, ti ganger for å få en stabil verdi.
        
    if (ldrStatus >= (normValue+5)) {
      digitalWrite(magnetPin, LOW);
      digitalWrite(laserPin, LOW);
      //Serial.println("---------------");
      //Serial.println("magnet off");
      Serial.println("padlock");
      state = STAGE_2;
    }
  }
  if (state == STAGE_2) {
    // Tidsfunksjon
    
    timenow = millis() / 1000; // hvor lang tid har det gått siden arduinoen slo seg på? Millis er funksjonen som teller millisekunder fra programmet starter.
  // sett start = true for å starte timer. Denne skal bli true i det låsen åpnes!
  if(start) {
   
    // hvis tid har gått ut
    if(totalSecondsLeft <= 0) {
      totalSecondsLeft = 0;
      // modulo for å få sekunder
      seconds = totalSecondsLeft % 60;
      // del på for å få minutter (hele tall rundet ned)
      minutes = totalSecondsLeft / 60;
      
      // HER HAR TIDA GÅTT UT
      // GJØR TING
      
      start = false;
      disp.setRefreshRate(10);
    }
    // Hvis tida siden start og sist sjekk er et sekund eller mer, tell ned sekund
    if(timenow - lasttime >= 1){
      lasttime = timenow;
      totalSecondsLeft--;
      if (totalSecondsLeft < 0) {
        totalSecondsLeft = 0;
        digitalWrite(outSignal, LOW);
      }
      seconds = totalSecondsLeft % 60;
      minutes = totalSecondsLeft / 60;
    }     
  }    
    // Konverter tiden til en streng så vi kan skrive ledene nuller og punktum
  String numberToWrite = "";
  if(minutes < 10) numberToWrite = "0";
  numberToWrite += String(minutes) + ".";
  if(seconds < 10) numberToWrite += "0";
  numberToWrite += String(seconds);
  // Skriv til display tallet.
  disp.write(numberToWrite);  
    // Defusing 
    
    int feil = digitalRead(A0);
    int riktig1 = digitalRead(A1);
    int riktig2 = digitalRead(A2);
    int riktig3 = digitalRead(A3);
    int riktig4 = digitalRead(A4);
    ledBlink();
   
    if (feil == LOW) {
      
     // Tidsreduksjon 10 s
     if (!hasReducedTime) {
      totalSecondsLeft -= 10;
      hasReducedTime = true;
      }
     ledControl(2);
     Serial.println("Feil");  
     //f = 1;
     
   } else if (riktig1 == LOW) {
     if (a == 0) {
      Serial.println("correct");
      ledControl(1);
     }
     a = 1;
   } else if (riktig2 == LOW) {
     if (b == 0) {
      Serial.println("correct");
      ledControl(1);
     }
     b = 1; 
   } else if (riktig3 == LOW) {
     if (c == 0) {
      Serial.println("correct");
      ledControl(1);
     }
     c = 1; 
   } else if (riktig4 == LOW) {
     if (d == 0) {
      Serial.println("correct");
      ledControl(1);
     }
     d = 1;
   }
   
   if (a && 1 and b && 1 and c && 1 and d && 1) {
    Serial.println("jamesbond");
    // LYDFUNKSJON
    ledControl(3);
    digitalWrite(outSignal, HIGH);
    start = false;
        
   }
   if (feil == HIGH) {
      hasReducedTime = false;
     }
  }
  
}
void reset() {
  // reset state
  state = STAGE_1;
}
/*
 * LED Funksjon kaller:
 * 1 = Grønn (riktig)
 * 2 = Rød (feil)
 * 3 = Blå (nøytral)
 */
void ledControl(int led) {
  ledTime = millis();
  switch(led) {
    case 1:        // 1 = Grønn  (riktig)
      ledColor = 1;
      break;
    case 2:       // 2 = Rød
      ledColor = 2;  
      break;
    case 3:       // 3 = Blå
      ledColor = 3; 
      break;
    default:
      break;
  }
}
/*
 * LED Funksjon styrer lys
 * 1 = Grønn (riktig)
 * 2 = Rød (feil)
 * 3 = Blå (nøytral)
 */
void ledBlink() {
  int duration = 1000;
  if (millis() - ledTime <= duration) {
    switch(ledColor) {
      case 1:
        digitalWrite(greenPin, HIGH);
        break;
      case 2:
        digitalWrite(redPin, HIGH);
        break;
      case 3:
        digitalWrite(bluePin, HIGH);
        break;
      default:
        break;
    }
  } else {
    digitalWrite(greenPin, LOW);
    digitalWrite(redPin, LOW);
    digitalWrite(bluePin, LOW);
    ledColor = 0;
  }
}
void sette_tall(int tallform){  
  switch(tallform){
    case(0):
        digitalWrite(A,LOW);
        digitalWrite(B,LOW);
        digitalWrite(C,LOW);
        digitalWrite(D,LOW);
        digitalWrite(E,LOW);
        digitalWrite(F,LOW);
        digitalWrite(G,HIGH);
        break;
    case(1):
        digitalWrite(A,HIGH);
        digitalWrite(B,LOW);
        digitalWrite(C,LOW);
        digitalWrite(D,HIGH);
        digitalWrite(E,HIGH);
        digitalWrite(F,HIGH);
        digitalWrite(G,HIGH);
        break;
    case(2):
        digitalWrite(A,LOW);
        digitalWrite(B,LOW);
        digitalWrite(C,HIGH);
        digitalWrite(D,LOW);
        digitalWrite(E,LOW);
        digitalWrite(F,HIGH);
        digitalWrite(G,LOW);
        break;
    case(3):
        digitalWrite(A,LOW);
        digitalWrite(B,LOW);
        digitalWrite(C,LOW);
        digitalWrite(D,LOW);
        digitalWrite(E,HIGH);
        digitalWrite(F,HIGH);
        digitalWrite(G,LOW);
        break;
    case(4):
        digitalWrite(A,HIGH);
        digitalWrite(B,LOW);
        digitalWrite(C,LOW);
        digitalWrite(D,HIGH);
        digitalWrite(E,HIGH);
        digitalWrite(F,LOW);
        digitalWrite(G,LOW);
        break;
    case(5):
        digitalWrite(A,LOW);
        digitalWrite(B,HIGH);
        digitalWrite(C,LOW);
        digitalWrite(D,LOW);
        digitalWrite(E,HIGH);
        digitalWrite(F,LOW);
        digitalWrite(G,LOW);
        break;
    case(6):
        digitalWrite(A,LOW);
        digitalWrite(B,HIGH);
        digitalWrite(C,LOW);
        digitalWrite(D,LOW);
        digitalWrite(E,LOW);
        digitalWrite(F,LOW);
        digitalWrite(G,LOW);
        break;
    case(7):
        digitalWrite(A,LOW);
        digitalWrite(B,LOW);
        digitalWrite(C,LOW);
        digitalWrite(D,HIGH);
        digitalWrite(E,HIGH);
        digitalWrite(F,HIGH);
        digitalWrite(G,HIGH);
        break;
    case(8):
        digitalWrite(A,LOW);
        digitalWrite(B,LOW);
        digitalWrite(C,LOW);
        digitalWrite(D,LOW);
        digitalWrite(E,LOW);
        digitalWrite(F,LOW);
        digitalWrite(G,LOW);
        break;
    case(9):
        digitalWrite(A,LOW);
        digitalWrite(B,LOW);
        digitalWrite(C,LOW);
        digitalWrite(D,LOW);
        digitalWrite(E,HIGH);
        digitalWrite(F,LOW);
        digitalWrite(G,LOW);
        break;
  }
}
/*void buzzer(tall) {
  switch(tall);
  buzztime = millis();
    case 1: 
      digitalWrite(buzzer, HIGH);
      if (millis - buzztime >= 2) {
        digitalWrite(buzzer, LOW);
      }
        digitalWrite(buzzer, HIGH);
        break;
    case 2:
      digitalWrite(buzzer, HIGH);
      if (millis - buzztime >= 5) {
        digitalWrite(buzzer, LOW);
      }
        digitalWrite(buzzer, HIGH);
        break;
        
}
*/

const int motorIn1 = 2;  //attach to one of the pin of the motor
const int motorIn2 = 4;  //attach to another pin of the motor

const int button1 = 7;
const int button2 = 8;

void setup(){
	pinMode(motorIn1,OUTPUT);
	pinMode(motorIn2,OUTPUT);
	pinMode(button1, INPUT);
	pinMode(button2, INPUT);
	clockwise(0);
	Serial.begin(9600);
}

void loop(){
	Serial.println(digitalRead(button1));
	Serial.println(digitalRead(button2));
	Serial.println();
	
	if(digitalRead(button1) == HIGH) {
		clockwise(2000);
	} else if(digitalRead(button2) == HIGH) {
		counterclockwise(2000);
	} else {
		clockwise(0);
	}
	delay(100);
}

void clockwise(int Speed){
	analogWrite(motorIn1,Speed);  //set the speed of motor
	analogWrite(motorIn2,0);  //stop the motorIn2 pin of motor
}

void counterclockwise(int Speed){
	analogWrite(motorIn1,0);  //stop the motorIn1 pin of motor
	analogWrite(motorIn2,Speed);  //set the speed of motor
}

#define sensorPort A0
#define motorIn1 3
#define motorIn2 4

int val;
float celsius;
float celsiusArray[10];
int counter = 0;
float avg;

void setup() {
	Serial.begin(9600);
	pinMode(motorIn1, OUTPUT);
	pinMode(motorIn2, OUTPUT);
}

void loop() {
	val = analogRead(sensorPort);
	celsius = (val / 1024.0) * 500;
	celsiusArray[counter] = celsius;
	avg = 0;
	for (int i = 0; i < 10; i++) avg += celsiusArray[i];
	avg = avg / 10;
	counter++;
	counter = counter % 10;
	for(int i = 0; i < 10; i++) {
		Serial.print(celsiusArray[i]);
		Serial.print(" ");
	}
	Serial.println();
	Serial.println(avg);

	if(avg >= 28.0) {
		clockwise(1000);
	} else {
		clockwise(0);
	}

	delay(10);
}

void clockwise(int Speed)
{
  analogWrite(motorIn1,Speed);
  analogWrite(motorIn2,0);
}

void counterclockwise(int Speed)
{
  analogWrite(motorIn1,0);
  analogWrite(motorIn2,Speed); 
}
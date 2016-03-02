// Include headers
#include <ZumoMotors.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <Pushbutton.h>

// Define constants
#define NUM_SENSORS 6
#define sensorThreshold 500
#define speedStop 0
#define speedMin 100
#define speedMid 200
#define speedTurn 400
#define speedMax 325
#define turnTime 50

// Variables
ZumoMotors motors;
ZumoReflectanceSensorArray reflectSensors;
Pushbutton button(ZUMO_BUTTON);

unsigned int sensorValues[NUM_SENSORS];

void setup() {
	Serial.begin(9600);
	reflectSensors.init();

	delay(500);

	unsigned long startTime = millis();
	
	while(millis() - startTime < 10000) {
		reflectSensors.calibrate();
	}
	
	for (byte i = 0; i < NUM_SENSORS; i++) {
		Serial.print(reflectSensors.calibratedMinimumOn[i]);
		Serial.print(' ');
	}

	Serial.println();

	for (byte i = 0; i < NUM_SENSORS; i++) {
		Serial.print(reflectSensors.calibratedMaximumOn[i]);
		Serial.print(' ');
	}
	Serial.println();
	Serial.println();
	button.waitForButton();
}

void loop() {
	unsigned int position = reflectSensors.readLine(sensorValues);
	bool isOnEdge = false;

	for (byte i = 0; i < NUM_SENSORS; i++) {
		if (sensorValues[i] < sensorThreshold) {
			isOnEdge = true;
			motors.setSpeeds(-speedTurn, -speedTurn);
			break;
		} 
	}
	if(isOnEdge) {
		delay(turnTime);
		if (position >= 2500) {
			motors.setSpeeds(speedTurn, -speedTurn);
			delay(turnTime * 2);
		} else {
			motors.setSpeeds(-speedTurn, speedTurn);
			delay(turnTime * 2);
		}
	}

	motors.setSpeeds(speedMax, speedMax);
}
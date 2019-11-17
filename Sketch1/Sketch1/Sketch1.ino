#include "sensorSystem.h"
#include "trusterSystem.h"
#include "map.h"

#define BTN_PIN A3
#define DIOD_PIN A4

SonarSensor* sonar;
servoTruster* servo;
servoTruster* manip;
Map* karta;
bool PIDon = false;
bool isright = true;
const float P = 0.15;
const float D = 0.2;
float oldError = 0;

void setup() {
	Serial.begin(115200);
	sonar = sensorSystem::getInstance()->sonar;
	servo = trusterSystem::getInstance()->servo;
	manip = trusterSystem::getInstance()->manip;
	karta = new Map();
	trusterSystem::getInstance()->truster->speed = 0.7f;
	pinMode(DIOD_PIN, OUTPUT);
	pinMode(BTN_PIN, INPUT_PULLUP);
	trusterSystem::getInstance()->manip->angle = 10;
	trusterSystem::getInstance()->servo->angle = 95;
}

void PIDmove() {
	auto left = sensorSystem::getInstance()->leftLineSensor->getValue();
	auto rig = sensorSystem::getInstance()->rigthLineSensor->getValue();
	auto err = left - rig;
	float PID = P * err + D * (err - oldError);
	oldError = err;
	servo->angle = acos(PID) / PI * 180 + 5;
}

void ReleMobe() {
	auto left = sensorSystem::getInstance()->leftLineSensor->getValue();
	auto rigth = sensorSystem::getInstance()->rigthLineSensor->getValue();
	auto error = left - rigth;
	auto angle = error * 2.f * 90.f;

	servo->angle = 90 + angle;
}


int counter = 0;
void checkButton(){
	auto pull = digitalRead(BTN_PIN);
	if (pull == 0)
		counter++;
	else {
		if (counter > 5)
			isright = !isright;
		counter = 0;
	}
	digitalWrite(DIOD_PIN, isright);
}

float time, oldTime = 0, deltaTime, startTime = 0;;
bool rotate = true;
int index = 0;

float funcDvig(float x) {
	return 45 * sin(x / PI);
}

bool findBlack = false;

void loop() {
	checkButton();
	/*if (!karta->isReady()) {
		karta->update();
		return;
	}*/
	sensorSystem::getInstance()->update();
	/*Serial.print(sensorSystem::getInstance()->leftLineSensor->getValue());
	Serial.print(" ");
	Serial.println(sensorSystem::getInstance()->rigthLineSensor->getValue());*/
	/*if (PIDon)
		PIDmove();*/
	time = millis();
	if (!oldTime)
		oldTime = time;
	if (!startTime)
		startTime = time;
	deltaTime = time - oldTime;
	if (time - startTime < 10000) {
		return;
	}
	if (time - startTime > 10800) {
		auto rig = sensorSystem::getInstance()->rigthLineSensor->getValue();
		if (!isright) {
			rig = sensorSystem::getInstance()->leftLineSensor->getValue();
		}
		if (rig > 0.7)
			findBlack = true;
		if (findBlack && rig < 0.3)
			PIDon = true;
		/*trusterSystem::getInstance()->truster->speed = 1.f;
		trusterSystem::getInstance()->servo->angle = 90 + funcDvig((time - startTime) / 1000);*/
	}
	if (time - startTime > 15000) {
		trusterSystem::getInstance()->manip->angle = 100;
	}
	auto step = 1000;
	if (time - startTime > 14700 + step) {
		trusterSystem::getInstance()->servo->angle = 95;
		trusterSystem::getInstance()->truster->speed = 1.f;
	}
	if (time - startTime > 15700 + step) {
		trusterSystem::getInstance()->truster->speed = -1.f;
		trusterSystem::getInstance()->servo->angle = 115;
	}
	if (time - startTime > 16700 + step) {
		trusterSystem::getInstance()->truster->speed = 1.f;
		trusterSystem::getInstance()->servo->angle = 95;
	}
	if (time - startTime > 17700 + step) {
		trusterSystem::getInstance()->truster->speed = -1.f;
		trusterSystem::getInstance()->servo->angle = 115;
	}
	if (time - startTime > 18700 + step) {
		trusterSystem::getInstance()->truster->speed = 1.f;
		trusterSystem::getInstance()->servo->angle = 95;
	}
	if (time - startTime > 19700 + step) {
		trusterSystem::getInstance()->truster->speed = -1.f;
		trusterSystem::getInstance()->servo->angle = 115;
	}
	if (time - startTime > 20700 + step) {
		trusterSystem::getInstance()->truster->speed = 1.f;
		trusterSystem::getInstance()->servo->angle = 95;
	}
	if (time - startTime > 21700 + step) {
		trusterSystem::getInstance()->truster->speed = 1.f;
		trusterSystem::getInstance()->servo->angle = 115;
	}
	if (PIDon)
		PIDmove();


	trusterSystem::getInstance()->move();
}

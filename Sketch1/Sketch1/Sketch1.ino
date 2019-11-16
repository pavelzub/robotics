#include "sensorSystem.h"
#include "trusterSystem.h"
#include "map.h"

SonarSensor* sonar;
WallSensor* wallSensor;
servoTruster* servo;
Map* karta;
bool PIDon = true;
const float P = 100;
const float D = 1000;
float oldError = 0;

void setup() {
	Serial.begin(115200);
	sonar = sensorSystem::getInstance()->sonar;
	wallSensor = sensorSystem::getInstance()->wallSensor;
	servo = trusterSystem::getInstance()->servo;
	karta = new Map();
}

void PIDmove() {
	auto left = sensorSystem::getInstance()->leftLineSensor->getValue();
	auto rigth = sensorSystem::getInstance()->rigthLineSensor->getValue();
	auto error = rigth - left;
	auto PID = P * error + D * (error - oldError);
	auto angle = map(PID, -200, 100, -1, 1);
	servo->angle = 90 + acos(angle);
}

void ReleMobe() {
	auto left = sensorSystem::getInstance()->leftLineSensor->getValue();
	auto rigth = sensorSystem::getInstance()->rigthLineSensor->getValue();
	auto error = rigth - left;
	auto angle = map(error, -1024, 1024, -89, 89);
	servo->angle = 90 + angle;
}

int i = 0;
int step = 1;

void loop() {
	/*if (!karta->isReady()) {
		karta->update();
		return;
	}*/
	//sensorSystem::getInstance()->update();
	
	if (PIDon) {}
		//PIDmove();
	i += step;
	if (i == 180 || i == 0)
		step *= -1;
	servo->angle = i;
	delay(50);
	Serial.println(i);

	trusterSystem::getInstance()->move();
}

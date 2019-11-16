#pragma once
#include "sensors.h"

#define TRIGGER_SONAR 12
#define ECHO_SONAR 11
#define MAX_DISTANCE 200
#define WALL_PIN 24
#define LINE_PIN A0
#define IR_PIN 11

class sensorSystem {
public:
	sensorSystem();
	void update();
	SonarSensor* sonar;
	WallSensor* wallSensor;
	LineSensor* lineSensor;
	static sensorSystem* getInstance();
private:
	static sensorSystem* instance;
};
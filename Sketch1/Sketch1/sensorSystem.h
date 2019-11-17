#pragma once
#include "sensors.h"

#define TRIGGER_SONAR 12
#define ECHO_SONAR 11
#define MAX_DISTANCE 200
#define WALL_PIN 24
#define LEFT_LINE_PIN A0
#define RIGHT_LINE_PIN A2
#define IR_PIN 10
#define COLOR_S0 4
#define COLOR_S1 5
#define COLOR_S2 6
#define COLOR_S3 7
#define COLOR_OUT 8

class sensorSystem {
public:
	sensorSystem();
	void update();
	SonarSensor* sonar;
	WallSensor* wallSensor;
	LineSensor* leftLineSensor;
	LineSensor* rigthLineSensor;
	ColorSensor* colorSensor;
	static sensorSystem* getInstance();
private:
	static sensorSystem* instance;
};
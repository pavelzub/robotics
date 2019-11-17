#include "sensorSystem.h"

sensorSystem* sensorSystem::instance = nullptr;

sensorSystem::sensorSystem():
	sonar(new SonarSensor(TRIGGER_SONAR, ECHO_SONAR, MAX_DISTANCE)),
	wallSensor(new WallSensor(WALL_PIN)),
	leftLineSensor(new LineSensor(LEFT_LINE_PIN)),
	rigthLineSensor(new LineSensor(RIGHT_LINE_PIN)),
	colorSensor(new ColorSensor(COLOR_S0, COLOR_S1, COLOR_S2, COLOR_S3, COLOR_OUT))
{}

void sensorSystem::update(){
	sonar->updateInfo();
	wallSensor->updateInfo();
	leftLineSensor->updateInfo();
	rigthLineSensor->updateInfo();
	colorSensor->updateInfo();
}

sensorSystem* sensorSystem::getInstance(){
	if (!instance) {
		instance = new sensorSystem();
	}
	return instance;
}

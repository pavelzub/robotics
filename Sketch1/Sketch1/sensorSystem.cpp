#include "sensorSystem.h"

sensorSystem* sensorSystem::instance = nullptr;

sensorSystem::sensorSystem():
	sonar(new SonarSensor(TRIGGER_SONAR, ECHO_SONAR, MAX_DISTANCE)),
	wallSensor(new WallSensor(WALL_PIN)),
	lineSensor(new LineSensor(LINE_PIN))
{}

void sensorSystem::update(){
	sonar->updateInfo();
	wallSensor->updateInfo();
	lineSensor->updateInfo();
}

sensorSystem* sensorSystem::getInstance(){
	if (!instance) {
		instance = new sensorSystem();
	}
	return instance;
}

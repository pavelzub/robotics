#include "trusterSystem.h"

trusterSystem* trusterSystem::instance = nullptr;

trusterSystem::trusterSystem():
	servo(new servoTruster(SERVO_PIN))
{
}

void trusterSystem::move(){
	servo->move();
}

trusterSystem* trusterSystem::getInstance(){
	if (!instance)
		instance = new trusterSystem();
	return instance;
}

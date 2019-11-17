#include "trusterSystem.h"

trusterSystem* trusterSystem::instance = nullptr;

trusterSystem::trusterSystem():
	servo(new servoTruster(SERVO_PIN)),
	manip(new servoTruster(MANIP_PIN)),
	truster(new trusterTruster(TRUSTER_0, TRUSTER_1, TRUSTER_PWM))
{
}

void trusterSystem::move(){
	servo->move();
	manip->move();
	truster->move();
}

trusterSystem* trusterSystem::getInstance(){
	if (!instance)
		instance = new trusterSystem();
	return instance;
}

#include "trusters.h"

servoTruster::servoTruster(int pin): 
	pin(pin),
	servo(new Servo)
{
	servo->attach(pin);
}

void servoTruster::move() {
	servo->write(angle);
}

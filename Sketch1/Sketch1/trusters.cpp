#include "trusters.h"
#include <Arduino.h>

servoTruster::servoTruster(int pin): 
	pin(pin),
	servo(new Servo)
{
	servo->attach(pin);
}

void servoTruster::move() {
	servo->write(angle);
}

trusterTruster::trusterTruster(int pin0, int pin1, int pwm):
	pin0(pin0),
	pin1(pin1),
	pwm(pwm)
{
	pinMode(pin0, OUTPUT);
	pinMode(pin1, OUTPUT);
	pinMode(pwm, OUTPUT);
}

void trusterTruster::move(){
	if (speed < 0) {
		digitalWrite(pin0, LOW);
		digitalWrite(pin1, HIGH);
	}
	else {
		digitalWrite(pin0, HIGH);
		digitalWrite(pin1, LOW);
	}
	auto val = abs(speed) * 255.f;
	analogWrite(pwm, val);
}

#pragma once
#include "trusters.h"
#define SERVO_PIN 17

class trusterSystem {
public:
	trusterSystem();
	void move();
	static trusterSystem* getInstance();
	servoTruster* servo;
private:
	static trusterSystem* instance;
};
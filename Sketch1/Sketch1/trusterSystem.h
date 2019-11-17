#pragma once
#include "trusters.h"
#include <Arduino.h>
#define SERVO_PIN 15
#define MANIP_PIN 13
#define TRUSTER_0 2
#define TRUSTER_1 3
#define TRUSTER_PWM 19

class trusterSystem {	
public:
	trusterSystem();
	void move();
	static trusterSystem* getInstance();
	servoTruster* servo;
	servoTruster* manip;
	trusterTruster* truster;
private:
	static trusterSystem* instance;
};
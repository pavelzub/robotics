#pragma once
#include <Servo.h>

class truster {
public:
	virtual void move() = 0;
};

class servoTruster: public truster {
public:
	servoTruster(int pin);
	float angle = 0.f;
	void move();
private:
	Servo* servo;
	int pin;
};

//class trusterTruster : public truster {
//public:
//	trusterTruster(int pin);
//	float speed = 0.f;
//	void move();
//private:
//	Servo* servo;
//	int pin;
//};

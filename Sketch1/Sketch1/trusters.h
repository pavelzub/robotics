#pragma once
#include <Servo.h>

class truster {
public:
	virtual void move() = 0;
};

class servoTruster: public truster {
public:
	servoTruster(int pin);
	float angle = 90.f;
	void move() override;
private:
	Servo* servo;
	int pin;
};

class trusterTruster : public truster {
public:
	trusterTruster(int pin0, int pin1, int pwm);
	float speed = 0.f;
	void move() override;
private:
	int pin0, pin1, pwm;
	int pin;
};

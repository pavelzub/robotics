#pragma once
//#include <NewPing.h>
#include <Thread.h>
#include <IRremote.h>

#define SONAR_DELTA 50
#define COLOR_DELAY 100
#define COLOR_TIMEOUT 5000

class Sensor {
public:
	virtual void updateInfo() = 0;
};

class SonarSensor: public Sensor {
public:
	SonarSensor(int triggerPin, int echoPin, int maxDist);
	void updateInfo() override;
	float getDistance() { return distance; }
private:
	//NewPing* sonar;
	float distance = -1;
	Thread thread;
	float time = 0;
};

class WallSensor : public Sensor {
public:
	WallSensor(int pin);
	void updateInfo() override;
	float getValue() { return value; }
private:
	int pin;
	bool value = false;
};

class LineSensor : public Sensor {
public:
	LineSensor(int pin);
	void updateInfo() override;
	float getValue() { return value; }
private:
	int pin;
	float value = 0.f;
};

class IRSensor : public Sensor {
public:
	IRSensor(int pin);
	void updateInfo() override;
	int dataIndex = 0;
	uint8_t received_data[8];
	float getValue() { return value; }
private:
	decode_results results;
	uint8_t rcv_counter = 0;
	IRrecv* irrecv;
	int pin;
	float value = 0.f;
};

class ColorSensor : public Sensor {
public:
	ColorSensor(int s0, int s1, int s2, int s3, int out);
	void updateInfo() override;
	float getValue() { return value; }
private:
	int values[3];
	int index = 0;
	int redFrequency = 0;
	int greenFrequency = 0;
	int blueFrequency = 0;
	int S0, S1, S2, S3, out;
	float oldTime = 0;
	float value = 0.f;
};
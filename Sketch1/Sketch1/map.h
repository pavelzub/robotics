#pragma once
#include "sensorSystem.h"

class Map{
public:
	Map();
	void update();
	bool isReady() { return ready; };
	uint8_t data[8];
private:
	IRSensor* irSensor;
	bool ready = false;
	int lastIndex = 0;
	uint8_t received_data[8];
	int sameCount;
};

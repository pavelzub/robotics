#include "map.h"

Map::Map():
	irSensor(new IRSensor(IR_PIN))
{}

//int find_mistake(uint8_t input[8])
//{
//	int i, mistake = 0;
//	for (i = 0; i < 7; i++)
//		if (input[i] == 1)
//			mistake ^= i + 1;
//	return mistake;
//}

void Map::update(){
	//if (ready) 
		//return;
	irSensor->updateInfo();
	/*if (irSensor->dataIndex > lastIndex) {
		lastIndex = irSensor->dataIndex;
		if (irSensor->received_data[4] == 255 && irSensor->received_data[7] == 255 && irSensor->received_data[6] == 255 && irSensor->received_data[5] == 255) {
			sameCount = 0;
			return;
		}
		if (sameCount == 0) {
			for (int i = 0; i < 8; i++)
				received_data[i] = irSensor->received_data[i];
			return;
		}
		if (sameCount == 1) {
			for (int i = 0; i < 8; i++)
				if (received_data[i] != irSensor->received_data[i]) {
					sameCount = 0;
					return;
				}
		}

		uint8_t tmp[8];
		for (int i = 0; i < 8; i++) {
			for (int i = 0; i < 8; i++)
				tmp[i] = received_data[i] & (1 << i);
			auto mistake = find_mistake(tmp);
			if (mistake)
				tmp[mistake - 1] = tmp[mistake - 1] == 0 ? 1 : 1;
			int res = tmp[6];
			res += tmp[5] * 2;
			res += tmp[4] * 4;
			res += tmp[2] * 8;
			received_data[i] = res;
			Serial.println(received_data[i]);
		}
		ready = true;
	}*/
}

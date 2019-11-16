#include "map.h"

Map::Map():
	irSensor(new IRSensor(IR_PIN))
{}

int fix(int i) {
	return i == 0 ? 1 : 0;
}

void Map::update(){
	if (ready)
		return;
	irSensor->updateInfo();

	if (irSensor->dataIndex > lastIndex) {
		lastIndex = irSensor->dataIndex;
		if (irSensor->received_data[4] == 255 && irSensor->received_data[7] == 255 && irSensor->received_data[6] == 255 && irSensor->received_data[5] == 255) {
			sameCount = 0;
			return;
		}
		if (sameCount == 0) {
			for (int i = 0; i < 8; i++)
				received_data[i] = irSensor->received_data[i];
			sameCount++;
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
		uint8_t ctrl[3];
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				tmp[j] = (received_data[i] & (1 << (7 - j))) == 0 ? 0 : 1;
			}
			ctrl[0] = tmp[3] ^ tmp[5] ^ tmp[7];
			ctrl[1] = tmp[3] ^ tmp[6] ^ tmp[7];
			ctrl[2] = tmp[5] ^ tmp[6] ^ tmp[7];

			if (ctrl[0] != tmp[1] && ctrl[1] != tmp[2] && ctrl[2] != tmp[4]) {
				tmp[7] = fix(tmp[7]);
			}
			else if (ctrl[0] != tmp[1] && ctrl[1] != tmp[2]) {
				tmp[3] = fix(tmp[3]);
			}
			else if (ctrl[0] != tmp[1] && ctrl[2] != tmp[4]) {
				tmp[5] = fix(tmp[5]);
			}
			else if (ctrl[2] != tmp[4] && ctrl[1] != tmp[2]) {
				tmp[6] = fix(tmp[6]);
			}

			int res = tmp[7];
			res += tmp[6] * 2;
			res += tmp[5] * 4;
			res += tmp[3] * 8;
			received_data[i] = res;
			Serial.println(received_data[i]);
		}
		ready = true;
	}
}

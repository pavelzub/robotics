#include "sensors.h"

SonarSensor::SonarSensor(int triggerPin, int echoPin, int maxDist) {
	//sonar = new NewPing(triggerPin, echoPin, maxDist);
}

void SonarSensor::updateInfo() {
	delay(50);
	//distance = sonar->ping_cm();
}

WallSensor::WallSensor(int pin): pin(pin) {
	pinMode(pin, INPUT);
}

void WallSensor::updateInfo(){
	value = digitalRead(pin) == 1;
}

LineSensor::LineSensor(int pin): pin(pin) {
	pinMode(pin, INPUT);
}

void LineSensor::updateInfo() {
	float tmp = analogRead(pin);
	//Serial.println(tmp);
	value = tmp / 1024.f;
}

IRSensor::IRSensor(int pin): pin(pin){
	irrecv = new IRrecv(pin);
	irrecv->enableIRIn();
}

void IRSensor::updateInfo(){
	if (irrecv->decode(&results)) {
		if (rcv_counter == 0) {
			if (results.value == 0xffffffff) {
				rcv_counter = 1;
			}
		}
		else {
			if (rcv_counter == 1) {
				received_data[0] = (uint8_t)(results.value >> 24);
				received_data[1] = (uint8_t)(results.value >> 16);
				received_data[2] = (uint8_t)(results.value >> 8);
				received_data[3] = (uint8_t)(results.value);
			}
			else if (rcv_counter == 2) {
				received_data[4] = (uint8_t)(results.value >> 24);
				received_data[5] = (uint8_t)(results.value >> 16);
				received_data[6] = (uint8_t)(results.value >> 8);
				received_data[7] = (uint8_t)(results.value);
			}
			rcv_counter++;
		}
		if (rcv_counter > 2) {
			rcv_counter = 0;
			Serial.print("Received data:");
			for (int i = 0; i < 8; i++) {
				Serial.print(" ");
				Serial.print(received_data[i]);
			}
			Serial.println();
			dataIndex++;
		}
		irrecv->resume(); // Receive the next value
	}
}

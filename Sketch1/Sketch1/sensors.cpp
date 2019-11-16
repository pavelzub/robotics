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

ColorSensor::ColorSensor(int s0, int s1, int s2, int s3, int out):
	S0(s0),
	S1(s1),
	S2(s2),
	S3(s3),
	out(out)
{
	pinMode(S0, OUTPUT);
	pinMode(S1, OUTPUT);
	pinMode(S2, OUTPUT);
	pinMode(S3, OUTPUT);
	pinMode(out, INPUT);
	digitalWrite(S0, HIGH);
	digitalWrite(S1, LOW);
}

void ColorSensor::updateInfo(){
	auto time = millis();
	if (time - oldTime > COLOR_DELAY) {
		switch (index)
		{
		case 0:
			digitalWrite(S2, LOW);
			digitalWrite(S3, LOW);

			values[0] = pulseIn(out, LOW);

			Serial.print("R = ");
			Serial.print(redFrequency);
			break;
		case 1:
			digitalWrite(S2, HIGH);
			digitalWrite(S3, HIGH);

			values[1] = pulseIn(out, LOW);

			Serial.print(" G = ");
			Serial.print(greenFrequency);
			break;
		case 2:
			digitalWrite(S2, LOW);
			digitalWrite(S3, HIGH);

			values[1] = pulseIn(out, LOW);

			Serial.print(" B = ");
			Serial.println(blueFrequency);
		}

		if (index == 2) {
			redFrequency = values[0];
			greenFrequency = values[1];
			blueFrequency = values[2];
			index = 0;
		}
		else
			index++;
	}
}

#include <stdio.h>
#include <wiringPi.h>
#include "sht7x.h"

unsigned inline int rotl(unsigned int value, int shift) {
	return (value << shift) | (value >> (sizeof(value) * 8 - shift));
}

unsigned inline int rotr(unsigned int value, int shift) {
	return (value >> shift) | (value << (sizeof(value) * 8 - shift));
}

inline void initComm(){
	pinMode(devicePin,OUTPUT);
	digitalWrite(devicePin, 1);
	SCL_0;
	DLY; DLY;
	SCL_1;
	DLY;
	digitalWrite(devicePin, 0);;
	DLY;
	SCL_0;
	DLY; DLY; DLY;
	SCL_1;
	DLY;
	digitalWrite(devicePin, 1);
	DLY;
	SCL_0;
	DLY;
}

inline void resetComm() {
	int i;    
	pinMode(devicePin, OUTPUT);
	pinMode(SCL, OUTPUT);
	digitalWrite(devicePin, 1);
	for(i = 0; i < 9; i++) {
		SCL_0;
		DLY; DLY; DLY;
		SCL_1;
		DLY; DLY; DLY;
	}
	initComm();
}
 
float measure (int type) {
	int i;
	int ack = 1;
	int ans = 0;
	unsigned char data1, data2, checksum;
	resetComm();
	if (writeByte(type) == 1) {
		printf("write error\n");
		return EX_WRITEERROR;
	}
		
	for(i = 0; i < 65535; i++) {
		ack = digitalRead(devicePin); 
		DLY;
		if (!ack)
			break;
	}
	if (ack)
		return EX_NOACKERROR;
		
	data1 = readByte(ACK);
	data2 = readByte(ACK);
	ans = data1;
	ans = ans << 8;
	ans += data2;
	checksum = readByte(NOACK);

	switch(type) {
		case READTEMPERATURE: 
			return D1 + D2 * ans;
		break;
		case READHUMIDITY:

			return	(measure(READTEMPERATURE) - 25) * (T1 + T2 * ans) + (C1 + C2 * ans + C3 * ans * ans);
		break;
	}
}

inline unsigned char readByte(unsigned char ack) {
	int i = 0;
	unsigned char data = 0;
	unsigned char temp;
	pinMode(devicePin, INPUT);
	for(i = 0; i < 8; i++) {
		SCL_1;
		DLY;
		temp = digitalRead(devicePin);
		data |= temp << (7 - i);
	
		DLY; DLY;
		SCL_0;
		DLY; DLY; DLY;
	}
	if (ack) pinMode(devicePin, OUTPUT);
	digitalWrite(devicePin, 0);;
	DLY;
	SCL_1;
	DLY; DLY; DLY;
	SCL_0;
	DLY;
	pinMode(devicePin, INPUT);
	return data;
}

inline unsigned char writeByte(unsigned char byte) {
	int i;
	char ack = 0;
	
	pinMode(devicePin, OUTPUT);
	
	for(i = 0; i < 8; i++) {
		digitalWrite(devicePin, (byte & 128) >> 7);
		byte = byte << 1;
		DLY;
		SCL_1;
		DLY;DLY;DLY;
		SCL_0;
		DLY; 
		DLY;DLY;
	}
	
	pinMode(devicePin, INPUT);
	DLY;
	SCL_1;
	DLY;
	DLY;
	ack = digitalRead(devicePin);

	DLY;
	SCL_0;
	return ack;
}

int main(int argc, char* argv[]) {
	float val;
	if (wiringPiSetup()) {
	printf("WiringPi init error.\n");
		return -1;
	}

	printf("init ok.\n");

	printf("temperature: %f\n", measure(READTEMPERATURE));
	printf("humidity: %f\n", measure(READHUMIDITY));
	devicePin = 1;
	printf("temperature: %f\n", measure(READTEMPERATURE));
	printf("humidity: %f\n", measure(READHUMIDITY));
	devicePin = 2;
	printf("temperature: %f\n", measure(READTEMPERATURE));
	printf("humidity: %f\n", measure(READHUMIDITY));

	pinMode(devicePin, OUTPUT);
	pinMode(SCL, OUTPUT);

	return 0;
}

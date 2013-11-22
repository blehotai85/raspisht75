#include <iostream>
#include <stdio.h>
#include <wiringPiI2C.h>
#include <wiringPi.h>

#define SDA 0
#define SCL 7
#define SPD 5
#define SPEED 50
#define READTEMP 3
#define READHUMIDITY 5
#define READSTATUSREG 7
#define WRITESTATUSREG 6
#define SOFTRESET 30

#define SCL_1	digitalWrite(SCL, HIGH)
#define SCL_0	digitalWrite(SCL, LOW)
#define SDA_1	digitalWrite(SDA, HIGH)
#define SDA_0	digitalWrite(SDA, LOW)
#define DLY		delayMicroseconds(SPD);

#define DEBUG


using namespace std;

unsigned inline int rotl(unsigned int value, int shift) {
	return (value << shift) | (value >> (sizeof(value) * 8 - shift));
}

unsigned inline int rotr(unsigned int value, int shift) {
	return (value >> shift) | (value << (sizeof(value) * 8 - shift));
}

inline void resetComm() {
    int i;    
    pinMode(SDA, OUTPUT);
    pinMode(SCL, OUTPUT);
    SDA_1;
    for(i = 0; i < 9; i++) {
	SCL_0;
	DLY; DLY;DLY;
	SCL_1;
	DLY; DLY;DLY;
    }
    SCL_0;
    DLY; DLY;DLY;
    SCL_1;
    DLY;
    SDA_0;
    DLY;
    SCL_0;
    DLY; DLY; DLY;
    SCL_1;
    DLY;
    SDA_1;
    DLY;
    SCL_0;
    DLY;
}

inline void testcomm() {
	SCL_0;
	//SDA_1;
	DLY;DLY;DLY;
	SCL_1;
	//SDA_0;
	DLY;DLY;DLY;
}

inline void initComm(){
	pinMode(SDA,OUTPUT);
	SDA_1;
	SCL_0;
	DLY;
	DLY;

	SCL_1;
	DLY;
	SDA_0;
	DLY;
	SCL_0;
	DLY;
	DLY;
	DLY;
	SCL_1;
	DLY;
	SDA_1;
	DLY;
	SCL_0;
	DLY;
}

inline void sendByte(char byte) {
	int i;
	int ack = 0;

	for(i = 0; i < 8; i++) {
		//DLY;	
		digitalWrite(SDA, (byte & 128) >> 7);
		//digitalWrite(SDA, 0);
		
		DLY;
		
		SCL_1;
		DLY;DLY;DLY;
		
		SCL_0;
		
		byte = byte << 1;
		
		DLY; 
		DLY;DLY;
		
	}
	pinMode(SDA, INPUT);
	DLY;
	SCL_1;
	DLY;
	DLY;
	DLY;
	SCL_0;
	
	//prepare for ACK

	/*DLY; DLY;
	ack = digitalRead(SDA);

	SCL_1; //rising edge of the ACK clock
	DLY; DLY;
	SCL_0; //falling edge of the ACK clock
	
	printf("ack: %d\n", ack);
		*/
}
	


int main(int argc, char* argv[])
{
	if (wiringPiSetup()) {
		printf("WiringPi init error.\n");
		return -1;
	}

	printf("WiringPi initialised.\n");
	pinMode(SCL, OUTPUT);
	pinMode(SDA, OUTPUT);
while(1) {
	//testcomm();
	initComm();
	resetComm();
	sendByte(5);
	DLY; DLY; DLY;
	DLY; DLY; DLY;
	DLY; DLY; DLY;
	DLY; DLY; DLY;
	DLY; DLY; DLY;
	DLY; DLY; DLY;
	DLY; DLY; DLY;
	DLY; DLY; DLY;
	DLY; DLY; DLY;
	DLY; DLY; DLY;
	DLY; DLY; DLY;
	DLY; DLY; DLY;
	DLY; DLY; DLY;
	DLY; DLY; DLY;
	DLY; DLY; DLY;
	DLY; DLY; DLY;
	DLY; DLY; DLY;
	DLY; DLY; DLY;
	DLY; DLY; DLY;
	DLY; DLY; DLY;
	DLY; DLY; DLY;
	DLY; DLY; DLY;
	DLY; DLY; DLY;
	DLY; DLY; DLY;
}



	return 0;
}

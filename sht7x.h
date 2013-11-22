#define SCL 7 //can be set to any pin wanted
#define SPD 5 //5 (6*SPD is an avg clock period, circa 33.33 kHz freq)

/* ERROR CODES */
#define EX_WRITEERROR -501
#define EX_NOACKERROR -502

/* ACK CONSTANTS */
#define ACK 1
#define NOACK 0

/* COMMANDS */
#define READTEMPERATURE 3
#define READHUMIDITY 5
#define READSTATUSREG 7
#define WRITESTATUSREG 6
#define SOFTRESET 30

/* CLOCK SIGNAL */
#define SCL_1	digitalWrite(SCL, HIGH)
#define SCL_0	digitalWrite(SCL, LOW)
#define DLY		delayMicroseconds(SPD);

/* CALCULATION COEFFICIENTS */
#define C1	-2.0468
#define C2	0.0367
#define C3	-0.0000015955
#define T1	0.01
#define T2	0.00008
#define D1	-39.7
#define D2	0.01

int devicePin = 0; //pin for SDA signal

typedef struct shtx {
	float temp;
	float humidity;
} t_shtx;

typedef struct shtx_array {
	t_shtx sensors[8];
} t_shtx_array;

unsigned inline int rotl(unsigned int , int);
unsigned inline int rotr(unsigned int, int);
inline void initComm();
inline void resetComm();
inline unsigned char readByte(unsigned char);
inline unsigned char writeByte(unsigned char);

float measure (int);



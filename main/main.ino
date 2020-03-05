#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
Adafruit_BNO055 bno = Adafruit_BNO055();





//PIN SPI------------------------------------
//#define Nbyte 1
#define _SCK   52
#define _MISO  50
#define _MOSI  51
#define _SS    53


#define S8 31
#define S9 47
#define S10 55
#define S11 59
#define S12 61
#define S13 62




#define KP 0.9 // definisco il proporzionale
#define KI 0.1 // definisco l'integrale
#define KD 1.1 // definisco il derivatospi_readfrom644l()

//array PWM
byte A[3] = {2, 10, 12};
byte B[3] = {3, 11, 13};
byte PWM [3] = {6, 7, 8};


int ang_sen[20] = {0, 15, 30, 45, 60, 75, 90, 112, 135, 157, 180, 203, 225, 248, 270, 285, 300, 315, 330, 345};


float vy;
float vx;
float velocita1 = 0;
float velocita2 = 0;
float velocita3 = 0;
float integral = 0;
float deltaPRE = 0;
float pidfactor = 0;

int compass;
int G_dir=0;
int G_speed=0;
int Max=235;


//VARIABILI RELATIVE ALLA LETTURA DELLA PALLA---------------
byte spi_temp_byte = 0;    // dato grezzo letto da SPI
byte ball_sensor = 0;      // sensore che vede la palla
byte ball_distance = 0;    // distanza della palla con valore da 0 a 6
bool ball_seen = false;    // palla in vista si/no era byte
byte old_s_ball;           // sensore che vedeva la palla in precedenza, paragonato con ball_sensor
unsigned long time_s_ball; // millisecondipassati dal cambiamento di sensore che vede la palla (KEEPER)
int dir = 0;


//VARIABILI RELATIVE ALLA LETTURA DELLE linee---------------
byte line[6] = {A8, A9, A10, A12, A13};
volatile byte state = 0;
byte line4 = 0; //byte di SN, SE, SS, SW
byte memo = 0;

unsigned long stopT = 0;
unsigned long stopT2 = 0;
volatile int flg = 0;

//variabili realtive alla canzone
int speakerPin=22;

void setup() {
  Serial.begin(9600);//spi_readfrom644l();//read the distance and position of the ball

  state = 0x3F; // inizializzo la memoria dei sensori di linea (state)

  pinMode(speakerPin, OUTPUT);

  bno.begin(bno.OPERATION_MODE_IMUPLUS);
  bno.setExtCrystalUse(true);
  initSPI();
  for (int i = 0 ; i < 3 ; i++)
  {
    pinMode(i, OUTPUT);
  }

  for (int K = 0 ; K < 6 ; K++)
  {
    pinMode(line[K], INPUT);
  }

  ADMUX = 7; // scollego i pin dopo A7 dall'ADC
  sei(); //abilita interrupt
  PCICR = 4; //abilita l'interrupt sul change del valore
  PCMSK2 = 0x3F; //abilita l'interrupt solo sui primi sei bit

}


void loop() {
  //song(); //canzone
  readimu();//lettura bussola
  spi_readfrom644l(); //lettura sensori palla
  if(flg==1) contline();//implemento linee ad attacco/difesa
  else ganon(45); 
}

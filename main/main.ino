
//---------------------------INCLUDO LE LIBRERIE-------- 
#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
//----------------------------------
Adafruit_BNO055 bno = Adafruit_BNO055();





//PIN SPI------------------------------------
//#define Nbyte 1
#define _SCK   52
#define _MISO  50
#define _MOSI  51
#define _SS    53
//------------------------------------


//sensori lettura linee pin--------------
#define S8 31
#define S9 47
#define S10 55
#define S11 59
#define S12 61
#define S13 62
//------------------------------------



// definiscoi il pid, guarda il tab
#define KP 0.9 // definisco il proporzionale
#define KI 0.1 // definisco l'integrale
#define KD 1.1 // definisco il derivatospi_readfrom644l()

//array PWM
byte A[3] = {2, 10, 12};
byte B[3] = {3, 11, 13};
byte PWM [3] = {6, 7, 8};
//-----------------------pin per i motori

//angoli sensori per la palla
int ang_sen[20] = {0, 15, 30, 45, 60, 75, 90, 112, 135, 157, 180, 203, 225, 248, 270, 285, 300, 315, 330, 345};
//-----------------

//variabili per il movimento : tab mv
float vy;
float vx;
float velocita1 = 0;
float velocita2 = 0;
float velocita3 = 0;


//---------------------- float per il pid: guardare il tab del pid
float integral = 0;
float deltaPRE = 0;
float pidfactor = 0;
//------------------


//---VARIABILI BUSSOLA----
int compass;
//----------------------



//assegno delle variabili globali 
int G_dir=0;  //variabile globale direzione
int G_speed=0;//variabile globale velocità
int Max=235;  //variabile che sta a intendere la massima velocità dei motori


//VARIABILI RELATIVE ALLA LETTURA DELLA PALLA---------------
byte spi_temp_byte = 0;    // dato grezzo letto da SPI
byte ball_sensor = 0;      // sensore che vede la palla
byte ball_distance = 0;    // distanza della palla con valore da 0 a 6
bool ball_seen = false;    // palla in vista si/no era byte
byte old_s_ball;           // sensore che vedeva la palla in precedenza, paragonato con ball_sensor
unsigned long time_s_ball; // millisecondipassati dal cambiamento di sensore che vede la palla (KEEPER)
int dir = 0;


/* //VARIABILI RELATIVE ALLA LETTURA DELLE linee---------------
byte line[6] = {A8, A9, A10, A11, A12, A13};  //pin dei sensori
volatile byte state = 0;   //variabile di stato
byte line4 = 0;            //byte di SN, SE, SS, SW
byte memo = 0;             //variabile che segna la memoria dei sensori
unsigned long stopT = 0;   //primo conteggio di tempo
unsigned long stopT2 = 0;  //secondo conteggio di tempo
volatile int flg = 0;      // flag per la meomeria
//--------------------------------
*/

//variabili realtive alla canzone
int speakerPin=22;

void setup() {
  Serial.begin(9600);//monitor seriale inizializzazione 
  //spi_readfrom644l();//read the distance and position of the ball
  Serial2.begin(57600);

  state = 0x3F; // inizializzo la memoria dei sensori di linea (state)

  pinMode(speakerPin, OUTPUT);// stabilisco lo speaker come output

  bno.begin(bno.OPERATION_MODE_IMUPLUS);
  bno.setExtCrystalUse(true);
  initSPI(); //inizializzo l'SPI guardare il dedicato tab
  
  for (int i = 0 ; i < 3 ; i++)
  {
    pinMode(i, OUTPUT);  
  }

  for (int K = 0 ; K < 6 ; K++)
  {
    pinMode(line[K], INPUT); //for per i sensori di linea
  }

  ADMUX = 7; // scollego i pin dopo A7 dall'ADC
  sei(); //abilita interrupt
  PCICR = 4; //abilita l'interrupt sul change del valore
  PCMSK2 = 0x3F; //abilita l'interrupt solo sui primi sei bit

}


void loop() {
  //song();             //canzone
  readimu();            //lettura bussola
  readBall();   //lettura sensori palla
  //if(flg==1) contline();//implemento linee ad attacco/difesa
  //else ganon(45);       //attaccante


  if (ball_seen)
    Serial.println(ball_sensor);
  else
    Serial.println(" non vedo palla");
  delay(250);
}
//fate i bravi...

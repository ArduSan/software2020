#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
Adafruit_BNO055 bno=Adafruit_BNO055();

//PIN SPI------------------------------------
//#define Nbyte 1
#define _SCK   52
#define _MISO  50
#define _MOSI  51
#define _SS    53


#define KP 1.6 // definisco il proporzionale
#define KI 0.1 // definisco l'integrale
#define KD 0.9 // definisco il derivatospi_readfrom644l()


byte A[3]={2,10,12};
byte B[3]={3,11,13};
byte PWM [3]={6,7,8};


int ang_sen[20]={0,15,30,45,60,75,90,112,135,157,180,203,225,248,270,285,300,315,330,345};


float vy;
float vx;
float velocita1=0;
float velocita2=0;
float velocita3=0;
float integral=0;
float deltaPRE=0;
float pidfactor=0;
int h;
int spompaciuccioapalloncino;

 
//VARIABILI RELATIVE ALLA LETTURA DELLA PALLA---------------
byte spi_temp_byte = 0;    // dato grezzo letto da SPI
byte ball_sensor = 0;      // sensore che vede la palla
byte ball_distance = 0;    // distanza della palla con valore da 0 a 6
bool ball_seen = false;    // palla in vista si/no era byte
byte old_s_ball;           // sensore che vedeva la palla in precedenza, paragonato con ball_sensor
unsigned long time_s_ball; // millisecondipassati dal cambiamento di sensore che vede la palla (KEEPER)
int dir=0;


//VARIABILI RELATIVE ALLA LETTURA DELLE LINEE---------------
byte line[6]={A8,A9,A10,A12,A13};
volatile byte state=0;
byte pti;
int S8 = 31;
int S9 = 47; 
int S10 = 55;
int S11 = 59;
int S12 = 61;  
int S13 = 62;
long stopT = 0;


void setup() {
  //Serial.begin(9600);
              
  bno.begin(bno.OPERATION_MODE_IMUPLUS);
  bno.setExtCrystalUse(true);
  initSPI();
  
  for(int i = 0 ; i<3 ; i++)
  {
    pinMode(i,OUTPUT);   
  }
  
  for(int K=0 ; K<6 ; K++)
  {
    pinMode(line[K],INPUT);
  }

ADMUX = 7; // scollego i pin dopo A7 dall'ADC
sei(); //abilita interrupt
PCICR = 4; //abilita l'interrupt sul change del valore
PCMSK2 = 0x3F; //abilita l'interrupt solo sui primi sei bit

}


ISR(PCINT2_vect){
  byte lettura;
  lettura = PINK & 63;
  state = lettura;
  
}


void loop() {
  /*Serial.println(state,BIN);
  delay(500);
  */
  readimu(); //leggo la bussola
  //stopsen();
  movsens();
  spi_readfrom644l();//read the distance and position of the ball
  ganon(55);
  
}


void orario(int mot ){  // funzione movimento orario
  digitalWrite(A[mot],HIGH);
  digitalWrite(B[mot],LOW);
}


void antiorario(int mot){ // funzione movimento antiorario
  digitalWrite(A[mot],LOW);
  digitalWrite(B[mot],HIGH);
}


void hearthattack(int mot){
  digitalWrite(A[mot],HIGH);
  digitalWrite(B[mot],HIGH);
  analogWrite(PWM[mot],255);
}

  
void vm(float V, float d) // funzione movimento
{
  vx=V*cos(rad(d));  //vettore asse x
  vy=-V*sin(rad(d)); //vettore asse y

  

  velocita1=sin(rad(60))*vx+cos (rad(60))*vy;//vmot1
  velocita2=sin(rad(180))*vx+cos (rad(180))*vy;//vmot2
  velocita3=sin(rad(300))*vx+cos (rad(300))*vy;//vmot3

 
  pidfactor=upid(); // aggiorno il pid con l'upid

  velocita1+=pidfactor;
  velocita2+=pidfactor;
  velocita3+=pidfactor;

  velocita1= constrain(velocita1, -255 , +255);  //do alle velocita il comando che non possono superare il 255 e non può andare sotto al -255
  velocita2= constrain(velocita2, -255 , +255);
  velocita3= constrain(velocita3, -255 , +255);

  if(velocita1>0) orario(0); 
  else antiorario(0);
  analogWrite(PWM[0],abs(velocita1)); //abs sta per prendo solo i valori assoluti(positivi)
 
  if(velocita2>0) orario(1); 
  else antiorario(1);
  analogWrite(PWM[1],abs(velocita2));
    
  if(velocita3>0) orario(2); 
  else antiorario(2);
  analogWrite(PWM[2],abs(velocita3));

}


float rad(float d){
  return(d*PI)/180;
}


void readimu(){
  imu::Vector<3> euler=bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  spompaciuccioapalloncino=euler.x();
  Serial.println(spompaciuccioapalloncino);
}


float upid(){
  float errorP,errorI,errorD,delta;
  delta=spompaciuccioapalloncino;
  if(delta>180) delta = delta-360;
  errorP = delta*KP;
  errorI = KD*(delta-deltaPRE);
  deltaPRE = delta;
  integral = 0.5 * integral+delta;
  errorI = KI*integral;  
  return errorP+errorI+errorD;
}


//initializing the spi
//pins and setting spi in master mode
void initSPI(){
  pinMode (_SCK, OUTPUT);
  pinMode (_MISO, INPUT);
  pinMode (_MOSI, OUTPUT);
  pinMode (_SS, OUTPUT);
  digitalWrite( _SS, HIGH); // Slave not selected
  SPCR = 81; //ARDUINO MEGA IS THE MASTER!
}//------------------------------------------------------------


//read from the spi slave that gives us the ball position
void spi_readfrom644l() //aggiorna ball_sensor e ball_distance
{
  PORTB = PORTB & 254;  //slave selected = digitalWrite( _SS, LOW)
  spi_temp_byte = spi_tx_rx(255);            //sends 255 to the slave and stores the byte received
  PORTB = PORTB | 1;                         //slave disabled = digitalWrite( _SS, HIGH)
  if (spi_temp_byte == 255) return;          //if the data received is 255, the slave wasn't ready, uses the old ball informations

  ball_sensor = spi_temp_byte & 31;          //extracting the first 5 bits that tell us what ir sensor sees the ball
  ball_distance = (spi_temp_byte & 224) >> 5;//extracting the last 3 bits that tell us the ball distance
  return;
}//------------------------------------------------------------


//general function to receive and send 1 byte to the slave
byte spi_tx_rx( byte d)
{
  SPDR = d;                     //sending 1 byte to the slave
  while ( (SPSR & 128) == 0);   //wait until we got something back as a response

  return SPDR;                  //return the byte received
}//------------------------------------------------------------


void ganon(int plus){
  spi_readfrom644l();
  int dir=0;
  int ball2;
  int ang=ang_sen[ball_sensor];

  if(millis() > stopT)
  {
    if(ang>340 || ang <20)plus-=20;
    if(ang>180)ball2 = ang - 360;
    else ball2 = ang;

    if(ball2>0) dir= ang+plus;
    else dir=ang-plus;

    if(dir<0)dir= dir+360;
    else dir= dir;
    vm(255,dir);
    if(ball_distance==6)vm(0,0);
  } 
      
}

 void gengar(){
    if(ball_distance==0|| ball_distance==1||ball_distance==2)ganon(55);
    if(ball_distance>2){
    if(ball_sensor==0||ball_sensor==19||ball_sensor==1)vm(0,0);
    else if(ball_sensor>=2 && ball_sensor<5)vm(255,90);
    else if(ball_sensor<= 18&& ball_sensor>15)vm(255,270);
    else ganon(55);
    }
    
    
 }

void movsens(){
  if(state==S8 || state==S13) vm(255,200);
  if(state==S9) vm(255,135);
  if(state==S10) vm(255,10);
  if(state==S11) vm(255,290);
  if(state==S12) vm(255,255);
}


void stopsen(){
  if(state == S8 || state == S9 || state == S10 || state == S11 || state == S12 || state == S13){
  Interrupt(200);
  hearthattack(0);
  hearthattack(1);
  hearthattack(2);
  }
  
}

 
void Interrupt(int sos) {
  stopT = millis() + sos;   
}

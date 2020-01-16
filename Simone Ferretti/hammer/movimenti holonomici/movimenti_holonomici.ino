byte A[3]={2,10,12};
byte B[3]={3,11,13};
byte PWM [3]={6,7,8};

float vy;
float vx;
float velocita1;
float velocita2;
float velocita3;




void setup() {

  for(int i = 0 ; i<3 ; i++)
  {
    pinMode(i,OUTPUT);
  }
  


  

}

void loop() {
  vm(100, 0);
 

}
void orario(int mot ){
  digitalWrite(A[mot],HIGH);
  digitalWrite(B[mot],LOW);
}
void antiorario(int mot){
  digitalWrite(A[mot],LOW);
  digitalWrite(B[mot],HIGH);
}


void vm(float V, float d)
{
  float movimento;
  
  vx=V*cos(rad(d));
  vy=-V*sin(rad(d));

  velocita1=sin(rad(60))*vx+cos (rad(60))*vy;//vmot1
  velocita2=sin(rad(180))*vx+cos (rad(180))*vy;//vmot2
  velocita3=sin(rad(270))*vx+cos (rad(270))*vy;//vmot3

  if(velocita1>0)
  {
    orario(0); 
  }
  else
  {
    antiorario(0);
  }
  analogWrite(PWM[0],velocita1);
    if(velocita2>0)
  {
    orario(1); 
  }
  else
  {
    antiorario(1);
  }
  analogWrite(PWM[1],velocita2);
    if(velocita3>0)
  {
    orario(2); 
  }
  else
  {
    antiorario(2);
  }
  analogWrite(PWM[2],velocita3);
}

float rad(float d)
{
  return(d*PI)/180;
}

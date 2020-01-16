int A [3] = {2,12,10};
int B [3] = {3,13,11};
int PWM [3] = {6,8,7};
float vy;
float vx;
float velocita1;
float velocita2;
float velocita3;




void setup() 
{
for(int i=0; i<3; i++)
  {
  pinMode(A[i],OUTPUT);
  pinMode(B[i],OUTPUT);
  pinMode(PWM[i],OUTPUT); 
  }
}


void loop() 
{
  h++
  if(h<3000) mov(100,0);
  else if(h>3000 && h<6000) mov(100,100);
  if(h>6000) h=0;
}

void orario(int mot)
{
  digitalWrite(A[mot],HIGH);
  digitalWrite(B[mot],LOW);
}
void anitiorario(int mot)
{
  digitalWrite(A[mot],LOW);
  digitalWrite(B[mot],HIGH);
}



void vm(float V, float d)
{
  float movimento;
  
  vx=V*cos(rad(d));
  vy=-V*sin(rad(d));
  
  velocita1=sin(rad(60))*vx+cos (rad(60))*vy;
  velovita2=sin(rad(180))*vx+cos (rad(180))*vy;
  velocita3=sin(rad(270))*vx+cos (rad(270))*vy;
  
  
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
  if(velocita 1<0)
  {
    antiorario(0);
  }
  else
  {
    orario(0);
  }
  analogWrite(PWM[0],velocita1);
  if (velocita2<0)
  {
    antiorario(1);
  }
  else
  {
    orario(1);
  }
  analogWrite(PWM[1],velocita2);
  if(velocita3<0)
  {
    antiorario(1);
  }
  else
  {
    orario(1);
  }
  analogWrite(PWM[2],velocita3);
}

float rad(float d)
{
  return(d*PI)/180;
}
  
  
  
  
  
  
  


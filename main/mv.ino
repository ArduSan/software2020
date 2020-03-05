// verso orario
 void orario(int mot ) { // funzione movimento orario
  digitalWrite(A[mot], HIGH);
  digitalWrite(B[mot], LOW);
}


//clockwise verse
void antiorario(int mot) { // funzione movimento antiorario
  digitalWrite(A[mot], LOW);
  digitalWrite(B[mot], HIGH);
}

// stop
void heartattack(int mot) {
  digitalWrite(A[mot], HIGH);
  digitalWrite(B[mot], HIGH);
  analogWrite(PWM[mot], 235);
}
void folk(int mot){
    digitalWrite(A[mot], LOW);
  digitalWrite(B[mot], LOW);
  analogWrite(PWM[mot], 0);
}

void stopm(){
  G_dir=0;
  G_speed=0;
  /*folk(0);
  folk(1);
  folk(2);*/
  
}
void vm(float V, float d) // funzione movimento
{
  vx = V * cos(rad(d)); //vettore asse x
  vy = -V * sin(rad(d)); //vettore asse y



  velocita1 = sin(rad(60)) * vx + cos (rad(60)) * vy; //vmot1
  velocita2 = sin(rad(180)) * vx + cos (rad(180)) * vy; //vmot2
  velocita3 = sin(rad(300)) * vx + cos (rad(300)) * vy; //vmot3


  pidfactor = upid(); // aggiorno il pid con l'upid

  velocita1 += pidfactor;
  velocita2 += pidfactor;
  velocita3 += pidfactor;

  velocita1 = constrain(velocita1, -235 , +235); //do alle velocita il comando che non possono superare il 255 e non può andare sotto al -255
  velocita2 = constrain(velocita2, -235 , +235);
  velocita3 = constrain(velocita3, -235 , +235);

  if (velocita1 > 0) orario(0);
  else antiorario(0);
  analogWrite(PWM[0], abs(velocita1)); //abs sta per prendo solo i valori assoluti(positivi)

  if (velocita2 > 0) orario(1);
  else antiorario(1);
  analogWrite(PWM[1], abs(velocita2));

  if (velocita3 > 0) orario(2);
  else antiorario(2);
  analogWrite(PWM[2], abs(velocita3));

}


float rad(float d) {
  return (d * PI) / 180;
}

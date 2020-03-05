//state of read
ISR(PCINT2_vect) {  //funzione di interrupt
  byte lettura;
  lettura = PINK & 63;
  state &= lettura;
  if (state != 63) flg = 1; //se flag sensor è 1 allora vede le linee
}


/*void escape() {  //funzione che mi sposta dalle linee
  switch (state) {

    case S8:
      G_dir = 180;
      G_speed = Max;

      break;

    case S13:
      G_dir = 180;
      G_speed = Max;

      break;

    case S9:
      G_dir = 90;
      G_speed = Max;

      break;

    case S10:
      G_dir = 0;
      G_speed = Max;

      break;



    case S11:
      G_dir = 0;
      G_speed = Max;

      break;

    case S12:
      G_dir = 270;
      G_speed = Max;

      break;

  }

}
*/

void bit_line() { //what he does if he see a line
  //SN
  if ((state & 0b00100001) == 0b00100001) bitClear(line4,0);
  else bitSet(line4, 0);

  //SE
  if ((state & 0b00010000) == 0b00010000) bitClear(line4,3);
  else bitSet(line4, 3);

  //SS
  if ((state & 0b00001100) == 0b00001100) bitClear(line4,2);
  else bitSet(line4, 2);

  //SW
  if ((state & 0b00000010) == 0b00000010) bitClear(line4,1);
  else bitSet(line4, 1);

memo = memo | line4;

  switch(memo){
    case 0: //0000
    G_dir=0;
    G_speed=0;
    beep(speakerPin, 1175, 200);
    delay(250);
    break;

    case 1: //0001
    G_dir=180;
    G_speed=Max;
    break;

    case 2: //0010
    G_dir=270;
    G_speed=Max;
    break;

    case 3: //0011
    G_dir=225;
    G_speed=Max;
    break;

    case 4: //0100
    G_dir=0;
    G_speed=Max;
    break;

    case 5: //0101
    G_dir=90;
    G_speed=Max;
    break;

    case 6: //0110
    G_dir=315;
    G_speed=Max;
    break;

    case 7: //0111
    G_dir=270;
    G_speed=Max;
    break;

    case 8: //1000
    G_dir=90;
    G_speed=Max;
    break;

    case 9: //1001
    G_dir=135;
    G_speed=Max;
    break;

    case 10: //1010
    G_dir=0;
    G_speed=Max;
    break;
    
    case 11: //1011
    G_dir=180;
    G_speed=Max;
    break;

    case 12: //1100
    G_dir=45;
    G_speed=Max;
    break;

    case 13: //1101
    G_dir=90;
    G_speed=Max;
    break;

    case 14: //1110
    G_dir=0;
    G_speed=Max;
    break;

    case 15: //1111
    G_dir=0;
    G_speed=0;
    break;
  }

  vm(G_speed,G_dir);//assegno il movimento
  
}



void contline(){
  if(stopT==0){
    stopT = millis() + 100;
    stopT2=0;
    //Serial.println("start");
  }

  if(stopT>millis()){ // freno per 100 ms
    /*heartattack(0);
    heartattack(1);
    heartattack(2);*/
    stopm();
    stopT2 = millis() + 200;
    //Serial.println("stop");
    }

  if(stopT2>millis()) bit_line();//Serial.println("scap");

  if(stopT2 != 0 && stopT2<millis()){
    stopT = 0;
    stopT2 = 0;
    flg=0;
    memo = 0;
    state = 0b00111111;
    //Serial.println("giuoco");
  }
}

ISR(PCINT2_vect) {
  byte lettura;
  lettura = PINK & 63;
  state = lettura;
  stato = state;
  if (state != 63) flagsensor = 1;
  if (state == 63) flagsensor = 0;

}


void movsens() {
  if (state == S8 || state == S13) {
    vm(255, 200);
    MuOvItIcAzZo();
  }

  if (state == S9) {
    vm(255, 135);
    MuOvItIcAzZo();
  }
  
  if (state == S10) {
    vm(255, 10);
    MuOvItIcAzZo();   
  }
  
  if (state == S11) {
    vm(255, 290);
    MuOvItIcAzZo();
  }

  if (state == S12) {
    vm(255, 255);
    MuOvItIcAzZo();
   
  }
}


void lemuri(){
  switch(stato){
    case S8: 
    vm(255, 200);
    break;
    
    case S13:
    vm(255, 200);
    break;

    case S9:
    vm(255,135);
    break;

    case S10:
    vm(255,10);
    break;

    case S11:
    vm(255,310);
    break;

    case S12:
    vm(255,255);
    break;
  }
}


void sPoStAtIcAzZo() {
  if (flagsensor == 1) lemuri();
  for(int k=0;k<500;k++){
    if(k<499) lemuri();
    if(k>=499){
      ganon(55);
      k=0;
    }
  }
}


void MuOvItIcAzZo() {
  if (flagsensor == 0) ganon(55);
}

void pArAcAzZo(){  
  if(flagsensor==0)gengar();
}

//state of read
ISR(PCINT2_vect) {
  byte lettura;
  lettura = PINK & 63;
  state = lettura;
  stato = state;
  if (state != 63) flg = 1; //se flag sensor è 1 allora vede le linee
  if (state == 63) flg = 0; //se flag sensor è 0 allora non vede le linee
}


void lemuri(){
  switch(stato){
    case S8:
    G_dir=180;
    G_speed=Max;
    //vm(255, 180);
    break;
    
    case S13:
    G_dir=180;
    G_speed=Max;
    //vm(255, 180);
    break;
    
    case S9:
    G_dir=90;
    G_speed=Max;
    //vm(255,90);
    break;

    case S10:
    G_dir=0;
    G_speed=Max;
    //vm(255,0);
    break;

    case S11:
    G_dir=0;
    G_speed=Max;
    //vm(255,0)
    break;

    case S12:
    G_dir=270;
    G_speed=Max;
    //vm(255,270);
    break;
      
  }
  
}


void morcock(){
  if(flg==1){
    if(stopT==0)    stopT=millis()+100,Serial.println("start");
  }    
     if(stopT>millis()){
      Serial.println("freno");
      stopm();
    }
    if(stopT!=0 && stopT<millis()){
      Serial.println("restart");
      stopT=0;
      }
  }
  /*if(sotpT>millis() && flg==0){
    folk[0];
      folk[1];
      folk[2];
  }
  if(stopT<millis()){
    if(flg==1){
      stopT2=millis()+200;
      if(stopT2>millis()) lemuri();
}      
   else if(stopT2>millis()&&flg==0) lemuri();
   else if(stopT2<millis()&&flg==0) {
    ganon(55);
    stopT=0; 
   }
  }
}*/


void morcock2() {
int stopF;
  
  if(flg==1){
    stopF=millis()+50;
    stopm();  
  }

  if(flg==1 && stopF>millis()){
    stopT=millis()+100;
    lemuri();
  }

  if(flg==0 && stopT>millis()) lemuri();

  if(flg==0 && stopT<millis()) ganon(55);
  
}


/*void sveltina(){
   
  if(flg==1){
    stopT=millis()+100;
    if(stopT>millis())lemuri();
  }
  
   else if(stopT>millis()&&flg==0) lemuri();
   else if(stopT<millis()&&flg==0) ganon(55);
      
}*/
    


//non uscire dalle line porca madonna


/*void ahah(){
  
  while(flg==1){
  lemuri();
  stopT=millis()+200;
  }
  if(stopT<millis()){
    if(flg==0)ganon(55);
  }
}*/
 

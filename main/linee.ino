//state of read
ISR(PCINT2_vect) {  //funzione di interrupt
  byte lettura;
  lettura = PINK & 63;
  state = lettura;
  stato = state;
  if (state != 63) flg = 1; //se flag sensor è 1 allora vede le linee
  if (state == 63) flg = 0; //se flag sensor è 0 allora non vede le linee
}


void escape(){   //funzione che mi sposta dalle linee
  switch(stato){

    case S8:
    G_dir=180;
    G_speed=Max;
   
    break;
       
    case S13:
    G_dir=180;
    G_speed=Max;
   
    break;
    
    case S9:
    G_dir=90;
    G_speed=Max;
   
    break;

    case S10:
    G_dir=0;
    G_speed=Max;
   
       break;


    
    case S11:
    G_dir=0;
    G_speed=Max;
   
    break;

    case S12:
    G_dir=270;
    G_speed=Max;
    
    break;
      
  }
  
}


void contline(){//what he does if he see a line 

  if(flg==0 && stopT==0 && stopT2==0)ganon(55); //se non vede le linee fa l'attaccante
  
  if(flg==1){
    if(stopT==0)    stopT=millis()+500;//Serial.println("start");//inizio il primo contatore
  }    
     if(stopT>millis()){
      //Serial.println("freno");
      stopm();                      //mi fermo per 100 ms
    }
    if(stopT!=0 && stopT<millis()){
      //Serial.println("restart");
      stopT2=millis()+900;             //inizio il secondo contatore 
      stopT=0;                         //azzero la prima variabile del primo contatore
      }
      if(stopT2!=0 && stopT2> millis())escape();//Serial.println("me ne sto a anna");   //me ne vado per 200 ms
      if(stopT2!=0&& stopT2<millis())ganon(55),stopT2=0;//Serial.println("palla");     //quando finiscono i 200ms allora torno attaccante e azzero la variabile del secondo contatore
}
  

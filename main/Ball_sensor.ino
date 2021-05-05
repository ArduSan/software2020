void readBall(){
  byte dummy;
  byte rxdata;
  if(Serial2.available()==0) return;

  
  while(Serial2.available()) 
    rxdata=Serial2.read();

  ball_sensor = rxdata&0b00001111;      // sensore che vede la palla
  ball_distance = 0;    // distanza della palla con valore da 0 a 6
  if(rxdata>127) ball_seen = true;
  else ball_seen = false;

}

void setup() {
  Serial.begin(57600);
  Serial2.begin(57600);
  
}

void loop() {
  char ch;
  if(Serial.available()){
    ch=Serial.read();
    Serial2.write(ch);
  }

  if(Serial2.available()){
    ch=Serial2.read();
    Serial.write(ch);
  }
}

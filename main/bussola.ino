void readimu() {
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  compass = euler.x();
  /*Serial.println(compass);
  delay(250);
  */
}

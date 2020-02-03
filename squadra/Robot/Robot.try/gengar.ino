void gengar() {
  if (ball_distance == 0 || ball_distance == 1)ganon(55);
  if (ball_distance > 1) {
    if (ball_sensor == 0 || ball_sensor == 19 || ball_sensor == 1)vm(0, 0);
    else if (ball_sensor >= 2 && ball_sensor < 5)vm(255, 90);
    else if (ball_sensor <= 18 && ball_sensor > 15)vm(255, 270);
    else ganon(55);
  }


}


void ganon(int plus) {
  spi_readfrom644l();
  int dir = 0;
  int ball2;
  int ang = ang_sen[ball_sensor];

  if(flagsensor == 0) {
  if (ang >= 340 || ang <= 20)  vm(240,ang);//plus -= 20;
    if (ang > 20 && ang <= 80)  vm(240,ang+30);//plus -= 20;
    if (ang < 340 && ang >= 280)  vm(240,ang-30);//plus -= 20;

    if (ang > 80 && ang <= 150)  vm(240,180);//plus -= 20;
    if (ang < 280 && ang >= 210)  vm(240,180);//plus -= 20;

    if (ang > 150 && ang < 210)  vm(240,140);//plus -= 20;

    if(ball_distance == 6) vm(0,0);



    return;



  //if (millis() > stopT) {
  if (ang > 180)ball2 = ang - 360;
  else ball2 = ang;

  if (ball2 > 0) dir = ang + plus;
  else dir = ang - plus;

  if (dir < 0)dir = dir + 360;
  else dir = dir;
  vm(255, dir);
  if (ball_distance == 6)vm(0, 0);
  }

}

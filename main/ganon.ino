
void ganon(int plus) {
  spi_readfrom644l();
  int dir = 0;
  int ball2;
  int ang = ang_sen[ball_sensor];

  if(flg == 0) {
  if (ang >= 340 || ang <= 20) {
    G_dir=ang;
    G_speed=Max;
    
  }
    if (ang > 20 && ang <= 80)  {
      G_dir=ang+30;
      G_speed=Max;
      
    }
    if (ang < 340 && ang >= 280){
      G_dir=ang-30;
      G_speed=Max;
      
    }

    if (ang > 80 && ang <= 150){
      G_dir=180;
      G_speed=Max;
      
    }
    if (ang < 280 && ang >= 210)  {
      G_dir=180;
      G_speed=Max;
      
    }

    if (ang > 150 && ang < 210) {
      G_dir=140;
      G_speed=Max;
      
    }

    if(ball_distance == 6) {
      stopm();
      
    }
  }
}


//funzione del Portiere 

void gengar() {
  if (ball_distance == 0 || ball_distance == 1)ganon(55);  //Se la palla è vicina fa da attaccante
  if (ball_distance > 1) {

    //do le direzioni di moviemento per il portiere nel caso in cui la palla è lontana 
    if (ball_sensor == 0 || ball_sensor == 19 || ball_sensor == 1){ 
      stopm();
    }
    else if (ball_sensor >= 2 && ball_sensor < 5){ // assegno un determinato angolo di sensori e in base a quello si muove il robot
      G_dir=90;
      G_speed=Max;
      
    }
    else if (ball_sensor <= 18 && ball_sensor > 15){ // assegno un determinato angolo di sensori e in base a quello si muove il robot 
      G_dir=270;
      G_speed=Max;
      
    }
    else ganon(55);//assegno ganon per sicurezza 
  }

  vm(G_speed,G_dir);//assegno il movimento
  
}

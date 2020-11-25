//FUNZIONE ATTACCANTE 

void ganon(int plus) {                       //vado a inizializzare la funzione ganon
  spi_readfrom644l();
  int dir = 0;
  int ball2;
  int ang = ang_sen[ball_sensor];
  
//VADO A DEFINIRE PER OGNI GRUPPO DI SENSORI CHE VEDE LA PALLA UN ANGOLO DI MOVIMENTO SPECIFICO

  if(flg == 0) {
  if (ang >= 340 || ang <= 20){              //qua si va a definire l'angolo in un range di >=340 <=20
    G_dir=ang;
    G_speed=Max;
    
  }
    if (ang > 20 && ang <= 80){              //qua si va a definire l'angolo in un range di >20 <=80
      G_dir=ang+30;
      G_speed=Max;
      
    }
    if (ang < 340 && ang >= 280){            //qua si va a definire l'angolo in un range di <340 >=280
      G_dir=ang-30;
      G_speed=Max;
      
    }

    if (ang > 80 && ang <= 150){             //qua si va a definire l'angolo in un range di >80 <=150
      G_dir=180;
      G_speed=Max;
      
    }
    if (ang < 280 && ang >= 210){            //qua si va a definire l'angolo in un range di <280 >=210
      G_dir=180;
      G_speed=Max;
      
    }

    if (ang > 150 && ang < 210){             //qua si va a definire l'angolo in un range di >150 <210
      G_dir=140;
      G_speed=Max;
      
    }

    if(ball_distance == 6){                  //se i sensori vedono la palla troppo distante, il movimento si blocca
      stopm();
      
    }
  }
  
  vm(G_speed,G_dir);                         //assegno il movimento
  
}

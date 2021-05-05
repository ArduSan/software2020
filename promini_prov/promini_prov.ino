#define S0 7
#define S1 6
#define S2 5 
#define S3 4
#define S4 A2
#define S5 A3
#define S6 12
#define S7 2
#define S8 3
#define S9 10
#define S10 8
#define S11 9

int contS[12]; //tutti i pin
int SMax=0; 
int sogM=250; // soglia massima del valore 
int index=0;
int dist=0;

void setup() {
  Serial.begin(9600);// velocità proiettazione  a monitor seriale
  
  pinMode(S0,INPUT); // stabilisco che il segnale dei sensori è input
  pinMode(S1,INPUT);
  pinMode(S2,INPUT);
  pinMode(S3,INPUT);
  pinMode(S4,INPUT);
  pinMode(S5,INPUT);
  pinMode(S6,INPUT);
  pinMode(S7,INPUT);
  pinMode(S8,INPUT);
  pinMode(S9,INPUT);
  pinMode(S10,INPUT);
  pinMode(S11,INPUT);
}

void loop() {
  for(int i=0;i<12;i++){
    contS[i]= 0; // azzero il valore per riassegnarlo
  }

  for(int i = 0; i < 250; i++) { 
  contS[0] += (!digitalRead(S0)); // digital read è negato
  contS[1] += (!digitalRead(S1));
  contS[2] += (!digitalRead(S2));
  contS[3] += (!digitalRead(S3));
  contS[4] += (!digitalRead(S4));
  contS[5] += (!digitalRead(S5));
  contS[6] += (!digitalRead(S6));
  contS[7] += (!digitalRead(S7));
  contS[8] += (!digitalRead(S8));
  contS[9] += (!digitalRead(S9));
  contS[10] += (!digitalRead(S10));
  contS[11] += (!digitalRead(S11));
  }

  SMax = 0;
  index = 0;
  for(int i=0;i<12;i++){
    if(contS[i]>= sogM){
      contS[i]=0;  // se il contatore è maggiore della soglia massima lo azzero poiché sarebbe un errore
    }
    if(contS[i]>SMax){
      SMax=contS[i]; //se il numero del contatore più alto rilevato in quell' istante è 
      index=i;       //maggiore del numero più alto visto nella storia alllora lo cambio e lo imposto come massimo 
    } 
  }

  Serial.print("Sens: ");// stampo su seriale quale sensore sta captando le frequenze
  Serial.println(index);
  Serial.print(" ");
  Serial.println(contS[index]);
  delay(200);
} 
/*
  //da ora vedo le distanze e le stabilisco 
  if(SMax<32){ // separo quindi le distanze in piccoli spazi da controllare 
    dist=0;
  }
  else if(SMax>32 && nMax<64){
    dist=1;
  }
  else if(SMax>64 && SMax<96){
    dist=2;
  }
  else if(SMax>96 && SMax<128){
    dist=3;
  }
  else if(SMax>128 && SMax<160){
    dist=4;
  }
  else if(SMax>160 && SMax<192){
    dist=5;
  }
  else if(SMax>192 && SMax<224){
    dist=6;
  }
  else if(nMax>224 && nMax<256){
    dist=7;
  }
      Serial.println(dist); // printa la distanza
    delay(200);
}
*/

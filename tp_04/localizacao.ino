/*void localiza(){

  int parada1 = 0;
  int parada2 = 0;

  int valor_LDR_DF;
  int previous_state;
  int LDR_DF_MAX = 0;
  int LDR_DF_MIN = 1024;
  int previous_diff;

  previous_state = analogRead(LDR_DF);
  previous_diff = 0;
  motor1->run(FORWARD);
  motor2->run(BACKWARD);
  motor1->setSpeed(mot1);
  motor2->setSpeed(mot2);

  while(parada1 == 0 || parada2 == 0){

    valor_LDR_DF = analogRead(LDR_DF);

    //REGISTRO DA LEITURA MÁXIMA

    if(valor_LDR_DF > LDR_DF_MAX){
      LDR_DF_MAX = valor_LDR_DF;
    }

    if(valor_LDR_DF < LDR_DF_MIN){
      LDR_DF_MIN = valor_LDR_DF;
    }

    if(valor_LDR_DF - previous_state > 0 && previous_diff < 0){
      parada1 = 1;
      parada2 = 1;
      motor1->run(RELEASE);
      motor2->run(RELEASE);
    }
    if(valor_LDR_DF - previous_state < 0 && previous_diff > 0){
      parada1 = 1;
      parada2 = 1;
      motor1->run(RELEASE);
      motor2->run(RELEASE);
    }

    previous_diff = valor_LDR_DF - previous_state;
    previous_state = valor_LDR_DF;
    delay(100);  
    }
} */


void localiza(int giros, int pin1, int pin2){
   int counter1 = 0;
   int counter2 = 0;
   
   byte previousState1 = digitalRead(pin1);
   byte previousState2 = digitalRead(pin2);
   
   int parada1 = 0;
   int parada2 = 0;
   
   int leitura_max = 810;
   int leitura_min = 150;
   
   int valor_LDR_DF;
   int LDR_DF_MAX = 0;
   int LDR_DF_MIN = 1024;
   int counters_LDR_DF_MAX[2];
   int counters_LDR_DF_MIN[2];
   
   int spd1 = 90, spd2 = 185;
   
   motor1->run(FORWARD);
   motor2->run(BACKWARD);
   motor1->setSpeed(spd1);
   motor2->setSpeed(spd2);
   
   while(parada1 == 0 || parada2 == 0){
   //LEITURA DE CADA PINO
   byte currentState1 = digitalRead(pin1);
   byte currentState2 = digitalRead(pin2);
   
   valor_LDR_DF = analogRead(LDR_DF);
   
   //INCREMENTO DOS CONTADORES DE CADA RODA
   if(currentState1 != previousState1){
   counter1++;
   previousState1 = currentState1; 
   }
   if(currentState2 != previousState2){
   counter2++;
   previousState2 = currentState2; 
   }
   
   //REGISTRO DA LEITURA MÁXIMA
   
   if(valor_LDR_DF > LDR_DF_MAX){
   LDR_DF_MAX = valor_LDR_DF;
   counters_LDR_DF_MAX[0] = counter1;
   counters_LDR_DF_MAX[1] = counter2;
   }
   
   if(valor_LDR_DF < LDR_DF_MIN){
   LDR_DF_MIN = valor_LDR_DF;
   counters_LDR_DF_MIN[0] = counter1;
   counters_LDR_DF_MIN[1] = counter2;
   }
   /*
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print(valor_LDR_DF);
   lcd.setCursor(0,1);
   lcd.print(LDR_DF_MAX);
   lcd.setCursor(9,1);
   lcd.print(LDR_DF_MIN);*/
   
   
   //PARADA INDIVIDUAL DE CADA RODA
   if(counter1>giros && parada1 == 0){
   motor1->setSpeed(0);
   parada1 = 1;
   }
   if(counter2>giros && parada2 == 0){
   motor2->setSpeed(0);
   parada2 = 1;
   }
   }
   
   //RELOCALIZA
   
   parada1 = 0;
   parada2 = 0;
   
   counter1 = 0;
   counter2 = 0;
   
   motor1->run(BACKWARD);
   motor2->run(FORWARD);
   motor1->setSpeed(spd1);
   motor2->setSpeed(spd2);
   
   int giros1, giros2;
   
   if((leitura_max - LDR_DF_MAX) < (LDR_DF_MIN - leitura_min)){
   giros1 = giros - counters_LDR_DF_MAX[0];
   giros2 = giros - counters_LDR_DF_MAX[1];
   }
   else{
   giros1 = giros - counters_LDR_DF_MIN[0];
   giros2 = giros - counters_LDR_DF_MIN[1];
   }
   
   
   while(parada1 == 0 || parada2 == 0){
   //LEITURA DE CADA PINO
   byte currentState1 = digitalRead(pin1);
   byte currentState2 = digitalRead(pin2);
   
   //INCREMENTO DOS CONTADORES DE CADA RODA
   if(currentState1 != previousState1){
   counter1++;
   previousState1 = currentState1; 
   }
   if(currentState2 != previousState2){
   counter2++;
   previousState2 = currentState2; 
   }
   
   //PARADA INDIVIDUAL DE CADA RODA
   if(counter1>giros1 && parada1 == 0){
   motor1->setSpeed(0);
   parada1 = 1;
   }
   if(counter2>giros2 && parada2 == 0){
   motor2->setSpeed(0);
   parada2 = 1;
   }
   }
   
}



void LDRDF(){
  int valor;
  digitalWrite(LED_B, HIGH);
  digitalWrite(LED_R, HIGH);
  digitalWrite(LED_G, HIGH);
  while(1){
    valor = analogRead(LDR_G);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(valor);
    delay(100);
  }
}

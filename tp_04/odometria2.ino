void motor_giros(int giros, int pin1, int pin2){
  int counter1 = 0;
  int counter2 = 0;

  byte previousState1 = digitalRead(pin1);
  byte previousState2 = digitalRead(pin2);

  int parada1 = 0;
  int parada2 = 0;

  motor1->run(FORWARD);
  motor2->run(FORWARD);
  motor1->setSpeed(mot1);
  motor2->setSpeed(mot2);

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
    if(counter1>giros && parada1 == 0){
      motor1->setSpeed(0);
      parada1 = 1;
    }
    if(counter2>giros && parada2 == 0){
      motor2->setSpeed(0);
      parada2 = 1;
    }
    
    Serial.print(counter1);
    Serial.print("\t");
    Serial.println(counter2);
  }
}




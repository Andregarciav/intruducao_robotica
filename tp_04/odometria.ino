void giros(int giros){
  int counter = 0;

  byte previousState = digitalRead(BB_G);

  int parada = 0;

  while(parada == 0){
    //LEITURA DE CADA PINO
    byte currentState = digitalRead(BB_G);

    //INCREMENTO DOS CONTADORES
    if(currentState != previousState){
      counter++;
      previousState = currentState; 
    }

    //PARADA
    if(counter>=giros && parada == 0){
      parada = 1;
    }
    //Serial.println(counter);
  }
}




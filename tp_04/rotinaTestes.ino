void teste(){
  //localiza(75, BB_L, BB_R);
  delay(2000);
  motor1->run(BACKWARD);
  motor2->run(FORWARD);
  motor1->setSpeed(mot1);
  motor2->setSpeed(mot2);
  delay(2000);
  //giros(1000);
  //delay(400);
  motor1->run(RELEASE);
  motor2->run(RELEASE);
  //motor2->setSpeed(0);
  delay(2000);
  //motor1->run(FORWARD);
  //delay(400);
  //motor1->run(RELEASE);
}

void parada(){
  motor1->run(RELEASE);
  motor2->run(RELEASE);
  motor1->setSpeed(0);
  motor2->setSpeed(0);
}

void liga_motores(){
  motor1->run(FORWARD);
  motor2->run(FORWARD);
  motor1->setSpeed(mot1);
  motor2->setSpeed(mot2);
}

void liga_leds(){
  digitalWrite(LED_B, HIGH);
  digitalWrite(LED_R, HIGH);
  digitalWrite(LED_G, HIGH);
}

void desliga_leds(){
  digitalWrite(LED_B, LOW);
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, LOW);
}


#define num_medias 20
#define tolerancia_ldr 30.0


int calib_line_follow[2]; //PRIMEIRA POSICAO CALIBRACAO ESQUERDA, SEGUNDA POSICAO CALIB DIREITA

int mediaLeituras (int vezes, int pin){
  int sum = 0;
  int leitura;

  for(int i = 0; i < vezes; i++){
    leitura = analogRead(pin);
    sum += leitura;
    delay(10);
  }
  return (sum / vezes);
}

void calibra_line_follow(){
  //Calibra os LDRs de Line Follow

    //LDR L
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Calibrando");
  lcd.setCursor(0,1);
  lcd.print("LDR L");
  delay(2000);
  calib_line_follow[0] = mediaLeituras(num_medias, LDR_L);
  calib_line_follow[0] *= (1.0 + (tolerancia_ldr/100.0));
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Calib LDR L:");
  lcd.setCursor(0,1);
  lcd.print(calib_line_follow[0]);
  delay(5000);

  //LDR L
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Calibrando");
  lcd.setCursor(0,1);
  lcd.print("LDR R");
  delay(2000);
  calib_line_follow[1] = mediaLeituras(num_medias, LDR_R);
  calib_line_follow[1] *= (1.0 + (tolerancia_ldr/100.0));
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Calib LDR R:");
  lcd.setCursor(0,1);
  lcd.print(calib_line_follow[1]);
  delay(5000);

  lcd.clear();
}

void line_follow(){
  motor1->run(FORWARD);
  motor2->run(FORWARD);
  motor1->setSpeed(mot1);
  motor2->setSpeed(mot2);

  int reduz1 = 75;
  int reduz2 = 100;
  while(1){
    valor_LDR_R = analogRead(LDR_R);
    valor_LDR_L = analogRead(LDR_L);

    lcd.setCursor(0,0);
    lcd.print(valor_LDR_L);
    lcd.setCursor(8,0);
    lcd.print(valor_LDR_R);

    if(valor_LDR_L < calib_line_follow[0]){
      motor1->setSpeed(0);
      while(valor_LDR_L < calib_line_follow[0]){
        //delay(1000);
        valor_LDR_L = analogRead(LDR_L);
        valor_LDR_R = analogRead(LDR_R);

        lcd.setCursor(0,0);
        lcd.print(valor_LDR_L);
        lcd.setCursor(8,0);
        lcd.print(valor_LDR_R);
      }
      motor1->setSpeed(mot1);
    }
    if(valor_LDR_R < calib_line_follow[1]){
      motor2->setSpeed(0);
      while(valor_LDR_R < calib_line_follow[1]){
        //delay(1000);
        valor_LDR_L = analogRead(LDR_L);
        valor_LDR_R = analogRead(LDR_R);

        lcd.setCursor(0,0);
        lcd.print(valor_LDR_L);
        lcd.setCursor(8,0);
        lcd.print(valor_LDR_R);
      }
      motor2->setSpeed(mot2);
    }
    if(valor_LDR_L < calib_line_follow[0] && valor_LDR_R < calib_line_follow[1]){
      motor1->setSpeed(0);
      while(valor_LDR_L < calib_line_follow[0] && valor_LDR_R < calib_line_follow[1]){
        //delay(1000);
        valor_LDR_L = analogRead(LDR_L);
        valor_LDR_R = analogRead(LDR_R);

        lcd.setCursor(0,0);
        lcd.print(valor_LDR_L);
        lcd.setCursor(8,0);
        lcd.print(valor_LDR_R);
      }
      motor1->setSpeed(mot1);
    }
  }
}







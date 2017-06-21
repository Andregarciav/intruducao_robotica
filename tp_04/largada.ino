void largada(){
  int leitura;
  leitura = analogRead(LDR_start);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Esperando luz");
  while(leitura < 800){
    leitura = analogRead(LDR_start);
  }
}



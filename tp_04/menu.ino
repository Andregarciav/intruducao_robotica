int menu(int x,int y){
  //switch q define as opcoes do menu
  switch(x){
  case 1://caso 1 quadrado
    lcd.setCursor(0,1);
    lcd.print ("Fecha garra"); 
    lcd.print ("          ");
    delay(500);
    if(y==1){     //select acionado
      agarra_bloco();
      delay(2000);
      //solta_bloco();
    }
    break;
  case 2: //para selecinar um triangulo
    lcd.setCursor(0,1);
    lcd.print ("Odometria"); 
    lcd.print ("          ");
    delay(500);
    if(y==1){       //select acionado
      motor1->run(FORWARD);
      motor1->setSpeed(mot1);
      giros(300);
      motor1->run(RELEASE);
    }
    break;
  case 3:  // para selecionar uma reta
    lcd.setCursor(0,1);
    lcd.print ("Abre garra"); 
    lcd.print ("          ");
    delay(500);
    if(y==1){   //select acionado
      abreGarra();
    }
    //reta
    break;
  case 4:    //identificaçao de cor
    lcd.setCursor(0,1);
    lcd.print ("TP 04"); 
    lcd.print ("          ");
    delay(500);
    if (y==1){
      largada();
      localiza(110, BB_L, BB_R);
      liga_motores();
      liga_leds();
      int scan = analogRead(LDR_G);
      while(scan < 820){
        scan = analogRead(LDR_G);

      }
      delay(10);
      motor1->run(RELEASE);
      motor2->run(RELEASE);
      motor1->setSpeed(0);
      motor2->setSpeed(0);
      delay(100);
      agarra_bloco();
      delay(100);
      desliga_leds();
      

    }
    break;
  case 5:
    lcd.setCursor(0,1);
    lcd.print ("ler LDRDF"); 
    lcd.print ("          ");
    delay(500);
    if (y==1){
      LDRDF();
    }
    break;  

  }
}










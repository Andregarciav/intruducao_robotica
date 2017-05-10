#include <LiquidCrystal.h>  
#include <Adafruit_MotorShield.h>
#include <Wire.h> 
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *motor1 = AFMS.getMotor(3);    //chama motor 1 no rele 3
Adafruit_DCMotor *motor2 = AFMS.getMotor(4);    //chama motor 2 no rele 4   

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
//vaariaveis globais 
int k=250;
int x=1;
//chamada de funcoes
int menu(int x);
void anda30();
void gira90();
void quadrado();
void triangulo();
void reta30();
void retaSemFim();
void identificar();
void decisao();
///////////////////////////////////////////////

void setup()   
{  
  AFMS.begin();
  lcd.begin(16, 2);  
  lcd.setCursor(1,0);  
  lcd.print("Robolfo V,2.0");  
  lcd.setCursor(0,1);  
  lcd.print("Func.: Quadrado");  
}  

  
void loop()  
{  
  int botao;  
  botao = analogRead (0);  //Leitura do valor da porta analógica A0
  
  lcd.setCursor(6,1);
  lcd.print(" ");  
  if (botao < 100) {  
    lcd.print ("Start rigth     ");
    
    //quadrado
    
    anda30();
    delay(50000);
    gira90();
    anda30();
    gira90();
    anda30();
    gira90();
    anda30();
    
  }  
 else if (botao < 200) {
    x=x+1;
    if(x>5){
      x=1;
    }
    
    menu(x);//botao up define qual funcao usar
  }  
  else if (botao < 400){  
    x=x-1;
    if(x<1){
      x=5;
    }
    menu(x);//botao down define qual funcao usar
  }  
  else if (botao < 600){ 
    lcd.print ("botao left");
    /* 
    motor1->setSpeed(0);
    motor1->run(FORWARD);
    motor2->setSpeed(0);
    motor2->run(FORWARD);
    */
  }  
  else if (botao < 800){
    lcd.print ("botao select      ");
    /*
    motor1->setSpeed(200);
    motor1->run(BACKWARD);
    motor2->setSpeed(200);
    motor2->run(BACKWARD);
    */
  } 

  
  
   
}

int menu(int x){
    switch(x){
      case 1:
      lcd.print ("Quadrado"); 
      lcd.print ("          ");
      delay(500);
      //quadrado
      break;
      case 2:
      lcd.print ("Triangulo"); 
      lcd.print ("          ");
      delay(500);
      //triangulo
      break;
      case 3:
      lcd.print ("Reta"); 
      lcd.print ("          ");
      delay(500);
      //reta
      break;
      case 4:
      lcd.print ("Cor"); 
      lcd.print ("          ");
      delay(500);
      //identificaçao de cor
      break;
      case 5:
      lcd.print ("Decisao"); 
      lcd.print ("          ");
      delay(500);
      //tudo
      break;
      
      
    }
}


void anda30()
{
  motor1->setSpeed(250);
  motor1->run(FORWARD);
  delay(1000);
}
void gira90()
{
  motor1->setSpeed(0);
  delay(1000);
  motor2->setSpeed(200);
  motor2->run(FORWARD);
  delay(1000);
  motor2->setSpeed(0);
  delay(1000);  
  motor1->setSpeed(200);
  motor1->run(FORWARD);
  delay(1000);
  motor1->setSpeed(0);
  delay(100);
  motor2->setSpeed(200);
  motor2->run(BACKWARD);
  delay(1000);  
  motor2->setSpeed(0);  
}

void quadrado(){
  
  }
void triangulo(){
  
  }
void reta30(){
  
  }
void retaSemFim(){
  
  }
void identificar(){
  
  }
void decisao(){
  
  }

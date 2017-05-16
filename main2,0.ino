#include <LiquidCrystal.h>  
#include <Adafruit_MotorShield.h>
#include <Wire.h> 
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *motor1 = AFMS.getMotor(1);    //chama motor 1 no rele 3
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);    //chama motor 2 no rele 4   

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
//vaariaveis globais 

const int LDR = 8;
int valorLido = 0;
int k=250;
int x=1;
int ledR = 49;
int ledG = 51;
int ledB = 53;
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
void gira45();
///////////////////////////////////////////////

void setup()   
{ 
  Serial.begin(9600);
  pinMode(ledR,OUTPUT);
  pinMode(ledG,OUTPUT);
  pinMode(ledB,OUTPUT);
  AFMS.begin();
  lcd.begin(16, 2);  
  lcd.setCursor(1,0);  
  lcd.print("Robolfo V,2.0");  
  lcd.setCursor(0,1);  
  lcd.print("Func.: Quadrado");  
}  

  
void loop()  
{  
  int botao = analogRead (0);  //Leitura do valor da porta analógica A0

  //FUNCAO DO CHEIKINHO
/*
valorLido = analogRead(LDR);
Serial.print("Valor lido pelo LDR: ");
Serial.println(valorLido);
delay(1000);
*/
  //------------------
  lcd.setCursor(6,1);
  lcd.print(" ");  
  if (botao < 100) {  
    lcd.print ("Start rigth     ");
    
  }  
 else if (botao < 200) {
    x=x+1;
    if(x>5){
      x=1;
    }
    
    menu(x,0);//botao up define qual funcao usar
  }  
  else if (botao < 400){  
    x=x-1;
    if(x<1){
      x=5;
    }
    menu(x,0);//botao down define qual funcao usar
  }  
  else if (botao < 600){ 
    lcd.print ("botao left");
    parada();
    /* 
    motor1->setSpeed(0);
    motor1->run(FORWARD);
    motor2->setSpeed(0);
    motor2->run(FORWARD);
    */
  }  
  else if (botao < 800){
    lcd.print ("botao select      ");
    menu(x,1);
    
  } 

  
  
   
}

int menu(int x,int y){
  //switch q define as opcoes do menu
    switch(x){
      case 1://caso 1 quadrado
      lcd.print ("Quadrado"); 
      lcd.print ("          ");
      delay(500);
      if(y==1){     //select acionado
      quadrado();
      }
      break;
      case 2: //para selecinar um triangulo
        lcd.print ("Triangulo"); 
        lcd.print ("          ");
        delay(500);
        if(y==1){       //select acionado
          triangulo();
      }
      break;
      case 3:  // para selecionar uma reta
        lcd.print ("Reta"); 
        lcd.print ("          ");
        delay(500);
        if(y==1){   //select acionado
          anda30();
        }
        //reta
      break;
      case 4:
        lcd.print ("Cor"); 
        lcd.print ("          ");
        delay(500);
        if (y==1){
          identificar();
          
          }
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
  motor1->setSpeed(222);
  motor1->run(FORWARD);
  motor2->setSpeed(250);
  motor2->run(FORWARD);
  delay(16000);
}
void gira90()
{
  motor1->setSpeed(0);
  motor2->setSpeed(0);
  delay(100);
  motor1->setSpeed(200);
  motor1->run(FORWARD);
  motor2->setSpeed(200);
  motor2->run(BACKWARD);
  delay(16000);
  motor1->setSpeed(0);
  motor2->setSpeed(0);
  delay(1000);   
}
void gira45(){
  motor1->setSpeed(0);
  motor2->setSpeed(0);
  delay(100);
  motor1->setSpeed(200);
  motor1->run(FORWARD);
  motor2->setSpeed(200);
  motor2->run(BACKWARD);
  delay(8000);
  motor1->setSpeed(0);
  motor2->setSpeed(0);
  delay(1000);   
}
void anda42(){
  motor1->setSpeed(232);
  motor1->run(FORWARD);
  motor2->setSpeed(250);
  motor2->run(FORWARD);
  delay(19000);
  
 }
  

void parada(){
  motor1->setSpeed(0);
  motor2->setSpeed(0);
}

void quadrado(){
  anda30();//anda ate v1
  gira90();//v1
  anda30();//anda ate v2
  gira90();//v2
  anda30();//anda ate v3
  gira90();//v3
  anda30();//anda ate v4
  }
void triangulo(){
  anda30();//anda ate v1
  gira90();//v1
  anda30();//anda ate v2
  gira45();//v2
  anda42();
  //anda42v43();//anda ate v3
  }
void identificar(){
  digitalWrite(ledR,HIGH);
  delay(1000);
  digitalWrite(ledG,HIGH);
  delay(1000);
  digitalWrite(ledB,HIGH);
  delay(1000);
  }
void decisao(){
  
  }

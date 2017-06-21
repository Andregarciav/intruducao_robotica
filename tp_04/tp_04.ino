//inclusão de biblioteca LCD
#include <LiquidCrystal.h>
//Bilbioteca Shieldd
#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

//DEFINICAO DOS PINOS
//BREAK BEAMS
#define BB_R 45
#define BB_L 41
#define BB_G 23

//LDRs
#define LDR_start 14
#define LDR_DF 12
#define LDR_G 10

//LEDS

#define LED_B 27
#define LED_R 31
#define LED_G 29

//DEFINIÇÃO DOS MOTORES
#define mot1 122 //Potência motor 1    130
#define mot2 220 // Potência motor 2   180
#define mot3 40 // Potência motor 3    27

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);    //chama motor 1 no rele 3
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);    //chama motor 2 no rele 4
Adafruit_DCMotor *motor3 = AFMS.getMotor(3);    //chama motor 3



LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

//BOTOES MENU
int x=1;
int botao;

void setup()
{
  Serial.begin(9600);
  pinMode(BB_L, INPUT);
  pinMode(BB_R, INPUT);
  pinMode(BB_G, INPUT);
  pinMode(LDR_start, INPUT);
  pinMode(LDR_DF, INPUT);
  pinMode(LDR_G, INPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  AFMS.begin();
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.println("Mega Robolfo    ");
  menu(x,0);
}

void loop()
{

  botao = analogRead(0);
  if (botao < 100) {  //BOTAO RIGHT
    lcd.print ("R");
  }  
  else if (botao < 200) {//BOTAO UP
    x=x-1;
    if(x<1){
      x=5;
    }
    menu(x,0);
  }  
  else if (botao < 400){  //BOTAO DOWN
    x=x+1;
    if(x>5){
      x=1;
    }
    menu(x,0);
  }  
  else if (botao < 600){ //BOTAO LEFT
    lcd.print ("L");
    parada();
  }  
  else if (botao < 800){ //BOTAO SELECT
    lcd.print ("S");
    menu(x,1);
    delay(10);
    menu(x,0);
  } 
}







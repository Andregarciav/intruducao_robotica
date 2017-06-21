//inclusão de biblioteca LCD
#include <LiquidCrystal.h>
//Bilbioteca Shieldd
#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

//LDRs DE LINE FOLLOWING
#define LDR_L 12
#define LDR_R 14

//DEFINIÇÃO DOS MOTORES
#define mot1 130 //Potência motor 1
#define mot2 180 // Potência motor 1
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);    //chama motor 1 no rele 3
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);    //chama motor 2 no rele 4 MOTOR DOIS GIRO INVERTIDO


LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

/////////////////////////////////////////////////////////////////////////

int valor_LDR_L = 0;
int valor_LDR_R = 0;


void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  AFMS.begin();
  pinMode(LDR_L, INPUT);
  pinMode(LDR_R, INPUT);
}

void loop ()
{
  valor_LDR_R = analogRead(LDR_R);
  valor_LDR_L = analogRead(LDR_L);

  Serial.print("Valor Esquerdo");
  Serial.print("\t");
  Serial.print("Valor Direito");
  Serial.println("");

  Serial.print("\t");
  Serial.print(valor_LDR_L);
  Serial.print("\t");
  Serial.print("\t");
  Serial.print(valor_LDR_R);
  Serial.println("");

  delay(1000);                       

  calibra_line_follow();
  delay(3000);
  
  valor_LDR_R = analogRead(LDR_R);
  valor_LDR_L = analogRead(LDR_L);
  delay(100);
  line_follow();
}



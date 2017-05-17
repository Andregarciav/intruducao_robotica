//inclusão de biblioteca LCD
#include <LiquidCrystal.h>
//Bilbioteca Shieldd
#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
//Declaração dos tempos do Delay
#define ida 22000
#define giro 11000
#define vertice giro+(giro)/2
#define volta 22000 //volta do trinagulo
#define num_medias 20 //numero de medicoes para pegar a media
#define tolerancia_ldr 10 //tolerancia do LDR

//DEFINIÇÃO DOS MOTORES
#define mot1 250 //Potência motor 1
#define mot2 222 // Potência motor 1
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *motor1 = AFMS.getMotor(1);    //chama motor 1 no rele 3
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);    //chama motor 2 no rele 4 MOTOR DOIS GIRO INVERTIDO

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
//timer

unsigned long tempo_atual;
unsigned long timer;
  
//vaariaveis globais

const int LDR = 8;
int valorLido = 0;
int k=250;
int x=1;
int ledR = 53;
int ledG = 51;
int ledB = 49;
int calib_ambiente; //Calibragem do ambiente
int calib_sombra; //Calibragem com objeto obstruindo
int calib_cor[3]; //Calibragem de cada cor frente a um objeto branco 0-Vermelho, 1-Verde, 2-Azul
int calib_black[3]; //Calibragem de cada cor frente a um objeto preto 0-Vermelho, 1-Verde, 2-Azul
int leitura_LDR[4]; //Leitura de sensor 0-Vermelho, 1-Verde, 2-Azul, 3- Branco
int cor_retorno;

//chamada de funcoes
//menu
int menu(int x);
//funcoes movimento
void anda10();
void anda30();
void gira45();
void gira90Direita();
void gira90Esquerda();
//estruturas
void quadrado();
void triangulo();
void reta30();
void identificar();
void decisao();
void parada();

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
  lcd.setCursor(6,1);
  lcd.print(" ");
  if (botao < 100) {
    lcd.print ("Start rigth     ");

  }
 else if (botao < 200) {
    x=x+1;
    if(x>6){
      x=1;
    }

    menu(x,0);//botao up define qual funcao usar
  }
  else if (botao < 400){
    x=x-1;
    if(x<1){
      x=6;
    }
    menu(x,0);//botao down define qual funcao usar
  }
  else if (botao < 600){
    lcd.print ("botao left");
    parada();
    
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
          motor1->setSpeed(mot1);
          motor1->run(BACKWARD);
          motor2->setSpeed(mot2);
          motor2->run(FORWARD);
          delay(23500); //Tempo do motor funcionando na volta
          motor1->setSpeed(0);
          motor2->setSpeed(0);

        }
        //reta
      break;
      case 4:
        lcd.print ("Cor");
        lcd.print ("          ");
        delay(500);
        if (y==1){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Realizando");
          lcd.setCursor(0,1);
          lcd.print("Leitura...");
          leLDR();
          retornaCor();

          }
      //identificaçao de cor
      break;
      case 5:
        lcd.print ("Decisao");
        lcd.print ("          ");
        delay(500);
        if(y==1){
        decisao();
        }
        break;
      case 6:
        lcd.print("Calibragem");
        delay(500);
        if(y==1){
        calibra();
        }
        break;
    }
}

void retorno(){
  motor1->setSpeed(mot1);
  motor1->run(BACKWARD);
  motor2->setSpeed(mot2);
  motor2->run(FORWARD);
  delay(1000); //Tempo do motor funcionando
  motor1->setSpeed(0);
  motor2->setSpeed(0);
  }
//Função do motor andar 30 cm
void anda30()
{
  motor1->setSpeed(mot1);
  motor1->run(FORWARD);
  motor2->setSpeed(mot2);
  motor2->run(BACKWARD);
  delay(ida); //Tempo do motor funcionando
  motor1->setSpeed(0);
  motor2->setSpeed(0);
}
void gira90Direita()//QUADRADO USA ESSE
{
  motor1->setSpeed(0);
  motor2->setSpeed(0);
  delay(100);
  motor1->setSpeed(mot1);
  motor1->run(BACKWARD);
  motor2->setSpeed(mot2);
  motor2->run(BACKWARD);
  delay(giro);
  motor1->setSpeed(0);
  motor2->setSpeed(0);
  delay(1000);
}
void gira90Esquerda(){
  motor1->setSpeed(0);
  motor2->setSpeed(0);
  delay(100);
  motor1->setSpeed(mot1);
  motor1->run(FORWARD);
  motor2->setSpeed(mot2);
  motor2->run(FORWARD);
  delay(giro);
  motor1->setSpeed(0);
  motor2->setSpeed(0);
  delay(1000);
}
void gira45(){
  motor1->setSpeed(0);
  motor2->setSpeed(0);
  delay(100);
  motor1->setSpeed(mot1);
  motor1->run(BACKWARD);
  motor2->setSpeed(mot2);
  motor2->run(BACKWARD);
  delay(vertice);
  motor1->setSpeed(0);
  motor2->setSpeed(0);
  delay(1000);
}
void anda42(){
  motor1->setSpeed(mot1);
  motor1->run(FORWARD);
  motor2->setSpeed(mot2);
  motor2->run(BACKWARD);
  delay(volta);
  parada();

 }


void parada(){
  motor1->setSpeed(0);
  motor2->setSpeed(0);
}

void quadrado(){
  anda30();//anda ate v1
  gira90Direita();//v1
  anda30();//anda ate v2
  gira90Direita();//v2
  anda30();//anda ate v3
  gira90Direita();//v3
  anda30();//anda ate v4
  }
void triangulo(){
  anda30();//anda ate v1
  gira90Direita();//v1
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
  tempo_atual = millis();
  timer = tempo_atual;
  
  rotina_1();
  
  while(analogRead(LDR)> calib_sombra && (tempo_atual - timer) <10000)
  {
    tempo_atual = millis();
    }  
  if((tempo_atual - timer) <10000){
    rotina_2();
      if(cor_retorno == 0){
       retorno();
       gira90Esquerda();
       decisao();
      }
      else if(cor_retorno == 1){
       retorno();
       gira90Direita();
       decisao();
      }
      else if(cor_retorno == 2){
       retorno();
       gira90Direita();
       gira90Direita();
       gira90Direita();
       gira90Direita();
       decisao();
      }
      else if(cor_retorno == 3){
       retorno();
       gira90Esquerda();
       gira90Esquerda();
       decisao();
      }
      else if(cor_retorno == 4){
       delay(100);
       motor1->setSpeed(0);
       motor2->setSpeed(0);
      }
  }
  else{
  delay(100);
  motor1->setSpeed(0);
  motor2->setSpeed(0);
  delay(100);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Sem obstaculo");
  delay(4000);
    }


  delay(100);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Robolfo V,2.0");
  lcd.setCursor(0,1);
  lcd.print("Func.: Decisao");
    
}


  void rotina_1(){
    motor1->run(FORWARD);
    motor1->setSpeed(mot1);
    motor2->run(BACKWARD);
    motor2->setSpeed(mot2);
  }

  void rotina_2(){
      delay(100);
      motor1->setSpeed(0);
      motor2->setSpeed(0);
      delay(100);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Realizando");
      lcd.setCursor(0,1);
      lcd.print("Leitura...");
      leLDR();
      cor_retorno = retornaCor();
      delay(5000);
  }
//////////////////////////////////////////
//FUNCOES DE Calibragem//
//////////////////////////////////////////
void calibra(){
  //BLOCO PARA CALIBRAR AMBIENTE E SOMBRA
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Deixe o LDR");
  lcd.setCursor(0,1);
  lcd.print("Exposto a luz");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("5,");
  delay(1000);
  lcd.print("4,");
  delay(1000);
  lcd.print("3,");
  delay(1000);
  lcd.print("2,");
  delay(1000);
  lcd.print("1");
  delay(1000);
  calibraAmbiente();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Posicione o obj.");
  lcd.setCursor(0,1);
  lcd.print("Tampando o LDR");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("5,");
  delay(1000);
  lcd.print("4,");
  delay(1000);
  lcd.print("3,");
  delay(1000);
  lcd.print("2,");
  delay(1000);
  lcd.print("1");
  delay(1000);
  calibraSombra();

  lcd.clear();
  lcd.print("Remova o obj");

  while(analogRead(LDR)<calib_ambiente);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Robolfo V,2.0");
  lcd.setCursor(0,1);
  lcd.print("Func.: Calibragem");
}

int mediaLeituras (int vezes){
  int sum = 0;
  int leitura;

  for(int i = 0; i < vezes; i++){
    leitura = analogRead(LDR);
    sum += leitura;
    delay(100);
  }
  return (sum / vezes);
}

void calibraAmbiente(){
  //Calibra o LDR segundo o ambiente
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Calibrando");
  lcd.setCursor(0,1);
  lcd.print("Ambiente");
  delay(1000);
  calib_ambiente = mediaLeituras(num_medias);
  calib_ambiente -= calib_ambiente/tolerancia_ldr;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Calib ambiente:");
  lcd.setCursor(0,1);
  lcd.print(calib_ambiente);
  delay(5000);
}

void calibraSombra(){
  //Calibra o LDR quando um objeto está frente ao LDR
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Calibrando");
  lcd.setCursor(0,1);
  lcd.print("Sombra");
  delay(1000);
  calib_sombra = mediaLeituras(num_medias);
  calib_sombra += calib_sombra/tolerancia_ldr;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Calib sombra:");
  lcd.setCursor(0,1);
  lcd.print(calib_sombra);
  delay(5000);
}

void calibraCores(){

}

void leLDR(){
  //Leitura cor vermelha
  digitalWrite(ledR, HIGH);
  delay(100);

  leitura_LDR[0] = mediaLeituras(num_medias);

  digitalWrite(ledR, LOW);
  delay(100);
  //Leitura cor verde
  digitalWrite(ledG, HIGH);
  delay(100);

  leitura_LDR[1] = mediaLeituras(num_medias);

  digitalWrite(ledG, LOW);
  delay(100);
  //Leitura cor azul
  digitalWrite(ledB, HIGH);
  delay(100);

  leitura_LDR[2] = mediaLeituras(num_medias);

  digitalWrite(ledB, LOW);

  delay(100);
  digitalWrite(ledR, HIGH);
  digitalWrite(ledG, HIGH);
  digitalWrite(ledB, HIGH);
  delay(100);
  leitura_LDR[3] = mediaLeituras(num_medias);
  delay(100);
  digitalWrite(ledR, LOW);
  digitalWrite(ledG, LOW);
  digitalWrite(ledB, LOW);

}

int retornaCor(){

  if(leitura_LDR[0]*0.7 >leitura_LDR[2] && leitura_LDR[1]*0.7>leitura_LDR[2]){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Cor:");
    lcd.setCursor(0,1);
    lcd.print("Amarelo");
    return 0;
  }
  else if(leitura_LDR[3]*0.85 < leitura_LDR[2] && leitura_LDR[3]*1.10 > leitura_LDR[2]){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Cor:");
    lcd.setCursor(0,1);
    lcd.print("Azul");
    return 1;
  }
  else if(leitura_LDR[3]*0.90 < leitura_LDR[1] && leitura_LDR[3]*1.10 > leitura_LDR[1]){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Cor:");
    lcd.setCursor(0,1);
    lcd.print("Verde");
    return 2;
  }
  else if(leitura_LDR[3]*0.90 < leitura_LDR[0] && leitura_LDR[3]*1.10 > leitura_LDR[0]){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Cor:");
    lcd.setCursor(0,1);
    lcd.print("Vermelho");
    return 3;
  }
  else {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Cor:");
    lcd.setCursor(0,1);
    lcd.print("Preto");
    return 4;
  }
}


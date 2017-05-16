int Armazena[20];
int Media;
int Armazena_Red[20];
int Armazena_Green[20];
int Armazena_Blue[20];
int cont;
int ledR=49;
int ledG=51;
int ledB=53;
int Valorlido;
const int LDR=8;
void Calibra(){
  for (cont = 0; cont < 20; cont++)
  {
    Armazena[cont]=analogRead(LDR);
  }
  
  }
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledR, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(ledG, OUTPUT);
}

void loop() {
    Valorlido = analogRead(LDR);
    digitalWrite(ledR, HIGH);   // turn the LED on (HIGH is the voltage level)
    Serial.print("Valor lido pelo LDR: ");
    Serial.println(Valorlido);
    delay(1000);
    Calibra();
    media();
    Serial.print("media ");
    Serial.println(Media);
/*
    if (Valorlido < (Media-(Media/3))){
      //motor1->setSpeed(0);
    }  
    
*/
}

int media(){
  int A;
  for(A=0;A<20;A=A+1){
    Media=Media+Armazena[A];
  }
  Media=Media/20;
}

void abreGarra(){
  motor3->run(BACKWARD);
  motor3->setSpeed(30);
  delay(100);
  motor3->run(RELEASE);
}

void fechaGarra(){
  motor3->run(FORWARD);
  motor3->setSpeed(40);
  delay(100);
  motor3->run(RELEASE);
}

void agarra_bloco(){
  motor3->run(FORWARD);
  motor3->setSpeed(40);
  //giros(18);
  delay(200);
  motor3->run(RELEASE);
}

void solta_bloco(){
  motor3->run(BACKWARD);
  motor3->setSpeed(40);
  delay(300);
  motor3->run(RELEASE);
}

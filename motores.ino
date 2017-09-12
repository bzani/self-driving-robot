/*
Virar o robo 90º para direita para desviar de obstaculo pela direita
*/
void virarDireita() {
  Serial.println("Virando para direita");
  digitalWrite(M1_IN1, LOW);
  digitalWrite(M2_IN3, HIGH);                                      //Esteira para frente
  analogWrite(M1_IN2, 155);                                       //Esteira para tras
  analogWrite(M2_IN4, 155);
  limiteLinha();
  delay(2000);//Espera por um segundo
  //pararRobo();
}
/*
Virar o robo 90º para esquerda para desviar de obstaculo para esquerda
*/
void virarEsquerda() {
  Serial.println("Virando para esquerda");
  digitalWrite(M1_IN1, HIGH);
  digitalWrite(M2_IN3, LOW);
  analogWrite(M1_IN2, 155);                                       //Esteira para tras
  analogWrite(M2_IN4, 155);
  limiteLinha();
  delay(2200);//Espera um segundo
  //pararRobo();
}
/*
  Parar o robo completamente
*/
void pararRobo() {
  Serial.println("Parado!");
  digitalWrite(M1_IN1, LOW);
  analogWrite(M1_IN2, 0);
  digitalWrite(M2_IN3, LOW);
  analogWrite(M2_IN4, 0);
  delay(2000);
  Serial.println("Continuando...");
}
/*
  Aciona Motores de acordo com a velocidade passada para a func.
*/
void acionaMotores(int M1velocidade, int M2velocidade) {
  /*
    Caso velocidade definida pelo PID ou outro método seja maior que 255
    a velocidade é definida como 255 para não acontecer sobrecarga de tensão
  */
  int VELOCIDADE = 0;
  if (desviandoObjeto) {
    VELOCIDADE = VELOCIDADE_MAXIMA_DESVIANDO_OBJ;
  } else {
    VELOCIDADE = VELOCIDADE_MAXIMA;
  }
  if (M1velocidade > VELOCIDADE)                                              //Caso a velocidade do motor 1 seja superior da permitida, mudar para velocidade base
    M1velocidade = VELOCIDADE;
  if (M2velocidade > VELOCIDADE)                                              //Caso a velocidade do motor 1 seja superior da permitida, mudar para velocidade base
    M2velocidade = VELOCIDADE;
  if (M1velocidade > 0) {                                                            //Caso a velocidade do motor for maior que 0 movemos esteira para frente
    digitalWrite(M1_IN1, LOW);
  } else {
    if (!desviandoObjeto) {
      M1velocidade = 0;
    } else {
      digitalWrite(M1_IN1, HIGH);
    }
  }
  if (M2velocidade > 0) {                                                            //Caso a velocidade do motor for maior que 0 movemos esteira para frente
    digitalWrite(M2_IN3, LOW);
  } else {       //Caso a velocidade do motor for maior que 0 movemos esteira para trás
    if (!desviandoObjeto) {
      M2velocidade = 0;
    } else {
      digitalWrite(M2_IN3, HIGH);
    }
  }
  analogWrite(M1_IN2, M1velocidade);                                                 //Aciona motores com velocidade passada
  analogWrite(M2_IN4, M2velocidade);                                                 //Aciona motores com velocidade passada
}

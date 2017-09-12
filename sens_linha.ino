
/*
   Rotina basica para calibrar os sensores de leitura de linha utilizando a biblioteca da POLOLU chamada
   QTRsensors.h contendo diversos recursos para armazenar os valores da linha.
*/
void calibraSensoresLinha()
{
  /*
    Rotina para calibrar o robo no que o mesmo e ligado. Armazenando os valores maximos e minimos.
  */
  Serial.println("Calibrando...");
  digitalWrite(M1_IN1, HIGH);
  analogWrite(M1_IN2, 120);                                       //Esteira para tras
  digitalWrite(M2_IN3, LOW);                                      //Esteira para frente
  analogWrite(M2_IN4, 120);
  for (int i = 0; i < 75; i++) {
    qtra.calibrate();
    delay(20);
  }
  digitalWrite(M1_IN1, LOW);                                       //Esteira para frente
  analogWrite(M1_IN2, 120);
  digitalWrite(M2_IN3, HIGH);                                      //Esteira para tras
  analogWrite(M2_IN4, 120);
  for (int i = 0; i < 150; i++) {
    qtra.calibrate();
    delay(20);
  }
  digitalWrite(M1_IN1, HIGH);
  analogWrite(M1_IN2, 120);                                       //Esteira para tras
  digitalWrite(M2_IN3, LOW);                                      //Esteira para frente
  analogWrite(M2_IN4, 120);
  for (int i = 0; i < 80; i++) {
    qtra.calibrate();
    delay(20);
  }
  for (int i = 0; i < 3; i++) {
    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(qtra.calibratedMinimumOn[i]);
  }
  calibrado = true;
}


/*
  Checagem para ver se robo está ou não na linha
*/
bool limiteLinha() {
  qtra.readLine(valorSensores);                                //faz leitura das posicoes dos sensores
  /*
     Faz comparacao do valor dos sensores com o valor minimo obtido durante a calibracao
  */
  if (analogRead(1) < branco && analogRead(2) < branco && analogRead(3) < branco) {
    Serial.println("Perdeu linha");
    perdeuLinha = true;
    return true;
  } else {
    Serial.println("Encontrou linha");
    desviandoObjeto = false;
    perdeuLinha = false;
    virarRobo = false;
    desviouDireita = false;
    desviouEsquerda = false;
    return false;
  }
}

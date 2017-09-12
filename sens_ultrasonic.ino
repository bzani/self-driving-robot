/*
  Checar qual lado (Esquerdo ou Direito) possui um obstaculo mais longe e começar o desvio por ele;
*/
bool checkUltraLado() {
  //virar para direita, onde o sensor da direita estï¿½ï¿½ com um sensor mais longe que o da direita
  Serial.println("em checkUltraLado");
  if (desviandoObjeto) {
    if (distanciaSensor(sonarDir) > distanciaSensor(sonarEsq)) {
      //Virar para direita
      Serial.println("Virar Direita ");
      virarDireita();
      desviarObjDireita();
      return true;
    } else {
      //Virar para esquerda
      Serial.println("Virar esquerda ");
      virarEsquerda();
      desviarObjEsquerda();
      return false;
    }
  }
}
/*
  Desvia Objeto pela esquerda
*/
void desviarObjEsquerda() {
  int distanciaLateral;
  //Andar para frente para fazer a primeira curva
  acionaMotores(VELOCIDADE_MAXIMA_DESVIANDO_OBJ, VELOCIDADE_MAXIMA_DESVIANDO_OBJ);
  //Anda por 1 segundo para compensar a perca de sinal da traseira
  delay(1000);
  acionaMotores(VELOCIDADE_MAXIMA_DESVIANDO_OBJ, VELOCIDADE_MAXIMA_DESVIANDO_OBJ);
  do{
    distanciaLateral = distanciaSensor(sonarDir);
  }while(distanciaLateral <= SETPOINTULTRASONIC || distanciaLateral == 0);
  //Para realizar a primeira cuva
  acionaMotores(VELOCIDADE_MAXIMA_DESVIANDO_OBJ, VELOCIDADE_MAXIMA_DESVIANDO_OBJ);
  delay(1000);
  virarDireita();
  acionaMotores(VELOCIDADE_MAXIMA_DESVIANDO_OBJ, VELOCIDADE_MAXIMA_DESVIANDO_OBJ);
  delay(2000);  
  acionaMotores(VELOCIDADE_MAXIMA_DESVIANDO_OBJ, VELOCIDADE_MAXIMA_DESVIANDO_OBJ);
   do{
    distanciaLateral = distanciaSensor(sonarDir);
  }while(distanciaLateral <= SETPOINTULTRASONIC || distanciaLateral == 0); 

  //Para realizar a segunda curva
  acionaMotores(VELOCIDADE_MAXIMA_DESVIANDO_OBJ, VELOCIDADE_MAXIMA_DESVIANDO_OBJ);
  delay(1000);
  virarDireita();
  acionaMotores(VELOCIDADE_MAXIMA_DESVIANDO_OBJ, VELOCIDADE_MAXIMA_DESVIANDO_OBJ);
  delay(1500);  
  acionaMotores(VELOCIDADE_MAXIMA_DESVIANDO_OBJ, VELOCIDADE_MAXIMA_DESVIANDO_OBJ);
   do{
    distanciaLateral = distanciaSensor(sonarDir);
  }while(limiteLinha());   
  Serial.println("Buscando Linha...");
  desviouEsquerda = true;
}
/*
  Desvia Objeto pela direita
*/
void desviarObjDireita() {
  int distanciaLateral;
  //Andar para frente para fazer a primeira curva
  acionaMotores(VELOCIDADE_MAXIMA_DESVIANDO_OBJ, VELOCIDADE_MAXIMA_DESVIANDO_OBJ);
  //Anda por 1 segundo para compensar a perca de sinal da traseira
  delay(1000);
  acionaMotores(VELOCIDADE_MAXIMA_DESVIANDO_OBJ, VELOCIDADE_MAXIMA_DESVIANDO_OBJ);
  do{
    distanciaLateral = distanciaSensor(sonarEsq);
  }while(distanciaLateral <= SETPOINTULTRASONIC || distanciaLateral == 0);
  //Para realizar a primeira cuva
  acionaMotores(VELOCIDADE_MAXIMA_DESVIANDO_OBJ, VELOCIDADE_MAXIMA_DESVIANDO_OBJ);
  delay(1000);
  virarEsquerda();
  acionaMotores(VELOCIDADE_MAXIMA_DESVIANDO_OBJ, VELOCIDADE_MAXIMA_DESVIANDO_OBJ);
  delay(2000);  
  acionaMotores(VELOCIDADE_MAXIMA_DESVIANDO_OBJ, VELOCIDADE_MAXIMA_DESVIANDO_OBJ);
   do{
    distanciaLateral = distanciaSensor(sonarEsq);
  }while(distanciaLateral <= SETPOINTULTRASONIC || distanciaLateral == 0); 

  //Para realizar a segunda curva
  acionaMotores(VELOCIDADE_MAXIMA_DESVIANDO_OBJ, VELOCIDADE_MAXIMA_DESVIANDO_OBJ);
  delay(1000);
  virarEsquerda();
  acionaMotores(VELOCIDADE_MAXIMA_DESVIANDO_OBJ, VELOCIDADE_MAXIMA_DESVIANDO_OBJ);
  delay(2000);  
  acionaMotores(VELOCIDADE_MAXIMA_DESVIANDO_OBJ, VELOCIDADE_MAXIMA_DESVIANDO_OBJ);
   do{
    distanciaLateral = distanciaSensor(sonarEsq);
  }while(limiteLinha());   
  desviouDireita = true;
}
int distanciaSensor(NewPing Sensor) {
  return Sensor.ping_median(3) / US_ROUNDTRIP_CM;                                           //Retorna distancia do sensor ultrasonic medido pela media de 3 medições
}

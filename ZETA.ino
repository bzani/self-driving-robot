#include <NewPing.h>
#include <Arduino.h>
#include "QTRSensors.h"
#include "definicoesGerais.h"                                    //Configuracoes gerais

//Prototipos
void calibraSensoresLinha(void);

/*
    Inicializa sensores de linha
    esquerda -> [1, 2, 3] <- direita
*/
QTRSensorsAnalog qtra((unsigned char[]) {
  1, 2, 3
}, NUM_SENSORES_LINHA);

/*
  Instancia sensores ultrasonicos utilizando a biblioteca NewPing
*/
NewPing sonarCenter(ultraTrigCenter, ultraEchoCenter, 2000);
NewPing sonarDir(ultraTrigDir, ultraEchoDir, 2000);
NewPing sonarEsq(ultraTrigEsq, ultraEchoEsq, 2000);

//Cria vetor para gravar valores dos sensores separadamente
unsigned int valorSensores[NUM_SENSORES_LINHA];

int erro = 0;
int ultimoerro = 0;                                                 //Inicia variavel global para armazenar ultimo erro
/*
    Utilizado metodo de tentativa e erro para obter valores de Kp e Kd
*/
bool calibrado = false;                                            // Define se robo esta ou nao calibrado
bool perdeuLinha = false;                                          // Inicia variavel global para definir se robo perdeu
bool desviandoObjeto = false;                                      // Inicia variavel que verifica se robo esta ou nao desviando um objeto
bool buscandoLinha = false;                                        // Caso o robo perca a linha, inicia-se a busca pela mesma
bool virarRobo = false;
bool desviouDireita = false;
bool desviouEsquerda = false;

void setup()
{
  //Inicializa comunicacao serial
  Serial.begin(9600);

  /*
      Inicializa motores
      M1 = Esquerda
      M2 = Direita
  */
  pinMode(M1_IN1, OUTPUT);
  pinMode(M1_IN2, OUTPUT);
  pinMode(M2_IN3, OUTPUT);
  pinMode(M2_IN4, OUTPUT);
  /*
    Inicia sensores ultrasonicos
  */
  pinMode(ultraEchoCenter, INPUT);
  pinMode(ultraTrigCenter, OUTPUT);
  pinMode(ultraEchoEsq, INPUT);
  pinMode(ultraTrigEsq, OUTPUT);
  pinMode(ultraEchoDir, INPUT);
  pinMode(ultraTrigDir, OUTPUT);
  digitalWrite(ultraTrigDir, LOW);
  delayMicroseconds(10);

  //Calibrar sensores
  calibraSensoresLinha();
}

void loop()
{
  float Kp = 4.7;                                                                        //Define constante proporcional, com valor testado e adequado manualmente
  float Kd = 0.2;
  unsigned int posicao = qtra.readLine(valorSensores);                                //faz leitura dos sensores de linha a todo momento.
  /*
    Caso o robo encontre um objeto proximo a ele, iniciar imediatamente o desvio.
  */
  Serial.print("Sensor centro: ");
  Serial.println(distanciaSensor(sonarCenter));
  if (((distanciaSensor(sonarCenter) <= SETPOINTULTRASONIC) && (distanciaSensor(sonarCenter) >= 5)) && calibrado && !desviandoObjeto) { //Verifica se robo esta prox. de um objeto atraves de seu sensor central
    desviandoObjeto = true;                                                                                                            //Caso detecte um objeto em sua frente sera considerado que o robo perdeu a linha
    perdeuLinha = true;                                                                                                                // e esta desviando de um objeto para ficar mais facil de buscar a linha novamente.
    pararRobo();
    checkUltraLado();                                                                                                                  //Faz verificacao do lado em que o robo podera desviar do objeto.
  }
  /*
    Caso o robo esteja na linha, vamos executar o cod abaixo e seguir a linha encontrada
  */
  if (!desviandoObjeto && calibrado && !perdeuLinha) {                               //Caso o robo esteja em linha (perdeuLinha = false) e esteja calirado,
    //vamos seguir a linha
    //Kp = 4.0;                                                                        //Define constante proporcional, com valor testado e adequado manualmente
    //Kd = 0.4;                                                                        //Define constante derivativa, com valor testado e adequado manualmente
    erro = posicao - 1000;                                                       //Define erro, quando erro for = 0 quer dizer que o robo esta em linha.
    int velocidadeMotor = Kp * erro + Kd * (erro - ultimoerro);                      //Faz Calculo PID para a velocidade do motor
    ultimoerro = erro;                                                               //Armazena ultimoerro
    int M1velocidade = VELOCIDADE_MAXIMA - velocidadeMotor;                          //Define velocidade do motor com base na saída (Output) do PID
    int M2velocidade = VELOCIDADE_MAXIMA + velocidadeMotor;                          //Define velocidade do motor com base na saída (Output) do PID
    acionaMotores(M1velocidade, M2velocidade);                                       //Aciona motores com velocidade passada para os mesmos.
    limiteLinha();
  }
  limiteLinha();
}

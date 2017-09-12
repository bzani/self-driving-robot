#ifndef DEFINICOESGERAIS_H

#define NUM_SENSORES_LINHA 3 //Numero de sensores de linha

//Porta dos motores
#define M1_IN1 12
#define M1_IN2 11    //Usado para alterar a direcao do motor
#define M2_IN3 10    //IDEM
#define M2_IN4 9

#define branco 400

//Portas Sensores Ultrasonicos
#define ultraEchoCenter 16
#define ultraEchoEsq 17
#define ultraEchoDir 15
#define ultraTrigCenter 19
#define ultraTrigEsq 18
#define ultraTrigDir 14

//Define limites de velocidade para o motor M1 e M2
#define VELOCIDADE_MAXIMA 255
#define VELOCIDADE_MAXIMA_DESVIANDO_OBJ 200
#define VELOCIDADE_MAXIMA_SEM_LINHA 200

//Setpoint ou distancia desejada para robo ficar distante d eum objeto
#define SETPOINTULTRASONIC 20

#endif


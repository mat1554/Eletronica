#include <stdio.h>
#include <wiringPi.h>
#include <math.h>

//Define as portas da GPIO

#define CLOCK			6
#define NENABLE			5
#define BSERIAL			4

int num[8];

//Funcao para conversao em valor binario
void conversao (int valor){
  int i;
  for (i=0; i<8; i++){
    num[i] = valor%2;
    valor = valor/2;
  }
}

//Funcao para escrever no registrador de deslocamento um valor binario
//eh necessario um clock a mais pois o registrador de saida esta 1 pulso de clock atrasado do registrador de entrada

void escreve_valor (int j){
  int i;
  conversao (j);
  for (i=0; i<8; i++){
    digitalWrite (NENABLE, 1);
    digitalWrite (BSERIAL, num[7-i];
    digitalWrite (CLOCK, 1);
    digitalWrite (CLOCK, 0);
  }
  digitalWrite (CLOCK, 1);
  digitalWrite (CLOCK, 0);
  digitalWrite (NENABLE, 0);
}

int main (void)
{
  int f;
  int forma;
  int i;

  wiringPiSetup () ;
  pinMode (BSERIAL, OUTPUT);
  pinMode (CLOCK, OUTPUT);
  pinMode (NENABLE, OUTPUT);

  //Escolha do usuario para forma de onda e frequencia
  printf ("Escolha a forma de onda desejada (1 para triangular e 0 para senoide)");
  scanf ("%d", &forma);
  printf ("Escolha a frequencia da onda (500Hz ou 50000Hz)");
  scanf ("%d", &f);

  //Gera onda triangular com frequencia de 500hz
  //o valor -7 é usado para corrigir eventuais tempos perdidos com a execucao do programa
  if ((forma==1)&&(f==500)){
    for (;;){
      for (i=0; i<=15; i++){
        escreve_valor (i);
        delayMicroseconds (25000/f - 7);
      }
      for (i=14; i>0; i--){
        escreve_valor (i);
        delayMicroseconds (25000/f - 7);
      }
    }
  }

  //Gera onda triangular com frequencia de 5khz
  //o valor -1 é usado para corrigir eventuais tempos perdidos com a execucao do programa
  if ((forma==1)&&(f==5000)){
    for (;;){
      for (i=0; i<=15; i++){
        escreve_valor (i);
        delayMicroseconds (25000/f - 1);
      }
      for (i=14; i>0; i--){
        escreve_valor (i);
        delayMicroseconds (25000/f - 1);
      }
    }
  }

  //Gera onda senoidal com frequencia escolhida
  //o valor -7 é usado para corrigir eventuais tempos perdidos com a execucao do programa
  if (forma==0){
    for (;;){
      for (i=0; i<20; i++){
      escreva_valor (7*(sin(2*3.14*i/20)+8));
      delayMicroseconds (25000/f - 7);
    }
  }
  return 0 ;
}
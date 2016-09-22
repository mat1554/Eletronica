#include <stdio.h>
#include <wiringPi.h>
#include <math.h>

//Define as portas da GPIO

#define B0			6
#define B1			5
#define B2			4
#define B3            1
#define ENABLE        3

/*Programa principal
Consiste de um loop infinito com duracao de 500ms que alterna entre os 4 estados possiveis dos dados*/

int main (void)
{
  int atualizacao = 0;

  wiringPiSetup () ;
  pinMode (B0, OUTPUT);
  pinMode (B1, OUTPUT);
  pinMode (B2, OUTPUT);
  pinMode (B3, OUTPUT);
  pinMode (ENABLE, OUTPUT);

  for (;;){
    delay (500);
    if (atualizacao>3)
      atualizacao = 0;
    //Fita de led desligada
    if (atualizacao == 0){
      digitalWrite (B0, 0);
      digitalWrite (B1, 0);
      digitalWrite (B2, 0);
      digitalWrite (B3, 0);
      digitalWrite (ENABLE, 0);
      delay (100);
      digitalWrite (ENABLE, 1);
    }
    //Fita de led com pouco brilho
    if (atualizacao == 1){
      digitalWrite (B0, 0);
      digitalWrite (B1, 1);
      digitalWrite (B2, 0);
      digitalWrite (B3, 0);
      digitalWrite (ENABLE, 0);
      delay (100);
      digitalWrite (ENABLE, 1);
    }
    //Fita de led com brilho intermediario
    if (atualizacao == 2){
      digitalWrite (B0, 0);
      digitalWrite (B1, 0);
      digitalWrite (B2, 1);
      digitalWrite (B3, 0);
      digitalWrite (ENABLE, 0);
      delay (100);
      digitalWrite (ENABLE, 1);
    }
    //Fita de led com brilho maximo
    if (atualizacao == 3){
      digitalWrite (B0, 1);
      digitalWrite (B1, 1);
      digitalWrite (B2, 1);
      digitalWrite (B3, 1);
      digitalWrite (ENABLE, 0);
      delay (100);
      digitalWrite (ENABLE, 1);
    }
    atualizacao++;
  }
  return 0 ;
}

#include <stdio.h>
#include <math.h>
#include <wiringPi.h>

#define BSERIAL		6
#define CLOCK		4
#define NENABLE		5
#define CONVERSOR	0

int bin[8];

void conversao (int num) {
  int i;
  for (i=0; i<8; i++){
    bin [i] = num%2;
    num = num/2;
  }
}
/*
float conversao2 (){
  int i;
  int decimal=0;
  for (i=0; i<8; i++){
    decimal = decimal*2 + bin[i];
  }
  return (decimal);
}
*/

float conversao2(){
  return 128*bin[7]+64*bin[6]+32*bin[5]+16*bin[4]+8*bin[3]+4*bin[2]+2*bin[1]+1*bin[0];
}

void escreve_valor (){
  int i;
  digitalWrite (NENABLE, 1);
  for (i=7; i>=0; i--){
    digitalWrite (BSERIAL, bin[i]);
    digitalWrite (CLOCK, 1);
    digitalWrite (CLOCK, 0);
  }
  digitalWrite(CLOCK,1);
  digitalWrite(CLOCK,0);
  digitalWrite (NENABLE, 0);
}

int main ()
{
  int num=0;
  int i,n=0;
  float dados[1024];

  wiringPiSetup () ;
  pinMode (BSERIAL, OUTPUT);
  pinMode (CLOCK, OUTPUT);
  pinMode (NENABLE, OUTPUT);

  while(n < 1024){

    for(i=0;i<=7;i++){
      bin[i]=0;
    }

    for (i=7;i>=0;i--){
      bin[i]=1;
      escreve_valor();
      delayMicroseconds (30);
      if (digitalRead(CONVERSOR) == 1){
        bin[i]=0;
        escreve_valor();
      }      
    }
    dados[n] = conversao2();
    n++;
  }
  
  for(i=0;i<1024;i++){
    printf("%f\n",3*dados[i]/255);
  }

  while (1){
    for (i=0;i<1024;i++){
      conversao (dados[i]);
      escreve_valor ();
      delayMicroseconds (220);
    }
  }
  return 0 ;
}
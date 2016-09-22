#include <stdio.h>
#include <wiringPi.h>
#include <math.h>

//Define as portas da GPIO

#define PWMIN		6
#define TX            5
#define ENABLE        3

/*Programa principal
Consiste de um loop infinito que amostra os dados do PWM, converte em um valor de tensao e em posse desses dados calcula a temperatura ambiente. Dependendo da temperatura, ele desliga ou liga nosso "aquecedor" */

int main (void)
{
  float tensao = 0;
  int dc = 0;
  int i=0;
  int atualizacao=0;
  float R;
  float T;
  float Tamb=23;

  wiringPiSetup () ;
  pinMode (PWMIN, INPUT);
  pinMode (TX, OUTPUT);
  pinMode (ENABLE, OUTPUT);

  
  for (;;){
    atualizacao++;
    for (i=0; i<100; i++){ 
      if (digitalRead (PWMIN)==1)
        dc++;
      delayMicroseconds (40) ;
    }
    tensao =(float) dc/20;

    /*Atualizacao os valores de tensao, resistencia e temperatura a cada 1s, e envia o estado que o aquecedor deve ter (0, deslisgado e 1, ligado)*/

    if (atualizacao >= 250){
      system ("clear");

      printf ("\n Tensao = %.2f V", tensao);

      R = (2880 - 533.33*tensao)/(0.82 + tensao/30);
      //R = (98580 - 16800*tensao)/(tensao + 24.132);
      printf ("\n Rt = %2f oms", R);

      T = 493.6*pow(R, -0.1436) - 138.6;
      //T = 69.22*exp(-0.004292*R) + 69.32*exp(-0.0004602*R);
      printf ("\n Temperatura = %2f", T);

      atualizacao = 0;

      if (T>20+Tamb){
        digitalWrite(TX,0);
        digitalWrite(ENABLE,0);
        delayMicroseconds (10);
        digitalWrite(ENABLE,1);
      }
      else{
        digitalWrite(TX,1);
        digitalWrite(ENABLE,0);
        delayMicroseconds (10);
        digitalWrite(ENABLE,1);
      }
    }
    dc = 0;
  }

  return 0 ;
}

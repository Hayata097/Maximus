#include <Wire.h>
#include "Adafruit_TCS34725.h"

//inicializa o sensor de cor com as especificações. Mudar o número antes de MS para aumentar ou diminuir a velocidade
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_16X);

unsigned int vermelho, verde, azul, lux, c;

void setup(void) {
  Serial.begin(115200);

  //incializa o sensor
  if (tcs.begin()) {
    Serial.println("Sensor encontrado e ativo!");
  } else {
    Serial.println("Sensor não encontrado - ERRO!");
    while (1);
  }

}

void loop(void) {
  //pega as leituras ao sensor  
  tcs.getRawData(&vermelho, &verde, &azul, &c);
  lux = tcs.calculateLux(vermelho, verde, azul);

  if(lux<1000) {
    Serial.print("O sensor está na linha preta! E a leitura do Lux é: ");
    Serial.println(lux);
  }
  else if (verde > (vermelho + 500) and verde > (azul+500)) {
    Serial.print("O sensor está na linha verde! E a leitura é: ");
    Serial.println(verde);
  }
  else {
    Serial.print("O sensor fora das linhas! E a leitura do Lux é: ");
    Serial.println(lux);
  }
  
  delay(50);

}

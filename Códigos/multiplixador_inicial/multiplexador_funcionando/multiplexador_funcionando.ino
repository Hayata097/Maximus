#include <Wire.h>
#include "Adafruit_TCS34725.h"

// Endereço do TCA9548A
#define TCAADDR 0x70

// Inicializa os sensores de cor com as especificações
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_16X);

unsigned int vermelho, verde, azul, lux, c;

void tcaselect(uint8_t i) {
  if (i > 7) return;

  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();
}

void setup(void) {
  Serial.begin(115200);
  Wire.begin();

  // Inicializa o sensor no canal 1 (lado esquerdo)
  tcaselect(1);
  if (tcs.begin()) {
    Serial.println("Sensor esquerdo encontrado e ativo!");
  } else {
    Serial.println("Sensor esquerdo não encontrado - ERRO!");
    while (1);
  }

  // Inicializa o sensor no canal 2 (lado direito)
  tcaselect(2);
  if (tcs.begin()) {
    Serial.println("Sensor direito encontrado e ativo!");
  } else {
    Serial.println("Sensor direito não encontrado - ERRO!");
    while (1);
  }
}

void loop(void) {
  // Ler sensor do lado esquerdo
  tcaselect(1);
  lerSensor("Esquerdo");

  // Ler sensor do lado direito
  tcaselect(2);
  lerSensor("Direito");

  delay(50);
}

void lerSensor(String lado) {
  tcs.getRawData(&vermelho, &verde, &azul, &c);
  lux = tcs.calculateLux(vermelho, verde, azul);

  Serial.print("Sensor "); Serial.print(lado); Serial.print(": ");

  if (lux < 1000) {
    Serial.println("na linha preta!");
    Serial.println(lux);
  } else if (lux < 1300 ) {
    Serial.println("na linha verde! Leitura do Verde: ");
    Serial.println(lux);
  } else if (lux > 1400 ) {
    Serial.println("fora das linhas! ");
    Serial.println(lux);
  }


}

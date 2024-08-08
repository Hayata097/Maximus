#include <Wire.h>
#include "Adafruit_TCS34725.h"

// Endereço do TCA9548A
#define TCAADDR 0x70

 //Motores de passo
#define step_esquerdo 2
#define step_direito 3
#define direcao_esquerdo 5
#define direcao_direito 6
#define enable_pin 8

#define tempo_passo 600
#define passoPorCm 20
#define passoPorGrau 2


// Inicializa os sensores de cor com as especificações
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_16X);

unsigned int vermelhoEsquerdo, verdeEsquerdo, azulEsquerdo, luxEsquerdo;
unsigned int vermelhoDireito, verdeDireito, azulDireito, luxDireito;
int threshold = 500; // Defina o limiar adequado para seu sensor e ambiente

void tcaselect(uint8_t i) {
  if (i > 7) return;

  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();
}

void setup(void) {

  //Motores
  pinMode(step_esquerdo, OUTPUT);
  pinMode(step_direito, OUTPUT);
  pinMode(direcao_esquerdo, OUTPUT);
  pinMode(direcao_direito, OUTPUT);
  pinMode(enable_pin, OUTPUT);

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
//----------------------------------------------------
void frente(float cm){
  for (int x = 0; x<(int(80*cm)); x++) {
      digitalWrite(direcao_esquerdo, LOW);
      digitalWrite(direcao_direito, HIGH);
      digitalWrite(step_esquerdo, HIGH);
      digitalWrite(step_direito, HIGH);
      delayMicroseconds(tempo_passo);
      digitalWrite(step_esquerdo, LOW);
      digitalWrite(step_direito, LOW);
      delayMicroseconds(tempo_passo);
  }
}

//Recebe a quantidade de centimetros que o robô deve se mover pra trás
void tras(float cm){
    
  for (int x = 0; x<(int(80*cm)); x++) {
      digitalWrite(direcao_esquerdo, HIGH);
      digitalWrite(direcao_direito, LOW);
      digitalWrite(step_esquerdo, HIGH);
      digitalWrite(step_direito, HIGH);
      delayMicroseconds(tempo_passo);
      digitalWrite(step_esquerdo, LOW);
      digitalWrite(step_direito, LOW);
      delayMicroseconds(tempo_passo);
  }
}

//Recebe a quantidade de graus que o robô deve girar pra direita
void girar_direita(int grau){
     
  for (int x = 0; x<(int (grau*9.5)); x++) {
      digitalWrite(direcao_esquerdo, LOW);
      digitalWrite(direcao_direito, LOW);
      digitalWrite(step_esquerdo, HIGH);
      digitalWrite(step_direito, HIGH);
      delayMicroseconds(tempo_passo);
      digitalWrite(step_esquerdo, LOW);
      digitalWrite(step_direito, LOW);
      delayMicroseconds(tempo_passo);
  }    
}

//Recebe a quantidade de graus que o robô deve girar pra esquerda
void girar_esquerda(int grau){
  
  for (int x = 0; x<(int (grau*9.5)); x++) {
      digitalWrite(direcao_esquerdo, HIGH);
      digitalWrite(direcao_direito, HIGH);
      digitalWrite(step_esquerdo, HIGH);
      digitalWrite(step_direito, HIGH);
      delayMicroseconds(tempo_passo);
      digitalWrite(step_esquerdo, LOW);
      digitalWrite(step_direito, LOW);
      delayMicroseconds(tempo_passo);
  }
}

void esquerda(){
      
      digitalWrite(direcao_direito, HIGH);
      digitalWrite(step_direito, HIGH);
      delayMicroseconds(tempo_passo);
      digitalWrite(step_direito, LOW);
      delayMicroseconds(tempo_passo);
}

void direita(){
      digitalWrite(direcao_esquerdo, HIGH);
      digitalWrite(step_esquerdo, HIGH);
      delayMicroseconds(tempo_passo);
      digitalWrite(step_esquerdo, LOW);
      delayMicroseconds(tempo_passo);

}



//--------------------------------------------------

void lerSensorEsquerdo() {
  tcaselect(1);
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);
  vermelhoEsquerdo = r;
  verdeEsquerdo = g;
  azulEsquerdo = b;
  luxEsquerdo = c;
}

void lerSensorDireito() {
  tcaselect(2);
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);
  vermelhoDireito = r;
  verdeDireito = g;
  azulDireito = b;
  luxDireito = c;
}

void loop(void) {
  // Ler os sensores
  lerSensorEsquerdo();
  lerSensorDireito();

  // Exibir os valores no monitor serial
  Serial.print("Esquerdo - Lux: "); Serial.print(luxEsquerdo);
  Serial.print(" | Direito - Lux: "); Serial.println(luxDireito);

  // Tomar decisões com base nas leituras dos sensores
  if (luxEsquerdo < 2800 && luxDireito < 2800) {
    Serial.println("Linha detectada em ambos os lados!");
    frente(1);

  } else if (luxEsquerdo < 3300  && luxDireito > 5000) {
    Serial.println("Linha detectada no lado esquerdo.");
    girar_direita(5);
    frente(1);

  } else if (luxEsquerdo > 5000  &&  luxDireito < 3300) {
    Serial.println("Linha detectada no lado direito.");
    girar_esquerda(5);
    frente(1);

  } else if (3400 < luxEsquerdo && luxEsquerdo < 3800  && luxDireito < 3600) {
    Serial.println("Verde no lado direito.");
    girar_esquerda(5);  
    frente(1);

  //} else if (2400 < luxEsquerdo < 2550  &&  2600 < luxDireito < 2800){
   // Serial.println("Verde no lado direito, preto no lado esquerdo");
   // girar_esquerda(5);  
   // frente(1);

  } else if (luxEsquerdo < 2600 && luxDireito > 5000 ) {
    Serial.println("Verde no lado esquerdo.");
    girar_direita(5);
    frente(1);

  //} else if (luxEsquerdo < 3500  && 2500 < luxDireito < 3000){
    //Serial.println("Verde no lado esquerdo, preto no lado direito");
    //girar_direita(10);  
    //frente(1);

  } else if (luxEsquerdo > 4000  && luxDireito > 4000 ) {
    Serial.println("Linha não detectada em nenhum dos lados.");
    frente(1);
  }  

  //} else if (2500 < luxEsquerdo < 3000  && 2500 < luxDireito > 3000 ) {
    //girar_direita(100);

  else {
    // Esse bloco é executado se nenhuma das condições acima for atendida
    Serial.println("Nenhuma condição foi satisfeita. Ação padrão.");
    frente(1);
    // Ou outro comportamento desejado
  }
  delay(50); // Ajuste o delay conforme necessário
}

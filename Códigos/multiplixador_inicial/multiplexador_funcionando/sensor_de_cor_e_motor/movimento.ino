//Recebe a quantidade de centimetros que o robô deve se mover pra frente
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

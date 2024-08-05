    /*
==============================================================================================================
BIBLIOTECAS:
==============================================================================================================*/


/*
==============================================================================================================
MAPEAMENTO DE HARDWARE:
==============================================================================================================*/
  
  //Motores de passo
  #define step_esquerdo 2
  #define step_direito 3
  #define direcao_esquerdo 5
  #define direcao_direito 6
  #define enable_pin 8
  
  //Sensores de linha

  


/*
==============================================================================================================
CONSTANTES:
==============================================================================================================*/

  #define tempo_passo 600
  #define passoPorCm 20
  #define passoPorGrau 2


/*
==============================================================================================================
VARIÁVEIS:
==============================================================================================================*/



/*
==============================================================================================================
CONFIGURAÇÃO:
==============================================================================================================*/
void setup() {

  //Motores
  pinMode(step_esquerdo, OUTPUT);
  pinMode(step_direito, OUTPUT);
  pinMode(direcao_esquerdo, OUTPUT);
  pinMode(direcao_direito, OUTPUT);
  pinMode(enable_pin, OUTPUT);

  Serial.begin(9600);
  
 
}


/*
==============================================================================================================
PROGRAMA PRINCIPAL:
==============================================================================================================*/
void loop() {
  // Verifica se chegou alguma coisa
  if (Serial.available() > 0) {
    char comando;
    
    //Aqui o pulo do gato, ele fica lendo e atualizando até chegar no último.
    while (Serial.available() > 0) {
      comando = Serial.read();
    }
    
    // ai ele faz o mais recente
    Serial.println(comando);
    
    if (comando == 'w') {
      frente(1);
    }
    else if (comando == 'd') {
      girar_direita(5);
    }
    else if (comando == 'a') {
      girar_esquerda(5);
    }
    else {
      tras(1);
    }
  }
}

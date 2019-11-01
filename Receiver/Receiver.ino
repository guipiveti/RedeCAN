#define LED_ERRO 4

#include <CAN.h>

void setup() {
  Serial.begin(9600);
  pinMode(LED_ERRO, OUTPUT);
  while (!Serial);
  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    digitalWrite(LED_ERRO, HIGH);
    while (1);
  }
}

void loop() {
  int packetSize = CAN.parsePacket();
  if (packetSize) {
    Serial.print("Mensagem recebida de 0x");
    Serial.print(CAN.packetId(), HEX);
    Serial.print("\t");

    if (CAN.packetId() == 0) {                                    //SENSOR DE CHAMAS
      int leitura = CAN.read();
      if (leitura == 1) {
        Serial.println(" ----> Alerta de Fogo!!!");
      }else{
        Serial.println("Sem fogo.");
      }
    } else if (CAN.packetId() == 1) {                             //SENSOR DE TEMPERATURA
      int leitura = CAN.read();
      Serial.print((float(leitura)*5/(1023))/0.01);
      Serial.println("ºC");
    }else if (CAN.packetId() == 2) {                              //SENSOR LDR
      int leitura = CAN.read();
      if (leitura > 190){
      Serial.println("MUITO CLARO");
      }
      else if (leitura < 100){
      Serial.println("ESCURO");
      }
      else{
        Serial.println("CLARIDADE NORMAL");
      }
      Serial.println("");
    }
  }
}

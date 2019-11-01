#define LED_ERRO 4

#define sensor A0

#define endereco_2 7
#define endereco_1 6
#define endereco_0 5

#define D_A 3    //1- Sensor Digital   0- Sensor Analógico

#include <CAN.h>
int leitura =0;
int end_0, end_1, end_2, d_a =0;
int endereco;

void setup() {
  Serial.begin(9600);
  pinMode(sensor, INPUT);
   
  pinMode(endereco_0, INPUT);
  pinMode(endereco_1, INPUT);
  pinMode(endereco_2, INPUT);

  pinMode(D_A, INPUT);
  
  end_0 = digitalRead(endereco_0);
  end_1 = digitalRead(endereco_1);
  end_2 = digitalRead(endereco_2);
  
  d_a = digitalRead(D_A);

  endereco=1*end_0+2*end_1+4*end_2;
  
  while (!Serial);
  Serial.println(end_0);
  Serial.println(end_1);
  Serial.println(end_2);
  //Serial.println(endereco);
  if (!CAN.begin(500E3)) {
    Serial.println("ERRO!!!");
    digitalWrite(LED_ERRO, HIGH);
    ////////////////////////////////////////////////////////////////////RESETAR
    while (1);
  }
}

void loop() {
  leitura = 0;
  if(d_a==0){
    for(int i=0; i<10; i++){
      leitura += analogRead(sensor);
    }
    leitura=leitura/10;                         //CONVERTER V->ºc
    CAN.beginPacket((int)endereco);
    CAN.write(leitura);
    CAN.endPacket();
  }else{
         leitura += digitalRead(sensor);
         CAN.beginPacket((int)endereco);
         CAN.write(leitura);
         CAN.endPacket();
  }
  delay(1000);
}

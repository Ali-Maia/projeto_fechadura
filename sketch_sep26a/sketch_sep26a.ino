#include <SPI.h>
#include <MFRC522v2.h>
#include <MFRC522DriverSPI.h>
#include <MFRC522DriverPinSimple.h>
#include <MFRC522Debug.h>


#define RST_PIN 9
#define LED_VERDE 3
#define LED_VERMELHO 4

MFRC522DriverPinSimple SS_PIN(10);
//MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522DriverSPI driver{SS_PIN}; // Create SPI driver.
//MFRC522DriverI2C driver{}; // Create I2C driver.
MFRC522 mfrc522{driver};  // Create MFRC522 instance.

void setup() {
  Serial.begin(9600);   // Inicia a comunicação serial
  SPI.begin();          // Inicia o SPI bus
  mfrc522.PCD_Init();  // Init MFRC522 board.   // Inicia o módulo RFID
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_VERMELHO, LOW);
}

void loop() {
  // Verifica se uma nova tag está presente
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    delay(50);
    return;
  }

  String conteudo = "";
  // Lê o UID da tag
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    conteudo += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
    conteudo += String(mfrc522.uid.uidByte[i], HEX);
  }
  conteudo.toUpperCase();

  Serial.println(conteudo);  // Envia o UID para o computador via Serial

  // Aguarda resposta do computador
  while (!Serial.available()) {
    delay(10);
  }

  char response = Serial.read();

  if (response == '1') {
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_VERMELHO, LOW);
  } else {
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_VERMELHO, HIGH);
  }

  delay(1000); // Aguarda 1 segundo antes de apagar os LEDs
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_VERMELHO, LOW);
}

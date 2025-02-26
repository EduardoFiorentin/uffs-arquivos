#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10

String uid;

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  Serial.println("Aproxime uma tag do leitor...");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;

  uid = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    uid += String(rfid.uid.uidByte[i], HEX);
  }
  // Serial.print("UID da tag: ");
  Serial.println(uid);

  // Ações baseadas na tag
  // if (uid == "4a5b6c7d") { // Substitua pelo UID da sua tag
  //   Serial.println("Acesso permitido!");
  //   digitalWrite(13, HIGH); // Exemplo: ligar um LED
  //   delay(1000);
  //   digitalWrite(13, LOW);
  // } else {
  //   Serial.println("Acesso negado!");
  // }

  rfid.PICC_HaltA();
  delay(2000);
}

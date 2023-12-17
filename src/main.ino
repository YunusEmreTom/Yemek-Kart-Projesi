#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 7

MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

int blockNum = 2;
byte readBlockData[18];

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Scan a MIFARE 1K Tag to update data...");
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.print("\n");
  Serial.println("**Card Detected**");

  Serial.print(F("Card UID:"));
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.print("\n");

  Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  Serial.println(mfrc522.PICC_GetTypeName(piccType));

  Serial.print("\n");
  Serial.println("Reading from Data Block...");
  ReadDataFromBlock(blockNum, readBlockData);

  // Güncellenmiş veriyi oluştur
  byte originalValue = readBlockData[13];
  byte originalValueY = readBlockData[12];
  //byte updatedValue = (originalValue > 0) ? originalValue - 1 : 0;
  byte updatedValue;
  byte updatedValueY;
  if (originalValue > 0) {
    originalValue -= 1;
    updatedValue = originalValue - 1;
    updatedValueY = originalValueY;
    Serial.print("geçiş yapılabilir");
  } else {
    if (originalValueY > 0) {
      updatedValueY = originalValueY - 1;
      originalValue = 9;
      Serial.print("geçiş yapılabilir");
    } else {
      Serial.print("geçiş yapılamaz");
      updatedValue = 0;
    }
  }

  // Güncellenmiş veriyi yaz
  byte updatedBlockData[16];
  memcpy(updatedBlockData, readBlockData, 16);
  updatedBlockData[13] = updatedValue;
  updatedBlockData[12] = updatedValueY;

  Serial.print("\n");
  Serial.println("Writing to Data Block...");
  WriteDataToBlock(blockNum, updatedBlockData);

  // Okuma işlemi
  Serial.print("\n");
  Serial.println("Reading from Data Block...");
  ReadDataFromBlock(blockNum, readBlockData);

  // Diğer işlemler buraya eklenebilir
}

void WriteDataToBlock(int blockNum, byte blockData[]) {
  // Yetkilendirme işlemi
  MFRC522::StatusCode status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNum, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Authentication failed for Write: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  } else {
    Serial.println("Authentication success");
  }

  // Veriyi yazma işlemi
  status = mfrc522.MIFARE_Write(blockNum, blockData, 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Writing to Block failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  } else {
    Serial.println("Data was written into Block successfully");
  }
}

void ReadDataFromBlock(int blockNum, byte readBlockData[]) {
  // Yetkilendirme işlemi
  byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNum, &key, &(mfrc522.uid));

  if (status != MFRC522::STATUS_OK) {
    Serial.print("Authentication failed for Read: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  } else {
    Serial.println("Authentication success");
  }

  // Veriyi okuma işlemi
  status = mfrc522.MIFARE_Read(blockNum, readBlockData, 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Reading failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  } else {
    Serial.println("Block was read successfully");
  }
}

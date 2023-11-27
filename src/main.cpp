#include <SPI.h>
#include <MFRC522.h>
#include <SD.h>

#define SS_PIN 10 // RFID modülü için kullanılan slave select pin
#define RST_PIN 9 // RFID modülü için kullanılan reset pin
#define RED_LED 5  // Kırmızı LED pin
#define GREEN_LED 6  // Yeşil LED pin

MFRC522 mfrc522(SS_PIN, RST_PIN); // RFID nesnesi oluştur

File myFile; // SD kart dosya nesnesi oluştur

void setup() {
  Serial.begin(9600); // Seri haberleşmeyi başlat
  SPI.begin(); // SPI haberleşmesini başlat
  mfrc522.PCD_Init(); // RFID modülünü başlat

  pinMode(RED_LED, OUTPUT); // Kırmızı LED'i çıkış olarak ayarla
  pinMode(GREEN_LED, OUTPUT); // Yeşil LED'i çıkış olarak ayarla

  if (!SD.begin(4)) { // SD kartı başlat, 4. pin slave select pinidir
    Serial.println("SD kart başlatılamadı!");
    return;
  }
  Serial.println("SD kart başarıyla başlatıldı.");
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    String cardNumber = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      cardNumber += String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      cardNumber += String(mfrc522.uid.uidByte[i], HEX);
    }
    cardNumber.toUpperCase();
    
    Serial.println("Okunan kart numarası: " + cardNumber);
    
    int remainingMeals = getRemainingMeals(cardNumber);

    if (remainingMeals > 0) {
      digitalWrite(GREEN_LED, HIGH); // Yeşil LED'i yak
      digitalWrite(RED_LED, LOW); // Kırmızı LED'i söndür
      
      Serial.println("Yemek hakkınız var. Kalan hak: " + String(remainingMeals));
      
      updateRemainingMeals(cardNumber, remainingMeals - 1); // Yemek hakkını bir azalt
      
      logCardNumber(cardNumber); // Kart numarasını SD karta kaydet
    } else {
      digitalWrite(GREEN_LED, LOW); // Yeşil LED'i söndür
      digitalWrite(RED_LED, HIGH); // Kırmızı LED'i yak
      
      Serial.println("Yemek hakkınız bitmiştir. Yemek yiyemezsiniz.");
    }

    delay(2000); // Kartın sürekli okunmasını önlemek için kısa bir bekleme
  }
}

int getRemainingMeals(String cardNumber) {
  // Bu fonksiyon, kart numarasına göre kalan yemek hakkını SD karttan okur
  String fileName = "/YemekHaklari/" + cardNumber + ".txt";
  
  if (SD.exists(fileName)) {
    myFile = SD.open(fileName, FILE_READ);
    int remainingMeals = myFile.parseInt();
    myFile.close();
    
    return remainingMeals;
  } else {
    // Eğer dosya yoksa, yeni bir dosya oluşturup maksimum yemek hakkını ayarla
    myFile = SD.open(fileName, FILE_WRITE);
    myFile.println("5"); // Örneğin, başlangıçta herkese 5 yemek hakkı verilmiştir
    myFile.close();
    
    return 5;
  }
}

void updateRemainingMeals(String cardNumber, int remainingMeals) {
  // Bu fonksiyon, kart numarasına göre kalan yemek hakkını SD kartta günceller
  String fileName = "/YemekHaklari/" + cardNumber + ".txt";
  
  myFile = SD.open(fileName, FILE_WRITE);
  myFile.println(remainingMeals);
  myFile.close();
}

void logCardNumber(String cardNumber) {
  // Bu fonksiyon, o gün yemek yiyen kişinin kart numarasını SD karta kaydeder
  String fileName = "/GunlukYemekListesi/gunluk_liste.txt";
  
  myFile = SD.open(fileName, FILE_WRITE);
  myFile.println(cardNumber);
  myFile.close();
}

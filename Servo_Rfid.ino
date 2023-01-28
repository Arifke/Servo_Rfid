
////////////////////////Muhammed Arif Keskin///////////////////////

#include<MFRC522.h>       // Rfid kart icin gerekli kutuphaneyi ekliyoruz
#include<SPI.h>           // Rfid haberlesmesi icin SPI kutuphanesini kullanıyoruz
#include<Servo.h>         // Servo motor kutuphanesini ekliyoruz

#define rst_pin 9         // Rfid kart icin RST ve SDA pinlerini tanimliyoruz
#define ss_pin 10
#define servo_pin 8       // Servo'nun takili oldugu pini tanimliyoruz

Servo motor;
MFRC522 rfid(ss_pin ,rst_pin);
byte ID[4]={48,129,141,34};   // byte 0-255 arasindaki degeleri tutabilen 8 bitten olusan degiskenlerdir  

void setup() 
{
 Serial.begin(9600);
 
 SPI.begin();             // SPI haberlesmesini baslatiyoruz 
 rfid.PCD_Init();         // Rfid kartinin calismasinin baslmasi icin Init komutunu ekliyoruz
 motor.attach(servo_pin); // Servo motorun pinin tanimladik
}

void loop()
{
  
 if(!rfid.PICC_IsNewCardPresent())      // Yeni kart okutulmadıgı surece bekleme komutu
  return;
 
 if(!rfid.PICC_ReadCardSerial())       // Kart okutulmadıgı surece bekleme komutu
 return;

if(rfid.uid.uidByte[0]==ID[0] &&       // Kendi kart ID'miz ile okuttugumuz kartin ID'sinin aynı olmasini kontrol ediyoruz
   rfid.uid.uidByte[1]==ID[1] &&       // Kartimizin 1.Byte ile okuttugumuz kartın 1.Byte'ni karsilastirir 
   rfid.uid.uidByte[2]==ID[2] &&
   rfid.uid.uidByte[3]==ID[3] )
   {
   Serial.println("Kapı Acıldı");
   Serial.print("ID Numarasi");
for(int sayac=0;sayac<4;sayac++)
{
  Serial.print(rfid.uid.uidByte[sayac]);
  Serial.print(" ");
}
   Serial.println(" ");
   motor.write(180);                   //Servo motorun haraket etmesi icin kullanilan komut
   delay(5000);
   motor.write(0);
   delay(1000);
   }
   else                                // if'in tam tersi durumunda, gecersiz kart kullanildiginda  
   {
    Serial.println("Gecersiz Kart");
    Serial.print("ID Numarasi");
for(int sayac=0;sayac<4;sayac++)
{
  Serial.print(rfid.uid.uidByte[sayac]);
  Serial.print(" ");
}
   Serial.println(" ");
   }
 rfid.PICC_HaltA();                     // Surekli okuma yapmasini engellemek icin bu komut ile bitiriyoruz
}

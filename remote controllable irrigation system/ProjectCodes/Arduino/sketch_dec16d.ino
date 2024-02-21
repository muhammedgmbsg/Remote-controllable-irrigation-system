#include <SoftwareSerial.h>

SoftwareSerial bluetooth(1, 0); 

int toprakNemPin = A0;
int suMotoruPin = 7;
int suKomut=13;
bool durum;

char komut = '0';

void setup() {
  bluetooth.begin(9600);
  pinMode(toprakNemPin, INPUT);
  pinMode(suMotoruPin, OUTPUT);
  pinMode(suKomut, OUTPUT);
}

void loop() {
  durum=true;
  digitalWrite(suMotoruPin, HIGH);

  int toprakNem = analogRead(toprakNemPin);
  
  
  // Bluetooth üzerinden komut bekleniyor mu?
  if (bluetooth.available() > 0) {
   
    komut = bluetooth.read();  
    if(komut !='1'){
       bluetooth.println("Sulamak için bekleyiniz");
       durum=false;
    }



digitalWrite(suKomut,HIGH);
delay(200);
  
}

 if(1023-toprakNem<500 && 1023-toprakNem>200){
  if(komut=='1'){
    digitalWrite(suMotoruPin, LOW);
    
        bluetooth.println("3 saniye sulama yapılıyor");

    delay(3000);
    digitalWrite(suMotoruPin, HIGH);
   
  }
  else{

    if(durum==true){
     bluetooth.println("Sulama gerekiyor");
    }
  }
 }
 else if(1023-toprakNem<200){
  if(komut=='1'){
    digitalWrite(suMotoruPin, LOW);
   
            bluetooth.println("5 saniye sulama yapılıyor");

    delay(5000); 
    digitalWrite(suMotoruPin, HIGH);
     
  }
  else{
  if(durum==true){
     bluetooth.println("Acil sulama gerekiyor");
    }
     
  }
 }
 else{
  digitalWrite(suMotoruPin, HIGH);
  
 }

  // Bluetooth üzerinden toprak nem seviyesi ve sulama durumunu gönder
  if(durum==true){
  bluetooth.print("NEM:");
  bluetooth.println(1023-toprakNem);
 }
digitalWrite(suKomut,LOW);

  delay(1300);  // Gecikme ekleyerek sensör verilerini kontrol etme sıklığını ayarla
}

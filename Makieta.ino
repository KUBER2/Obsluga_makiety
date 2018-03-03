#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTPIN 8 //ustawiam port na ktorym bedzie podlaczony czujnik
#define DHTTYPE DHT22 //definiuje rodzaj czujnika

LiquidCrystal_I2C lcd1(0x27,16,2);  // Ustawienie wyścietlacza 1 jego adresu i wilkości
LiquidCrystal_I2C lcd2(0x24,16,2);  // Ustawienie wyścietlacza 2 jego adresu i wilkości
DHT dht(DHTPIN, DHTTYPE);  // utworzenie obiektu dth do obslugi czujnika

float humP,tempC;
const int przek2 =  11;
const int wentylator =  10;



//blok deklaracji funkcji
void wyswietlPowitanie();
void wyswietlTemperature(float T);
void wyswietlWilgotnosc(float H);
void sprawdzenieOdczytow(float h, float t);
void pobierzParametry (float& h, float& t);
void wyswietlParametry(float T,float H);

void setup()
{
  pinMode(wentylator, OUTPUT);
  digitalWrite(wentylator, HIGH);
  Serial.begin(9600);
  //while(!Serial);
  dht.begin();
  wyswietlPowitanie();
  pobierzParametry (humP, tempC); 
  sprawdzenieOdczytow(humP, tempC);
}





void loop()
{
  
  delay(2000);  
  pobierzParametry (humP, tempC); 
  sprawdzenieOdczytow(humP, tempC);
  wyswietlParametry(humP, tempC);
  
  if (humP>50) {
      digitalWrite(wentylator, LOW);
    } else {
      digitalWrite(wentylator, HIGH);
    }
  
}













//funkcja wyswietlajaca powitanie
void wyswietlPowitanie(){
  lcd1.init();                      // initialize the lcd 
  lcd1.backlight();
  lcd1.clear();
  lcd1.setCursor(0,0);
  lcd1.print("Witaj");
  lcd2.init();                      // initialize the lcd 
  lcd2.backlight();
  lcd2.clear();
  lcd2.setCursor(0,0);
  lcd2.print("Witaj");
  delay(3000);
  
}
//Funkacja do wyswietlania parametrow
void wyswietlTemperature(float T){
  lcd1.clear();
  lcd1.setCursor(0,0);
  lcd1.print("Temp: ");
  lcd1.print(T);
}
//funkacja do wyswietlania wilgotnosci
void wyswietlWilgotnosc(float H){
  lcd1.clear();
  lcd1.setCursor(0,1);
  lcd1.print("Wilgot: ");
  lcd1.print(H);
}
//funkcja do pobierania paramtrwo z czujnika DTH22
void pobierzParametry (float& h, float& t){
  // odczyt parametrow zajmuje okolo cwierc sekundy, moze potrwac nawet do 2 sekund Reading temperature or humidity takes about 250 milliseconds!
  h = dht.readHumidity(); // odczytuje wilgotnosc
  t = dht.readTemperature(); //odczytuje temperature Read temperature as Celsius (the default)
  Serial.print("\nHumidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");

  
}
void sprawdzenieOdczytow(float h, float t){
  if (isnan(h) || isnan(t) ) {
    lcd1.clear();
    lcd1.setCursor(0,0);
    lcd1.print("blad odczytu");
    return;
    }
}
//Funkcja do wyswietlania temperatury i wilgonosci na LCD
void wyswietlParametry(float H, float T){
  lcd1.clear();
  lcd1.setCursor(0,0);
  lcd1.print("Temp: ");
  lcd1.print(T);
  lcd1.print(" *C");
  lcd1.setCursor(0,1);
  lcd1.print("Wilgot: ");
  lcd1.print(H);
  lcd1.print(" %");
  
}




#include <LiquidCrystal.h>
#include <dht11.h>

dht11 DHT11; // create object of DHT11
#define dhtpin A0 // set the pin to connect to DHT11

LiquidCrystal lcd(2,3,4,5,6,7);
int fan = 11;
int led = 8;
float temp;
int tempMin = 28;
int tempMax = 30;
int fanSpeed;
int fanLCD;

void setup() {
    Serial.begin(9600);// setting up serial monitor

    pinMode(fan, OUTPUT);
    pinMode(led, OUTPUT);
    pinMode(dhtpin, INPUT);
    lcd.begin(16,2);

}

void loop() {
  DHT11.read(dhtpin);// initialize the reading
  temp = getTemp('C');

   Serial.print(getTemp('C'));
   Serial.print("C ");
   Serial.println();

   if (temp < tempMin)
   {
    fanSpeed = 0;
    analogWrite(fan, fanSpeed);
    fanLCD = 0;
    digitalWrite(fan, LOW);
   }

   if ((temp >= tempMin) && (temp <= tempMax))
   {
    fanSpeed = 100;
    fanSpeed = 1.5*fanSpeed;
    fanLCD = map(temp, tempMin, tempMax, 0, 100);
    analogWrite(fan, fanSpeed);
   }

  if (temp > tempMax)
  {
    digitalWrite(led, HIGH);
  } 
  else 
  {
    digitalWrite(led, LOW);
  }

  lcd.print("TEMP: ");
  lcd.print(temp);
  lcd.print("C ");
  lcd.setCursor(0,1);
  lcd.print("FANS: ");
  lcd.print(fanLCD);
  lcd.print("%");
  delay(500);
  lcd.clear();
}

float getTemp(char type) {
  float temp = (float)DHT11.temperature;//get temp
  return temp;
  
}

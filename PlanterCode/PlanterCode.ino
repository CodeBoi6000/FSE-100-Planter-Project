#include <dht.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

dht DHT;

#define DHT11_PIN 7
int redPin= 10;
int greenPin = 9;
int bluePin = 8;
int fan = 13;
#define VRX_PIN  A1
#define VRY_PIN  A0
int BUT_PIN = 6;

double xValue = 0.0;
double yValue = 0.0;
int bValue = 0;

void setup(){
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(fan, OUTPUT);
  pinMode(redPin,  OUTPUT);              
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}
void setColor(int redValue, int greenValue,  int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin,  greenValue);
  analogWrite(bluePin, blueValue);
}
void loop(){
  xValue = double(analogRead(VRX_PIN)-504)/503.00;
  yValue = double(analogRead(VRY_PIN)-518)/505.00;
  bValue = digitalRead(BUT_PIN);
  int chk = DHT.read11(DHT11_PIN);
  lcd.setCursor(0,0); 
  lcd.print("Temp: ");
  // lcd.print(xValue);
  lcd.print(DHT.temperature);
  lcd.print((char)223);
  lcd.print("C   ");
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(DHT.humidity);
  // lcd.print(yValue);
  lcd.print("%");
  //delay(250);
  if (DHT.humidity>63 && DHT.humidity<70){
    setColor(255,50,0);
  } else if (DHT.humidity>69) {
    setColor(255,0,0);
    digitalWrite(fan, 1);
  // } else if (bValue == 1) {
  //   setColor(0,0,255);
  } else {
    setColor(0,255,0);
    digitalWrite(fan, 0);
  }
}
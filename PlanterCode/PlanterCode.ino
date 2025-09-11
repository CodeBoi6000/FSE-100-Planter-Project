#include <dht.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
dht DHT;

#define DHT11_PIN 7
#define VRX_PIN  A1
#define VRY_PIN  A0
int redPin= 10;
int greenPin = 9;
int bluePin = 8;
int fanPin = 13;
int BUT_PIN = 6;

void setup(){
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(fanPin, OUTPUT);
  pinMode(redPin,  OUTPUT);              
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

class UI(){
  void setColor(int redValue, int greenValue,  int blueValue) {
    analogWrite(redPin, redValue);
    analogWrite(greenPin,  greenValue);
    analogWrite(bluePin, blueValue);
  }

  double getJoystick(int axis){
    if (axis == 0) {
      return(digitalRead(BUT_PIN))
    } else if (axis == 1) {
      return(double(analogRead(VRX_PIN)-504)/503.00)
    } else if (axis == 2){
      return(double(analogRead(VRY_PIN)-518)/505.00)
    } else {
      break;
    }
  }
}

class fan() {
  void run(double speed) {
    analogWrite(fanPin, 255 * speed);
  
  void stop() {
    analogWrite(finPin, 0);
  }
}

void loop(){
  lcd.setCursor(0,0); 
  lcd.print("Temp: ");
  lcd.print(DHT.temperature);
  lcd.print((char)223);
  lcd.print("C   ");
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(DHT.humidity);
  lcd.print("%");
  if (DHT.humidity>50 && DHT.humidity<70){
    UI.setColor(255,50,0);
  } else if (DHT.humidity>69) {
    UI.setColor(255,0,0);
    digitalWrite(fan, 1);
  } else {
    UI.setColor(0,255,0);
    digitalWrite(fan, 0);
  }
}
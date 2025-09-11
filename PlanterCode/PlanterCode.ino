#include <dht.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 13, 5, 4, 3, 2);
dht DHT;

#define DHT11_PIN 7
#define VRX_PIN  A1
#define VRY_PIN  A0
int redPin= 10;
int greenPin = 9;
int bluePin = 8;
int fanPin = 11;
int BUT_PIN = 6;

void setup(){
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(fanPin, OUTPUT);
  pinMode(redPin,  OUTPUT);              
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

class UI{
  public:
    void setColor(int redValue, int greenValue,  int blueValue) {
      analogWrite(redPin, redValue);
      analogWrite(greenPin,  greenValue);
      analogWrite(bluePin, blueValue);
    }

  double getJoystick(int axis){
    if (axis == 0) {
      return(digitalRead(BUT_PIN));
    } else if (axis == 1) {
      return(double(analogRead(VRX_PIN)-504)/503.00);
    } else if (axis == 2){
      return(double(analogRead(VRY_PIN)-518)/505.00);
    }
  }
};

class fan {
  public:
    void run(double speed) {
      analogWrite(fanPin, 255 * speed);
    }

  public:
    void stop() {
      analogWrite(fanPin, 0);
    }
};

class tempPID {
  private:
    double ref = 0;
  public:
    void setPID(double P, double I, double D){
      double tP = P;
      double tI = I;
      double tD = D;
    }

    void setRef(double Target){
      ref = Target;
      double accErr = 0;
    }

    void getResult(double Input) {
      double error =  - Input;
    }
};

void loop(){
  int chk = DHT.read11(DHT11_PIN);
  UI UI;
  fan fan;
  lcd.setCursor(0,0); 
  lcd.print("Temp: ");
  lcd.print(DHT.temperature);
  lcd.print((char)223);
  lcd.print("C   ");
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(DHT.humidity);
  lcd.print("%");
  if (DHT.humidity>65 && DHT.humidity<70){
    UI.setColor(255,50,0);
    fan.run(0.5);
  } else if (DHT.humidity>69) {
    UI.setColor(255,0,0);
    fan.run(1);
  } else {
    UI.setColor(0,255,0);
    fan.stop();
  }
}
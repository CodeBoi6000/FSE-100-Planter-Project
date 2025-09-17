#include <dht.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 13, 5, 4, 3, 2); // (RS, E, D4, D5, D6, D7)
dht DHT;

#define DHT11_PIN 7 // DHT11 data pin
#define VRX_PIN  A1 //Joystick X axis
#define VRY_PIN  A0 //Joystick Y axis
int redPin= 10; //Red leg of LED
int greenPin = 9; //Green leg of LED
int bluePin = 8; //Blue leg of LED
int fanPin = 11; //Transister middle pole
int BUT_PIN = 6; //Joystick button

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
    bool startup = true;
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
    double tref = 0;
    double integral = 0;
    double prevError = 0;
    double prevTime = 0;
    double tP;
    double tI;
    double tD;

  public:
    void setPID(double P = 0, double I = 0, double D = 0){
      double tP = P;
      double tI = I;
      double tD = D;
    }

    void setRef(double Target){
      tref = Target;
    }

    double getResult(double Input) {
      double error = Input - tref;
      double time = millis();
      double dt = (time - prevTime)/1000;
      double proportional = error;
      integral += error * dt;
      double derivative = (error - prevError) / dt;
      prevError = error;
      prevTime = time;
      double output = ((0.05 * proportional) + (0.0001 * integral) + (0.001 * derivative));
      if (output > 1) {
        output = 1;
      } else if (output > 0 && output < 0.2) {
        output = 0.2;
      } else if (output < 0) {
        output = 0;
      }
      return (output);
    }
};

UI UI;
fan fan;
tempPID tempPID;
void loop(){
  int chk = DHT.read11(DHT11_PIN);
  tempPID.setPID(0.5,0.00001,0.01);
  tempPID.setRef(70);
  lcd.setCursor(0,0); 
  lcd.print("Temp: ");
  lcd.print(tempPID.getResult(DHT.humidity));
  lcd.print((char)223);
  lcd.print("C   ");
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(DHT.humidity);
  lcd.print("%");
  if (DHT.humidity>65 && DHT.humidity<70){
    UI.setColor(255,50,0);
  } else if (DHT.humidity>69) {
    UI.setColor(255,0,0);
  } else {
    UI.setColor(0,255,0);
  }
  fan.run(tempPID.getResult(DHT.humidity));
}
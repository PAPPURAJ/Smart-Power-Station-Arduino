
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  //Display Pin

//Adjustable Limits
int windLimit = 2;
int solerLimit = 2;
int batteryLimit = 10;


int pin1 = A1;  //Wind Voltage sensor
int pin2 = A3;  //Soler Voltage sensor
int pin3 = A5;  //Battery Voltage sensor

int relay1 = 9; //Wind
int relay2 = 8; //Soler
int relay3 = 7; //Battery

int v1, v2, v3;

float R1 = 27800.0,R2 = 7580.0;
String secondText = "";


void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
}

void loop()
{

  getVolt();

  if (v1 >= windLimit || v2 >= solerLimit) {
    secondText = "Charging ";
    secondText += v1 >= windLimit ? "W" : "";
    secondText += v2 >= solerLimit ? " S" : "";
  }
  else secondText = "Not charging";

  dis("W:" + String(v1) + " S:" + String(v2) + " B:" + String(v3), secondText);

  relay(1, v1 >= windLimit);
  relay(2, v2 >= solerLimit);
  relay(3, v3 >= batteryLimit);
  delay(500);
}


void relay(int pin, int state) {
  switch (pin) {
    case 1:
      digitalWrite(relay1, !state);
      break;
    case 2:
      digitalWrite(relay2, !state);
      break;
    case 3:
      digitalWrite(relay3, state);
      break;

  }
}



void dis(String a, String b) {
  lcd.clear();
  lcd.print(a);
  lcd.setCursor(0, 1);
  lcd.print(b);
}

void getVolt() {
  v1 = (int)(((analogRead(pin1) * 5.0) / 1024.0) / (R2 / (R1 + R2)));
  v2 = (int)(((analogRead(pin2) * 5.0) / 1024.0) / (R2 / (R1 + R2)));
  v3 = (int)(((analogRead(pin3) * 5.0) / 1024.0) / (R2 / (R1 + R2)));
}

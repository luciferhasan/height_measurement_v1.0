#include <LiquidCrystal_I2C.h>

#define Trig 2
#define Echo 3
#define buzzer 11
long duration = 0.0;
int distance = 0;
int measuredHeight = 200;

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup()
{
  pinMode(Trig, OUTPUT);
  pinMode(Echo,INPUT);
  pinMode(buzzer,OUTPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Welcome....");
  delay(3000);
  
}

void loop() 
{
  int distance = findDistance();
  Serial.println(distance);

  if((measuredHeight - distance) > 140)
  {
    while(1)
    {
      Buzz();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Measuring.....");
      delay(1500);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print((measuredHeight - distance));
      lcd.setCursor(5,0);
      lcd.print("CMS");
      int a = measuredHeight - distance;
      int ft = a/30;
      int inch = (a%30)/2.4;
      lcd.setCursor(0,1);
      lcd.print(ft);
      lcd.setCursor(4,1);
      lcd.print("FT");
      lcd.setCursor(7,1);
      lcd.print(inch);
      lcd.setCursor(10,1);
      lcd.print("INCH");
      Serial.println("Height Detected");
      Serial.println((measuredHeight - distance));
      delay(10000);
      break;
    }                 
  }

  else
  {
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Please Stand...");
    lcd.setCursor(0,0);
    lcd.print("SNEH INTL SCHOOL");
    Serial.println(distance);
    delay(100);
  }
}

int findDistance()
{
  digitalWrite(Trig,LOW);
  delayMicroseconds(2);
  digitalWrite(Trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig,LOW);
  duration = pulseIn(Echo,HIGH);
  distance = 0.034*duration/2;

  return distance;
}

void Buzz()
{
  digitalWrite(buzzer,HIGH);
  delay(340);
  digitalWrite(buzzer,LOW);
  delay(172);
  digitalWrite(buzzer,HIGH);
  delay(340);
  digitalWrite(buzzer,LOW);
  delay(172);
}

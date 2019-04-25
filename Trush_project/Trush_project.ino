#include <Servo.h>

struct ldr
{
  char  pin;
  int   oldValue;
  int   newValue;
  int   deference;
};

ldr ldr1;
ldr ldr2;
boolean night;
boolean firstCall;
int greenLed = 13;
int sensitivity;
Servo openBoxeServo;

void setup() {
  // put your setup code here, to run once:
  pinMode(greenLed, OUTPUT);
  openBoxeServo.attach(9);
  Serial.begin(9600);
}

void loop() {
  //fill the pin variable value withe the corespendent analog pin in the arduino board 
  ldr1.pin = A0;
  ldr2.pin = A1;
  //read the value of the analog
  ldr1.newValue = analogRead(ldr1.pin);
  ldr2.newValue = analogRead(ldr2.pin);
  //configure day or night mode
  dayOrNight(ldr1, ldr2);
  //if open the boxw fct returne true then light the led and turne the servo for open the box
  //else turne of the led if its ON
  
  if (openTheBoxe())
  {
    digitalWrite(greenLed, HIGH);
    openBoxeServo.write(120);
    delay(3000);
    digitalWrite(greenLed, LOW);
    openBoxeServo.write(0);
  }
  else
  {
    digitalWrite(greenLed, LOW);
    openBoxeServo.write(0);
  }
  delay(100);
}

boolean openTheBoxe()
{
  //calculate the deference of light in a T time between tow states
  ldr1.deference = ldr1.newValue - ldr1.oldValue;
  ldr2.deference = ldr2.newValue - ldr2.oldValue;

  //pute the new value of light as an old value for the next calcuation of deference
  ldr1.oldValue = ldr1.newValue;
  ldr2.oldValue = ldr2.newValue;

  //change the sensitivity between day and night mesurment
  if (night)
    sensitivity = 30;
   else
    sensitivity = 50;
        
  //print the sensores data in the serial monitor
  printLog(ldr1, ldr2, sensitivity);
  
  //decide to open the boxe or not
  if (ldr1.deference > sensitivity || ldr2.deference > sensitivity)
    return (true);  
  else
     return (false);
}

void dayOrNight(ldr ldr1, ldr ldr2)
{
  if (ldr1.newValue > 800 && ldr2.newValue > 800)
    night = false;
   else
    night = true;
}

void printLog(ldr ldr1, ldr ldr2, int sensitivity)
{
  Serial.println("...................................L O G..................................");
  Serial.println("|  ldr pin  |  Old ldr value  | New ldr value |  Deference | sensitivity |");
  Serial.print("\t");
  Serial.print((int)ldr1.pin - 13);
  Serial.print("\t");
  Serial.print(ldr1.oldValue);
  Serial.print("\t\t");
  Serial.print(ldr1.newValue);
  Serial.print("\t\t");
  Serial.print(ldr1.deference);
  Serial.print("\t\t");
  Serial.print(sensitivity);
  Serial.print("\n");
  Serial.print("\t");
  Serial.print((int)ldr2.pin - 13);
  Serial.print("\t");
  Serial.print(ldr2.oldValue);
  Serial.print("\t\t");
  Serial.print(ldr2.newValue);
  Serial.print("\t\t");
  Serial.print(ldr2.deference);
  Serial.print("\t\t");
  Serial.print(sensitivity);
  Serial.print("\n");
}

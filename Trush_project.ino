#include <Servo.h>
int greenLed = 13;
int oldLdr1Value;
int newLdr1Value;
char ldr1 = A0;
Servo openBoxeServo;

void setup() {
  // put your setup code here, to run once:
  pinMode(greenLed, OUTPUT);
  openBoxeServo.attach(9);
  Serial.begin(6900);
}

void loop() {
  newLdr1Value = analogRead(ldr1);
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
  delay(500);
}

boolean openTheBoxe()
{
  int deference1;
  Serial.println("Old ldr value : ");
  Serial.println(oldLdr1Value);
  Serial.println("New ldr value : ");
  Serial.println(newLdr1Value);
  Serial.println(".......................");
  deference1 = newLdr1Value - oldLdr1Value;
  oldLdr1Value = newLdr1Value;
  if (deference1 > 40)
    return (true);  
  else
     return (false);
}

//Beyza
#include <Servo.h>
// 180 horizontal MAX
Servo horizontal;
int servoh = 90;
int servohLimitHigh = 180;
int servohLimitLow = 0;
Servo vertical;
int servov = 45;
int servovLimitHigh = 180;
int servovLimitLow = 0;
// LDR pin connections
// name = analogpin;
int ldrlt = 0; //LDR sol üst
int ldrrt = 1; //LDR sağ üst
int ldrld = 2; //LDR sol alt
int ldrrd = 3; //LDR sağ alt

// Low-pass filter constants
const float alpha = 0.5;
float prevAVT = 0;
float prevAVD = 0;
float prevAVL = 0;
float prevAVR = 0;

void setup()
{
  Serial.begin(9600);
  // servo connections
  // name.attacht(pin);
  horizontal.attach(9);
  vertical.attach(10);
  horizontal.write(90);
  vertical.write(45);

  delay(3000);
}

void loop()
{
  int lt = analogRead(ldrlt); // sol üst
  int rt = analogRead(ldrrt); // sağ üst
  int ld = analogRead(ldrld); // sol alt
  int rd = analogRead(ldrrd); // sağ alt

  // Apply low-pass filter to smooth sensor readings
  float avt = alpha * prevAVT + (1 - alpha) * (lt + rt) / 2;
  float avd = alpha * prevAVD + (1 - alpha) * (ld + rd) / 2;
  float avl = alpha * prevAVL + (1 - alpha) * (lt + ld) / 2;
  float avr = alpha * prevAVR + (1 - alpha) * (rt + rd) / 2;
  prevAVT = avt;
  prevAVD = avd;
  prevAVL = avl;
  prevAVR = avr;

  // int dtime = analogRead(4)/20;
  // int tol = analogRead(5)/4;
  int dtime = 10;
  int tol = 50;
  int dvert = avt - avd; // check the diffirence of up and down
  int dhoriz = avl - avr; // check the diffirence of left and right

  Serial.print(avt);
  Serial.print(" ");
  Serial.print(avd);
  Serial.print(" ");
  Serial.print(avl);
  Serial.print(" ");
  Serial.print(avr);
  Serial.print(" ");
  Serial.print(dtime);
  Serial.print(" ");
  Serial.print(tol);
  Serial.println(" ");

  if (-1 * tol > dvert || dvert > tol)
  {
    if (avt > avd)
    {
      servov = ++servov;
      if (servov > servovLimitHigh)
      {
        servov = servovLimitHigh;
      }
    }
    else if (avt < avd)
    {
      servov = --servov;
      if (servov < servovLimitLow)
      {
        servov = servovLimitLow;
      }
    }
    vertical.write(servov);
  }
  if (-1 * tol > dhoriz || dhoriz > tol)
  {
    if (avl > avr)
  {
    servoh = --servoh;
    if (servoh < servohLimitLow)
      {
        servoh = servohLimitLow;
      }
    }
    else if (avl < avr)
  {
    servoh = ++servoh;
    if (servoh > servohLimitHigh)
      {
        servoh = servohLimitHigh;
      }
    }
    else if(avl=avr){
    
    horizontal.write(servoh);
  }

  delay(dtime);
}

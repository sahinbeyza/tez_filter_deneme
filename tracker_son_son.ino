#include <Servo.h>
// 180 horizontal MAX
Servo horizontal;
int servoh = 0;
int servohLimitHigh = 120;
int servohLimitLow = 0;
Servo vertical;
int servov = 0;
int servovLimitHigh = 90;
int servovLimitLow =0;
// LDR pin connections
// name = analogpin;
int ldrl = 0; //LDR sol 
int ldrr = 1; //LDR sağ 
int ldrd = 2; //LDR alt
int ldrt = 3; //LDR üst

void setup()
{
  Serial.begin(9600);
  // servo connections
  // name.attacht(pin);
  horizontal.attach(9);
  vertical.attach(10);
  horizontal.write(60);
  vertical.write(45);

  delay(3000);
}
void loop()
{
  int l = analogRead(ldrl); // sol üst
  int r = analogRead(ldrr); // sağ üst
  int d = analogRead(ldrd); // sol alt
  int t = analogRead(ldrt); // sağ alt
  // int dtime = analogRead(4)/20;
  // int tol = analogRead(5)/4;
  const float alpha = 0.75;
float prevT = 0;
float prevD = 0;
float prevL = 0;
float prevR = 0;
float tf = alpha * prevT + (1 - alpha) * (t) ;
float df = alpha * prevD + (1 - alpha) * (d) ;
float lf = alpha * prevL + (1 - alpha) * (l) ;
float rf = alpha * prevR + (1 - alpha) * (r) ;
  prevT = tf;
  prevD = df;
  prevL = lf;
  prevR = rf;
  float dtime = 10;
  int tol = 0.2;
  //int avt = (lt + rt) / 2; // average value top
  //int avd = (ld + rd) / 2; // average value down
  //int avl = (lt + ld) / 2; // average value left
  //int avr = (rt + rd) / 2; // average value right
  int dvert = tf - df; // check the diffirence of up and down
  int dhoriz = lf - rf;// check the diffirence og left and rigt
  Serial.print(tf);
  Serial.print(" ");
  Serial.print(df);
  Serial.print(" ");
  Serial.print(lf);
  Serial.print(" ");
  Serial.print(rf);
  Serial.print(" ");
  Serial.print(dtime);
  Serial.print(" ");
  Serial.print(tol);
  Serial.print(" ");
  Serial.print(" vertical : ");
  Serial.print(servov);
  Serial.print(" ");
  Serial.print("horizontal : ");
  Serial.print(servoh);
  Serial.print("\n");


if (-1 * tol > dvert || dvert > tol)
  {
    if (tf > df)
    {
      servov = ++servov;
      if (servov > servovLimitHigh)
      {
        servov = servovLimitHigh;
      }
    }
    else if (tf < df)
    {
      servov = --servov;
      if (servov < servovLimitLow) {
        servov = servovLimitLow;
      }
    } 
     else if (tf = df)
    {
      // nothing
    }
    vertical.write(servov);
    
  }
 if(-1 * tol > dhoriz || dhoriz > tol)
  {
    if (lf > rf)
    {
      servoh = --servoh;
      if (servoh < servohLimitLow)
      {
        servoh = servohLimitLow;
      }
    }
    else if (lf < rf) {
      servoh = ++servoh; 
      if (servoh > servohLimitHigh)
      {
        servoh = servohLimitHigh;
      }

    }
    else if (lf = rf)
    {
      // nothing
    }
    horizontal.write(servoh);
  } 
  delay(dtime);
}

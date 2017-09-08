#include <SoftwareSerial.h>

char toSend = 0;
int speed=7;
int rad=0;

int Motor1A = 2;
int Motor1B = 3;

int Motor2A = 4;
int Motor2B = 5;

int Motor3A = 6;
int Motor3B = 7;

int Motor4A = 8;
int Motor4B = 9;

void setup()
{
  Serial.begin(9600);
  Serial3.begin(9600);
  Serial.print("$$$");
  delay(100);
  pinMode( Motor1A, OUTPUT );
  pinMode( Motor1B, OUTPUT );
  digitalWrite( Motor1A, LOW );
  digitalWrite( Motor1B, LOW );
  pinMode( Motor2A, OUTPUT );
  pinMode( Motor2B, OUTPUT );
  digitalWrite( Motor2A, LOW );
  digitalWrite( Motor2B, LOW );
  pinMode( Motor3A, OUTPUT );
  pinMode( Motor3B, OUTPUT );
  digitalWrite( Motor3A, LOW );
  digitalWrite( Motor3B, LOW );
  pinMode( Motor4A, OUTPUT );
  pinMode( Motor4B, OUTPUT );
  digitalWrite( Motor4A, LOW );
  digitalWrite( Motor4B, LOW );
}

int flag1 = -1;
int flag2 = -1;


void loop()
{
  if (Serial3.available()>0)
  {
    toSend = (char)Serial3.read();
    Serial.println(toSend);
    if (toSend >= '0' && toSend <= '9')
    {
      speed=(int)toSend-47;
      Serial.println(speed);
    }
    if (toSend == 'S')
    {
      Stop();
    }
    if (toSend == 'F')
    {
      Up();
    }
    if (toSend == 'B')
    {
      Down();
    }
    if (toSend == 'L')
    {
       LeftUp(0);
    }
    if (toSend == 'R')
    {
      RightUp(0);
    }
    if (toSend == 'G')
    {
      LeftUp(1);
    }
    if (toSend == 'I')
    {
      RightUp(1);
    }
    if (toSend == 'H')
    {
      LeftDown();
    }
    if (toSend == 'J')
    {
      RightDown();
    }
  }
}
//upleft g - i
//down h - j
//ledtruoc w
//ledsau u
//loa v
void Up(){
    analogWrite( Motor1A, LOW );
    analogWrite( Motor1B, 25*speed );
    analogWrite( Motor2A, LOW );
    analogWrite( Motor2B, 25*speed );
    analogWrite( Motor3A, LOW );
    analogWrite( Motor3B, 25*speed );
    analogWrite( Motor4A, LOW );
    analogWrite( Motor4B, 25*speed );
}

void Down(){
    analogWrite( Motor1A, 25*speed );
    analogWrite( Motor1B, LOW );
    analogWrite( Motor2A, 25*speed );
    analogWrite( Motor2B, LOW );
    analogWrite( Motor3A, 25*speed );
    analogWrite( Motor3B, LOW );
    analogWrite( Motor4A, 25*speed );
    analogWrite( Motor4B, LOW );
}

void LeftUp(int is){
    if(is==0){
        analogWrite( Motor1A, 25*speed );
        analogWrite( Motor1B, 0 );
        analogWrite( Motor2A, 0 );
        analogWrite( Motor2B, 25*speed );
        analogWrite( Motor3A, 25*speed );
        analogWrite( Motor3B, 0 );
        analogWrite( Motor4A, 0 );
        analogWrite( Motor4B, 25*speed );
    }else{
        analogWrite( Motor1A, 10*rad );
        analogWrite( Motor1B, 10*rad );
        analogWrite( Motor2A, 10*rad );
        analogWrite( Motor2B, 25*speed );
        analogWrite( Motor3A, 10*rad );
        analogWrite( Motor3B, 10*rad );
        analogWrite( Motor4A, 10*rad );
        analogWrite( Motor4B, 25*speed );
    }
}

void RightUp(int is){
    if(is==0){
        analogWrite( Motor1A, 0 );
        analogWrite( Motor1B, 25*speed );
        analogWrite( Motor2A, 25*speed );
        analogWrite( Motor2B, 0 );
        analogWrite( Motor3A, 0 );
        analogWrite( Motor3B, 25*speed );
        analogWrite( Motor4A, 25*speed );
        analogWrite( Motor4B, 0 );
    }else{
        analogWrite( Motor1A, 10*rad );
        analogWrite( Motor1B, 25*speed );
        analogWrite( Motor2A, 10*rad );
        analogWrite( Motor2B, 10*rad );
        analogWrite( Motor3A, 10*rad );
        analogWrite( Motor3B, 25*speed );
        analogWrite( Motor4A, 10*rad );
        analogWrite( Motor4B, 10*rad );
    }
}

void RightDown(){
      analogWrite( Motor1A, 25*speed );
      analogWrite( Motor1B, 10*rad );
      analogWrite( Motor2A, 10*rad );
      analogWrite( Motor2B, 10*rad );
      analogWrite( Motor3A, 25*speed );
      analogWrite( Motor3B, 10*rad );
      analogWrite( Motor4A, 10*rad );
      analogWrite( Motor4B, 10*rad );
}

void LeftDown(){
      analogWrite( Motor1A, 10*rad );
      analogWrite( Motor1B, 10*rad );
      analogWrite( Motor2A, 25*speed );
      analogWrite( Motor2B, 10*rad );
      analogWrite( Motor3A, 10*rad );
      analogWrite( Motor3B, 10*rad );
      analogWrite( Motor4A, 25*speed );
      analogWrite( Motor4B, 10*rad );
}

void Stop(){
      digitalWrite( Motor1A, LOW );
      digitalWrite( Motor2A, LOW );
      digitalWrite( Motor3A, LOW );
      digitalWrite( Motor4A, LOW );
      digitalWrite( Motor1B, LOW );
      digitalWrite( Motor2B, LOW );
      digitalWrite( Motor3B, LOW );
      digitalWrite( Motor4B, LOW );
}


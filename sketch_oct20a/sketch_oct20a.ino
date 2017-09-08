#include <SoftwareSerial.h>

byte toSend = 0;

int bluetoothTx = 2;
int bluetoothRx = 3;
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);


// Motor 1 - control forward and fack
int Motor1A = 5;
int Motor1B = 6;
//Motor 2 - control left and right
int Motor2A = 7;
int Motor2B = 8;
//Motor 3 - control left and right
int Motor3A = 9;
int Motor3B = 10;
//Motor 4 - control left and right
int Motor4A = 11;
int Motor4B = 12;

void setup()
{
  Serial.begin(9600);
  //Setup Bluetooth serial connection to android
  bluetooth.begin(115200);
  bluetooth.print("$$$");
  delay(100);
  bluetooth.println("U,9600,N");
  bluetooth.begin(9600);
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
  if (bluetooth.available())
  {
    toSend = bluetooth.read();
    Serial.println(toSend);
    if (toSend == 'S')
    {
      flag1 = 0;
      flag2 = 0;
      digitalWrite( Motor1A, LOW );
      analogWrite( Motor1B, LOW );
      digitalWrite( Motor2A, LOW );
      analogWrite( Motor2B, LOW );
    }
    if (toSend == 'F' || toSend == 'G' || toSend == 'I')
    {
      if (flag1 != 1)
      {
        flag1 = 1;
        digitalWrite( Motor1A, HIGH );
        analogWrite( Motor1B, 50 );
      }
    }
    if (toSend == 'B' || toSend == 'H' || toSend == 'J')
    {
      if (flag1 != 2)
      {
        flag1 = 2;
        digitalWrite( Motor1B, HIGH );
        analogWrite( Motor1A, 50 );
      }
    }
    if (toSend == 'L' || toSend == 'G' || toSend == 'H')
    {
      if (flag2 != 1)
      {
        flag2 = 1;
        digitalWrite( Motor2B, HIGH );
        analogWrite( Motor2A, 50 );
      }
    }else if (toSend == 'R' || toSend == 'I' || toSend == 'J')
    {
      if (flag2 != 2)
      {
        flag2 = 2;
        digitalWrite( Motor2A, HIGH );
        analogWrite( Motor2B, 50 );
      }
    }else
    {
      if (flag2 != 3)
      {
        flag2 = 3;
        digitalWrite( Motor2A, LOW );
        analogWrite( Motor2B, LOW );
      }
    }
  }
}


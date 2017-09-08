#include <Wire.h>
#include "LiquidCrystal_I2C.h"
#include "Keypad.h"
#include <string.h>

#define IN1 0
#define IN2 1
#define IN3 2
#define IN4 3
#define toiDa 255
#define toiThieu 0

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

LiquidCrystal_I2C lcd(0x3F, 16, 4);

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'0', 'F', 'E', 'D'}
};
byte rowPins[ROWS] = {28, 26, 24, 22}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {36, 34, 32, 30}; //connect to the column pinouts of the keypad

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

unsigned int hongNgoai = 4;
unsigned int trangThai = 0;
uint8_t  pinOut[] = {46, 48, 50, 52};
uint8_t  pinIn[] = {45, 47, 49, 51};
int flag_truyen = 44;
int flag_nhan = 43;

unsigned int d = 0;
unsigned int s1 = 23;
unsigned int s2 = 25;
unsigned int s3 = 27;
unsigned int s4 = 29;
unsigned int s5 = 31;
unsigned int s6 = 33;
int incoming = 0;
//---------------------------------------------------//
//--------------------------------------------------//
template <typename T, int n>
void OUT(uint16_t dat, T(&pins)[n]);
template <typename T, int n>
uint16_t IN(T(&pins)[n]);
void xuLyHongNgoai();
void xuLyNhanDienTien();
void xuLyMuaHang();
void xuLyChonSanPham(char id);
void xuLyChonSoLuong(char sl);
void xuLyGuiTinHieu(char masanpham, char soluong);
void xuLyDuaTienRa();
void stepper(int val, int num);
void out(int i);
void step_x(int x, unsigned int dlay);
int chartoint(char num);
char inttochar(int num);
void duatienvao();
//--------------------------------------------------//
//-------------------------------------------------//
unsigned int flag_step = 0;
unsigned int flag = 0;
unsigned int money = 0;
unsigned int masanpham = 0;
unsigned int soluong = 0;
unsigned int dongia = 1;
unsigned int slmax = 1;
unsigned int count = 0;
unsigned int flag_nhandien = 0;
//-----------------------------------------------------//
//------------------------------------------------------//
void setup()
{
  flag_nhandien = 0;
  d = 0;
  flag_step = 0;
  flag = 0;
  money = 0;
  masanpham = 0;
  slmax = 1;
  soluong = 0;
  dongia = 1;
  count = 0;
  trangThai = 0;
  incoming = 0;
  lcd.init();
  lcd.backlight();

  lcd.setCursor(2, 1);
  lcd.print("Welcome!");

  pinMode(flag_truyen, OUTPUT);
  pinMode(pinOut[0], OUTPUT);
  pinMode(pinOut[1], OUTPUT);
  pinMode(pinOut[2], OUTPUT);
  pinMode(pinOut[3], OUTPUT);
  pinMode(pinOut[4], OUTPUT);
  digitalWrite(flag_truyen, HIGH);

  pinMode(flag_nhan, INPUT_PULLUP);
  pinMode(pinIn[0], INPUT_PULLUP);
  pinMode(pinIn[1], INPUT_PULLUP);
  pinMode(pinIn[2], INPUT_PULLUP);
  pinMode(pinIn[3], INPUT_PULLUP);
  pinMode(pinIn[4], INPUT_PULLUP);

  pinMode(hongNgoai, INPUT_PULLUP);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  int i;
  for (i = 8; i <= 11; i++) pinMode(i, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(s4, OUTPUT);
  pinMode(s5, OUTPUT);
  pinMode(s6, OUTPUT);
}
//--------------------------------------------------//
//---------------------------------------------------//
void loop()
{
  if (flag_step == 0) {
    xuLyHongNgoai();
  }
  if (flag_step == 1) {
    xuLyNhanDienTien();
  }
  if (flag_step == 2) {
    xuLyMuaHang();
  }
}
//-------------------------------------------------------//
//-------------------------------------------------------//
void xuLyNhanDienTien() {
  if (flag_nhandien == 0) {
    lcd.clear();
    lcd.setCursor(2, 1);
    lcd.print("Dang xu ly...");
    flag_nhandien = 1;
  }
  if (flag_nhandien == 1) {
    digitalWrite(flag_truyen, LOW);
    delay(50);
    digitalWrite(flag_truyen, HIGH);
    flag_nhandien = 2;
  }
  if (flag_nhandien == 2) {
    if (digitalRead(flag_nhan) == 0) {
      money = IN(pinIn);
      if (money > 10 || money <= 0) {
        flag_step = 0;
        flag_nhandien = 0;
        xuLyDuaTienRa();
      } else {
        duatienvao();
        flag_step = 2;
        flag_nhandien = 0;
      }
    }
  }
}
//----------------------------------------------------------//
void xuLyMuaHang() {
  if (flag == 0) {
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("$:");
    lcd.setCursor(5, 0);
    if (money == 1) {
      lcd.print("10.000d");
    } else if (money == 2) {
      lcd.print("20.000d");
    } else if (money == 3) {
      lcd.print("30.000d");
    } else if (money == 4) {
      lcd.print("40.000d");
    } else if (money == 5) {
      lcd.print("50.000d");
    } else if (money == 6) {
      lcd.print("60.000d");
    } else if (money == 7) {
      lcd.print("70.000d");
    } else if (money == 8) {
      lcd.print("80.000d");
    } else if (money == 9) {
      lcd.print("90.000d");
    } else if (money == 10) {
      lcd.print("100.000d");
    }

    lcd.setCursor(2, 1);
    lcd.print("Chon san pham");
    lcd.setCursor(0, 2);
    lcd.print("1 -> 6 :");
    flag = 1;
  }
  if (flag == 1) {
    char customKey = customKeypad.getKey();
    if (customKey == '1' || customKey == '2' || customKey == '3' || customKey == '4' || customKey == '5' || customKey == '6') {
      lcd.setCursor(9, 2);
      lcd.print(customKey);
      delay(200);
      xuLyChonSanPham(customKey);
      flag = 2;
    }
  }
  if (flag == 2) {
    if (money > 1) {
      if (count == 0) {
        lcd.clear();
        lcd.setCursor(2, 1);
        lcd.print("Chon so luong");
        lcd.setCursor(-2, 2);
        lcd.print("1 -> ");
        lcd.setCursor(3, 2);
        count++;
        if (count == 1) {
          slmax = money / dongia;
        }
        lcd.print(slmax);
        lcd.setCursor(-2, 2);
        lcd.print(" :");
        count = 2;
      }
      if (count == 2) {
        int sl = 0;
        char customKey = customKeypad.getKey();
        if (customKey) {
          switch (customKey) {
            case '1': sl = 1; break;
            case '2': sl = 2; break;
            case '3': sl = 3; break;
            case '4': sl = 4; break;
            case '5': sl = 5; break;
            case '6': sl = 6; break;
            case '7': sl = 7; break;
            case '8': sl = 8; break;
            case '9': sl = 9; break;
            default: sl = 1; break;
          }
          if (sl > slmax) {
            sl = slmax;
          }
          lcd.setCursor(6, 2);
          lcd.print(customKey);
          delay(200);
          xuLyChonSoLuong(inttochar(sl));
          flag = 3;
          count = 0;
        }
      }
    } else {
      flag = 3;
      count = 0;
    }
  }
  if (flag == 3) {
    money -= dongia * soluong;
    if (money > 10 || money < 0) {
      money = 0;
    }
    lcd.clear();
    lcd.setCursor(2, 1);
    lcd.print("Lay sp");
    lcd.setCursor(2, 2);
    lcd.print("ben duoi");
    xuLyGuiTinHieu(masanpham, soluong);
    if (money <= 0 || money > 10) {
      lcd.clear();
      lcd.setCursor(2, 1);
      lcd.print("Successful");
      lcd.setCursor(-2, 2);
      lcd.print("Thank you!");
      delay(1000);
    }
    flag = 4;
  }
  if (flag == 4) {
    if (money > 0) {
      lcd.clear();
      lcd.setCursor(1, 1);
      lcd.print("Tiep tuc");
      lcd.setCursor(3, 2);
      lcd.print("mua hang...");
      delay(1000);
      flag_step = 2;
      flag = 0;
      count = 0;
    } else {
      flag_step = 0;
      flag = 0;
      count = 0;
    }
  }
}
//----------------------------------------------------//
void xuLyChonSanPham(char id) {
  masanpham = chartoint(id);
}
//------------------------------------------------------//
void xuLyChonSoLuong(char sl) {
  soluong = chartoint(sl);
}
//---------------------------------------------------------//
void xuLyGuiTinHieu(char id, char sl) {
  int ma = chartoint(id);
  int sluong = chartoint(sl);
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  digitalWrite(s4, LOW);
  digitalWrite(s5, LOW);
  digitalWrite(s6, LOW);
  stepper(ma, sluong);
  delay(100);
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  digitalWrite(s4, LOW);
  digitalWrite(s5, LOW);
  digitalWrite(s6, LOW);
}
//----------------------------------------------------------//
void xuLyHongNgoai() {
  lcd.clear();
  lcd.setCursor(2, 1);
  lcd.print("Welcome!");
  if (digitalRead(hongNgoai) == 0)
  {
    trangThai += 1;
    analogWrite(IN1, 255);
    digitalWrite(IN2, LOW );
    digitalWrite(IN3, LOW);
    analogWrite(IN4, 255);
  }
  else
  {
    delay(200);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    if (trangThai > 0) {
      flag_step = 1;
    }
    trangThai = 0;
  }
}
//-----------------------------------------------------//
template <typename T, int n>
void OUT(uint16_t dat, T(&pins)[n])
{
  for (uint8_t i = 0; i < n; i++)
  {
    uint8_t pin = pins[ n - i - 1];
    pinMode(pin, OUTPUT);
    uint16_t k = (0x0001 << i)&dat;

    if (k == 0x0000)
      digitalWrite(pin, LOW);
    else
      digitalWrite(pin, HIGH);
  }
}
//-------------------------------------------------//
template <typename T, int n>
uint16_t IN(T(&pins)[n])
{
  uint16_t k = 0x0000;
  for (uint8_t i = 0; i < n; i++)
  {
    uint8_t pin = pins[n - i - 1];
    pinMode(pin, INPUT_PULLUP);
    if (digitalRead(pin))
    {
      k = k | (0x0001 << i);
    }
  }
  return k;
}
//-------------------------------------------------//
void xuLyDuaTienRa() {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Khong nhan");
  lcd.setCursor(2, 2);
  lcd.print("dang duoc");
  digitalWrite(IN1, LOW);
  analogWrite(IN2, 255 );
  analogWrite(IN3, 255);
  digitalWrite(IN4, LOW);
  delay(2000);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
//------------------------------------------------//
void stepper(int val, int num)
{
  switch (val)
  {
    case 1 : digitalWrite(s1, HIGH);
      step_x(-(200 * num), 30);
      delay (2000); break;
    case 2 : digitalWrite(s2, HIGH);
      step_x(-(num * 200), 30);
      delay (2000); break;
    case 3 : digitalWrite(s3, HIGH);
      step_x(-(200 * num), 30);
      delay (2000); break;
    case 4 : digitalWrite(s4, HIGH);
      step_x(-(200 * num), 30);
      delay (2000); break;
    case 5 : digitalWrite(s5, HIGH);
      step_x(-(200 * num), 30);
      delay (2000); break;
    case 6 : digitalWrite(s6, HIGH);
      step_x(-(200 * num), 30);
      delay (2000); break;
  }
}
//---------------------------------------------------//
void out(int i)
{
  int j;
  for (j = 8; j <= 11; j++)
  {
    int k = i + 8;
    if (k == j)  digitalWrite(j, LOW);
    else digitalWrite(j, HIGH);
  }
}
//-----------------------------------------------------//
void step_x(int x, unsigned int dlay)
{
  int i;
  for (i = 0; i < abs(x); i++)
  {
    if (x < 0)
    {
      if (d > 0) d--; else d = 3;
    }
    else
    {
      if (d < 3) d++; else d = 0;
    }
    out(d);
    delay(dlay);
  }
}
//-----------------------------------------------------//
int chartoint(char num) {
  if (num == '1') {
    return 1;
  } else if (num == '2') {
    return 2;
  } else if (num == '3') {
    return 3;
  } else if (num == '4') {
    return 4;
  } else if (num == '5') {
    return 5;
  } else if (num == '6') {
    return 6;
  } else if (num == '7') {
    return 7;
  } else if (num == '8') {
    return 8;
  } else if (num == '9') {
    return 9;
  } else {
    return 0;
  }
}

char inttochar(int num) {
  switch (num) {
    case 1:
      return '1';
    case 2:
      return '2';
    case 3:
      return '3';
    case 4:
      return '4';
    case 5:
      return '5';
    case 6:
      return '6';
    case 7:
      return '7';
    case 8:
      return '8';
    case 9:
      return '9';
    default:
      return '0';
  }
}

void duatienvao() {
  analogWrite(IN1, 255);
  digitalWrite(IN2, LOW );
  digitalWrite(IN3, LOW);
  analogWrite(IN4, 255);
  delay(2000);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}







#include <MPU6050_tockn.h>
#include <Kalman.h>
#include <Wire.h>
#include <I2Cdev.h> 
#include<Servo.h>
#include <LiquidCrystal.h>

#define killProgramme 12
int buttonState = 0;


const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int numRows = 2;
const int numCols = 16;

Servo motor_1; 
Servo motor_2;

MPU6050 mpu6050(Wire);


void setup() 
{
  motor_1.attach(3); 
  motor_2.attach(11);
  lcd.begin(16, 2);
  lcd.print("DONT MOVE SENSOR");
  lcd.setCursor(0, 1);
  lcd.print("CALIBRATING:");
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  pinMode(12, INPUT);
}

void loop() 
{
  buttonState = digitalRead(killProgramme);
  if (buttonState == HIGH)
  {
    lcd.clear();
    lcd.print("DONT MOVE SENSOR");
    lcd.setCursor(0, 1);
    lcd.print("CALIBRATING:");
    Wire.begin();
    mpu6050.begin();
    mpu6050.calcGyroOffsets(true);
    delay(1000);
  }
  mpu6050.update();
  Serial.print("angleX : ");
  Serial.print(mpu6050.getAngleX());
  Serial.print("\tangleY : ");
  Serial.print(mpu6050.getAngleY());
  Serial.print("\tangleZ : ");
  Serial.println(mpu6050.getAngleZ());
  int roll;
  int pitch;
  roll = mpu6050.getAngleX();
  pitch = mpu6050.getAngleY();
  lcd.clear();
  lcd.print("X:");
  lcd.print(mpu6050.getAngleX());
  lcd.setCursor(0, 1);
  lcd.print("Y:");
  lcd.print(mpu6050.getAngleY());


  motor_2.write(pitch  + 91); 
  motor_1.write(roll * (-1) + 93);
  delay(50); 

}

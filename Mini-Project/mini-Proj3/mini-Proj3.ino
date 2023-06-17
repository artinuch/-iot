/*
หากวัตถุเลื่อนผ่าน Infrared ให้ Servo ทำการเปิด(90 องศา) 10 วินาที พร้อมข้อความแสดงบนหน้าจอ LCD "Open" แล้วปิด(0 องศา) พร้อมแสดงข้อความ "Close"
*/
// TCRT5000 infrared อ่านเพิ่มเติม https://projecthub.arduino.cc/abhilashpatel121/using-ir-sensor-tcrt-5000-with-arduino-60cc92
// https://www.instructables.com/How-to-Use-TCRT5000-IR-Sensor-Module-With-Arduino-/
#include <Servo.h>  // เรียกใช้ library Servo ซึ่งเป็น library ที่มาพร้อมกับ Arduino IDE

Servo myServo;  // สืบทอด class Server ไปที่ class ที่ชื่อ myServo

const int pinIRd = 8; // กำหนดค่าคงที่ Infared ที่ขา 8
int IRvalueD = 0; // ตัวแปรเพื่อรับค่าตรวจวัตถุ

#include <Wire.h> 
#include <LiquidCrystal_I2C.h> //เรียกใช้ library LiquidCrystal_I2C โดย Marco Schwartz
LiquidCrystal_I2C lcd(0x27,16,2);  // กำหนด address เป็น 0x27 สำหรับ 16 ตัวอักษร และ 2 บรรทัด หากรันแล้วไม่มีตัวอักษรขึ้น ให้ปรับ VR หลังจอเพื่อเพิ่มลดแสง backlight หากปรับแล้วยังไม่เห็น แสดงว่า address ผิด ให้ค้น keyword "i2c scanner" จะพบวิธีหา address

unsigned long prev=0;  // เริ่มจับเวลา
unsigned long interval=10000;  // กำหนดระยะเวลาเพื่อคอยปิด

void setup() {
  myServo.attach(9);  // กำหนดขา 9 เป็นขาสั่งงาน Servo
  
  Serial.begin(9600);  
  
  pinMode(pinIRd,INPUT);  กำหนดขา infared ให้เป็น input

  lcd.init(); // สั่งให้ LCD เริ่มทำงาน
  lcd.init();
  lcd.backlight();  // สั่งให้ backlight ทำงาน หากต้องการปิด noBacklight() หากต้องการล้างหน้าจอ clear() เซ็ต cursor ไปที่ 0,0 home()
}

void loop() {
  lcd.clear();  // สั่งล้างหน้าจอ LCD
  IRvalueD = digitalRead(pinIRd);
  unsigned long curr = millis();  // รับค่าเวลาปัจจุบัน
  if(IRvalueD==1) {
    myServo.write(90); // สั่งให้ Servo หมุนไปองศาที่ 90
    lcd.setCursor(0,0); 
    lcd.print("OPEN");
    delay(1000);  // หน่วงเวลาเพื่อให้ Servo ทำงานเสร็จ
    prev = curr;
  } else {
    if (curr - prev >= interval){
      myServo.write(0); // สั่งให้ Servo หมุนไปองศาที่ 0
      lcd.setCursor(0,1); 
      lcd.print("CLOSE");
      delay(1000);  // หน่วงเวลาเพื่อให้ Servo ทำงานเสร็จ
    }else{}
  }
  delay(100);
}

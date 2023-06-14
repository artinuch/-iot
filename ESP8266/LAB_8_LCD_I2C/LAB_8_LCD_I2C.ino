#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  
/* 
กำหนดค่า address ของจอ LCD ที่ 0x27 เป็นจอขนาด 16 อักขระ จำนวน 2 บรรทัด
I2C แต่ละตัวอาจจะมี address ที่ไม่เหมือนกัน ควรจะหา address ให้เจอก่อน keyword ที่ใช้ค้นหาวิธี i2c scanner
*/
void setup()
{
  lcd.init(); // สั่งให้จอเริ่มทำงาน ซึ่งอาจจะต้องสั่ง 2 ครั้ง
  lcd.init();
  
  lcd.backlight(); // สั่งเปิดไฟ backlight หรือไฟพื้นหลัง
  lcd.setCursor(0,0); // กำหนดเริ่มต้นตำแหน่ง currsor ในตำแหน่งที่ 1 และบรรทัดที่ 1 โดยรูปแบบ setCursor(ตำแหน่งตัวอักษร,ตำแหน่งบรรทัด) ตำแหน่งลำดับ 1 จะเริ่มต้นจาก 0
  lcd.print("Hello, world!");
  lcd.setCursor(2,1);
  lcd.print("CS-LRU");
}


void loop()
{
}

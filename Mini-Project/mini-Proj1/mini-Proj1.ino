/*
 วัดระยะวัตถุด้วย Ultrasonic พร้อมแสดงผลบนหน้าจอ LCD เข้าใกล้จุดที่กำหนดในระยะ 5 cm จะสั่ง relay เปิดไฟ เมื่อออกจากระยะ 5 วินาทีแล้วปิด
*/

#define echoPin 3 // Echo Pin
#define trigPin 2 // Trigger Pin
/*
ประกาศขาสำหรับใช้ Ultrasonic โดยที่
ขา 3 รับสัญญาณ Ultrasonic (Echo) 
ขา 2 ส่งสัญญาณ Ultrasonic (Trigger)

*/
#define relayPin 13 // กำหนดขาของ relay

int maximumRange = 10; // กำหนดระยะสูงสุด หน่วย cm
int minimumRange = 0; // กำหนดระยะต่ำสุด หน่วย cm
long duration, distance; 
/* 
ประกาศตัวแปร เพื่อใช้กับ Utrasonic HC-SR04 คลื่นความถี่ในการทำงาน 40kHz ระยะสูงสุดที่สามารถวัดได้ 4 m (400 cm) ระยะต่ำสุดที่สามารถวัดได้ 0.02 m (2 cm)ความแม่นยำ ±3mm - องศาในการวัด 15 องศา
duration คือจำนวนครั้งที่ได้รับสัญญาณ Ultrasonic จากการสะท้อนของสัญญาณเมื่อกระทบวัตถุกลับมาถึงเซนเซอร์เพื่อนำมาใช้คำนวณระยะทาง
distance คือระยะทางที่คำนวนได้
*/

//unsigned long prev=0;  // เริ่มจับเวลา
//unsigned long interval=5000;  // กำหนดระยะเวลาเพื่อคอยปิด

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//เรียกใช้ library LiquidCrystal_I2C โดย Marco Schwartz
LiquidCrystal_I2C lcd(0x27,16,2);  // กำหนด address เป็น 0x27 สำหรับ 16 ตัวอักษร และ 2 บรรทัด หากรันแล้วไม่มีตัวอักษรขึ้น ให้ปรับ VR หลังจอเพื่อเพิ่มลดแสง backlight หากปรับแล้วยังไม่เห็น แสดงว่า address ผิด ให้ค้น keyword "i2c scanner" จะพบวิธีหา address

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT); //กำหนดให้ขา trigger เป็น Output
  pinMode(echoPin, INPUT);  //กำหนดให้ขา echo เป็น Input
  pinMode(relayPin, OUTPUT); //กำหนดให้ขา relayPin เป็น Output
  
  lcd.init(); // สั่งให้ LCD เริ่มทำงาน
  lcd.init();
  lcd.backlight();  // สั่งให้ backlight ทำงาน หากต้องการปิด noBacklight() หากต้องการล้างหน้าจอ clear() เซ็ต cursor ไปที่ 0,0 home()
}

void loop() {
//  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("                ");
  digitalWrite(trigPin, LOW); //ปิดการส่งสัญญาน Ultrasonic
  delayMicroseconds(2); // ไมโครวินาที คือ 1 วินาที มี 1,000,000 ไมโครวินาที
  digitalWrite(trigPin, HIGH);  //เปิดการส่งสัญญาน Ultrasonic
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); //ปิดการส่งสัญญาน Ultrasonic
  duration = pulseIn(echoPin, HIGH);  //นับจำนวนครั้งของสัญญาณที่สามารถรับได้

  distance = (duration * 0.0346) / 2;
/*
  การหาระยะห่าง นำจำนวนครั้งที่นับได้มาหารด้วยระยะเวลาที่คลื่น Ultrasonic เดินทางกระทบวัตถุแล้วสะท้อนกลับมา ซึ่งคลื่น Ultrasonic ที่ความถี่ 40kHz 
  ความเร็วของเสียงคือ 346 เมตร/วินาที หรือแปลงหน่วยได้ 0.0346 เซนติเมตร/มิลลิวินาที (ที่อุณหภูมิ 25 องศาเซลเซียส & เพื่อความสะดวกและง่ายของการคำนวณในที่นี้จึงขอใช้ 346 เมตร/วินาที)
  คำนวณระยะห่างได้ดังนี้ s=vt (s คือ ระยะทางระหว่างวัตถุ, v คือ ความเร็ว, t คือ เวลาที่ใช้ในการเดินทาง)
  แต่เนื่องจากเวลาที่เราได้มาเป็นเวลาที่คลื่นเสียงเดินทางออกไปรวมกับเวลาที่สะท้อนและเดินทางกลับมา เราอยากได้ระยะห่างคือเฉพาะที่เดินทางออกไปชนวัตถุเท่านั้น จึงต้องนำระยะทางมาหารด้วย 2 จึงได้สูตรสุดท้ายคือ
  s=vt/2
*/
  bool state_relay = 0; //กำหนดสถานะเพื่อให้ relay ทำงาน โดยที่ 0 คือหยุดทำงาน 1 คือทำงาน
  
  // เริ่มตรวนสอบระยะห่างเพื่อให้ relay ทำงาน
  if (distance >= maximumRange || distance <= minimumRange) {
    Serial.println("Out of Range");  //แสดงข้อความเมื่ออยู่นอกระยะ
    state_relay = 0;
    digitalWrite(relayPin, LOW);
//    prev = millis();  // เริ่มจับเวลา millis เป็น function ที่คืนค่าเวลา ณ ปัจจุบัน
  }
  else {
    Serial.println(String(distance) + " cm" + "\t" + "In Range");  //แสดงค่าระยะทาง
    digitalWrite(relayPin, HIGH); //สั่ง relay เปิด
    lcd.setCursor(0,1); // กำหนดตำแหน่งเริ่มต้นของการแสดงข้อความ ตัวอักษรที่,บรรทัดที่ โดยตำแหน่งแรกคือ 0
    lcd.print("Open");  // แสดงค่า ณ ตำแหน่งที่กำหนด
//    state_relay = 1;
  }
    
//  unsigned long curr = millis();  // รับค่าเวลาปัจจุบัน
//  if (state_relay == 0) {
//    if (curr - prev >= interval){
//      digitalWrite(relayPin, LOW);  // สั่ง relay ปิด
//    }else{}
//  } else {}

  lcd.setCursor(0,0); 
  lcd.print("Distant "+ String(distance)+" cm");
  lcd.setCursor(0,1);
  lcd.print("Close");
  
  delay(100);
}

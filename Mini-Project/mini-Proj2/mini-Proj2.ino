/*
แสดงผลบนหน้าจอ LCD ครั้งแรกแสดงอุณหภูมิจาก DHT11 กดอีกครั้งผลระยะห่างของฝ่ามือด้วย Ultrasonic กดอีกครั้งแสดงอุณหภูมิจาก DHT11 วนไปเรื่อยๆ
*/

#define echoPin 3 // Echo Pin
#define trigPin 2 // Trigger Pin
/*
ประกาศขาสำหรับใช้ Ultrasonic โดยที่
ขา 3 รับสัญญาณ Ultrasonic (Echo) 
ขา 2 ส่งสัญญาณ Ultrasonic (Trigger)
*/

int maximumRange = 200; // กำหนดระยะสูงสุด หน่วย cm
int minimumRange = 0; // กำหนดระยะต่ำสุด หน่วย cm
long duration, distance; 
/* 
ประกาศตัวแปร เพื่อใช้กับ Utrasonic HC-SR04 คลื่นความถี่ในการทำงาน 40kHz ระยะสูงสุดที่สามารถวัดได้ 4 m (400 cm) ระยะต่ำสุดที่สามารถวัดได้ 0.02 m (2 cm)ความแม่นยำ ±3mm - องศาในการวัด 15 องศา
duration คือจำนวนครั้งที่ได้รับสัญญาณ Ultrasonic จากการสะท้อนของสัญญาณเมื่อกระทบวัตถุกลับมาถึงเซนเซอร์เพื่อนำมาใช้คำนวณระยะทาง
distance คือระยะทางที่คำนวนได้
*/

#define buttonPin 4
// กำหนดให้ขา 4 เป็นขารับค่าปุ่ม

#include "DHT.h"
// เรียกใช้ library DHT sensor library โดย Adafruit

#define DHTTYPE DHT11 // นิยาม DHTTYPE ให้เป็น DHT11 ทั้งนี้ขึ้นอยู่กับว่าใช้ DHT ตัวใด หากใช้ DHT21 ก็กำหนดให้เป็น DHT21 เป็นต้น
#define DHTPIN 5  // กำหนดให้ขา 3 เป็นขารับค่าจาก DHT

DHT dht(DHTPIN, DHTTYPE); // สืบทอด class DHT ไปที่ class ที่ชื่อ dht

int lastButtonState;    // สถานะปุ่มเดิม
int currentButtonState; // สถานะปุ่มปัจจุบัน
bool state=0; //สถานะแสดงผล ตัวแปรประเภท bool จะเก็บข้อมูล True,Flase หรือ 1,0

#include <Wire.h> 
#include <LiquidCrystal_I2C.h> //เรียกใช้ library LiquidCrystal_I2C โดย Marco Schwartz
LiquidCrystal_I2C lcd(0x27,16,2);  // กำหนด address เป็น 0x27 สำหรับ 16 ตัวอักษร และ 2 บรรทัด หากรันแล้วไม่มีตัวอักษรขึ้น ให้ปรับ VR หลังจอเพื่อเพิ่มลดแสง backlight หากปรับแล้วยังไม่เห็น แสดงว่า address ผิด ให้ค้น keyword "i2c scanner" จะพบวิธีหา address

void setup() {
  Serial.begin(9600);
  dht.begin();  //สั่งให้ dht เริ่มทำงาน

  pinMode(buttonPin, INPUT_PULLUP); //กำหนดขาปุ่มเป็น Input pull up โดยเมื่อ กด ค่าที่ได้, 0 ไม่กด ค่าที่ได้ 1

  pinMode(trigPin, OUTPUT); //กำหนดให้ขา trigger เป็น Output
  pinMode(echoPin, INPUT);  //กำหนดให้ขา echo เป็น Input
  
  lcd.init(); // สั่งให้ LCD เริ่มทำงาน
  lcd.init();
  lcd.backlight();  // สั่งให้ backlight ทำงาน หากต้องการปิด noBacklight() หากต้องการล้างหน้าจอ clear() เซ็ต cursor ไปที่ 0,0 home()
}

void loop() {
  lcd.clear();
  lastButtonState    = currentButtonState;      // save the last state
  currentButtonState = digitalRead(buttonPin); // read new state

  if(lastButtonState == HIGH && currentButtonState == LOW) {
    state=!state;
  } else {}
  if (state==1){
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
    lcd.setCursor(0,0); 
    lcd.print("Distant "+ String(distance)+" cm");
  }else{
    
    float h = dht.readHumidity(); // ทำการอ่านค่าความชื้น
    float t = dht.readTemperature();
    /* 
     ทำการอ่านอุณหภูมิ โดยใช้ readTemperature
     รูปแบบ readTemperature(Format)
     โดยที่ Format จะมี 2 รูปแบบคือ
     false หรือ ว่างไว้ จะอ่านค่าออกมาเป็น Celsius
     true จะอ่านค่าออกมาเป็น Fahrenheit
    */ 
    /* 
     ตรวจสอบค่าที่อ่านได้ในตัวแปร ถ้าค่าใดค่าหนึ่งไม่มีค่าจะทำการออกแล้วกลับไปเริ่ม loop ใหม่ 
    */
    if (isnan(h) || isnan(t)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    } 
    lcd.setCursor(0,0); 
    lcd.print("Temp "+ String(t)+" c");
    lcd.setCursor(0,1); 
    lcd.print("Hum "+ String(h)+"%");
  }
  delay(100);
}

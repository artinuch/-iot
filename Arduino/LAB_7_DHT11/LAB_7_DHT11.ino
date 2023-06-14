#include <DHT.h>
// include เป็นการเรียกใช้งาน library ที่มีผู้พัฒนาไว้แล้วเข้ามาใช้งานในโปรแกรม

#define DHTPIN 2     

#define DHTTYPE    DHT11     // DHT 11
//#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE); //เป็นการสืบทอด class ของ DHT ไปเป็น class dht


void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  dht.begin();  //สั่งให้เซนเซอร์เริ่มทำงาน
}

void loop() {
  delay(2000);
  // ในการอ่านอุณหภูมิหรือความชื้นจากเซนเซอร์ โดยส่วนมาจะใช้เวลาในการทำงานแต่ละรอบประมาณ 250 มิลลิวินาที ซึ่งจำเป็นที่จะต้องรอก่อนที่จะทำการอ่าน
  
  float h = dht.readHumidity();
  // ทำการอ่านค่าความชื้น
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
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
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  /*
  isnan เป็น function ที่ใช้ตรวจสอบค่าว่า ว่าง หรือไม่ 
  หากเป็นค่า ว่าง จะส่งค่ากลับคืนมาคือ true หรือ 1 
  หากเป็นค่า ไม่ว่าง จะส่งค่ากลับคืนมาคือ false หรือ 0
  ส่วนสัญลักษณ์ || หมายถึง หรือ (or)
  */

  float hif = dht.computeHeatIndex(f, h); // หาดัชนีความร้อนหน่วยเป็น Fahrenheit
  float hic = dht.computeHeatIndex(t, h, false); // หาดัชนีความร้อนหน่วยเป็น Celsius
  /*
  เป็นการเรียกใช้ computeHeatIndex ซึ่งเป็น function ที่ใช้คำนวณค่าดัชนีความร้อน 
  อุณหภูมิที่คนเรารู้สึกได้ในขณะนั้นว่า อากาศร้อนเป็นอย่างไร
  โดยที่ค่าดัชนีความร้อนดังกล่าวจะใช้อุณหภูมิและความชื้นในการคำนวณ 
  */
 
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  /*
  print(F(ข้อความ)) หรือ Serial.println(F(ข้อความ))
  จะช่วยให้การใช้พื้นที่ของตัวแปร Global variables ใน memory ใช้พื้นที่น้อยลง
  */
}

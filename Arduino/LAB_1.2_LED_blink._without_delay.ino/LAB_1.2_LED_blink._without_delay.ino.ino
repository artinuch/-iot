#define ledpin 2 
int ledState = LOW; // ตัวแปรตัวนี้ถูกใช้เป็นตัวแปรที่เก็บสถานะของหลอด LED
unsigned long previousMillis = 0;
/*
ตัวแปร previousMillis เป็นตัวแปรที่ใช้เก็บค่าเวลาทำงานครั้งก่อน
unsigned เป็นการประกาศประเภทของตัวแปร แบบไม่คิดเครื่องหมาย
จากตัวอย่าง unsigned long จะเป็นการประกาศตัวแปรประเภท long แบบไม่คิดเครื่องหมาย โดยที่ 
long จะเก็บข้อมูลตัวเลข -2,147,483,648 ถึง 2,147,483,649
unsigned long จะเก็บตัวเลข 0 ถึง 4,294,967,296 
*/
const long interval = 1000; // const เป็นตัวแปรประเภท constant ซึ่งเป็นตัวประที่ไม่สามารถเปลี่ยนค่าได้

void setup() {
  pinMode(ledpin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();// ตัวแปรนี้ถูกใช้เป็นตัวแปรที่เก็บค่าเวลา ณ ปัจจุบัน

  if (currentMillis - previousMillis >= interval) {
    /*
    if เป็น function ที่มีไว้กำหนดเส้นทางของตัวโปรแกรม รูปแบบ if (เงื่อนไข) {จริง} else {เท็จ} ในกรณีที่ต้องการให้มีเงื่อนไขเพิ่มเติม สามารถใช้ if (เงื่อนไข) {จริง} else if (เงื่อนไข) {จริง} else {เท็จ}
    currentMillis - previousMillis >= interval แนวคิดคือ เวลาปัจจุบัน - เวลาทำงานครั้งก่อน = เวลาที่ให้หยุดรอ
    */
    
    previousMillis = currentMillis; //ถ้าเงื่อนไขเป็นจริง ให้ทำการเปลี่ยนค่าในตัวแปร previusMillis เป็นเวลาปัจจุบัน

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      // ตรวจสอบสถานะของหลอดไฟ ledState == LOW จริงหรือเท็จ
      // ถ้า จริง จะทำการเปลี่ยนสถานะให้เป็น HIGH
      ledState = HIGH;
    } else {
      // ถ้า เท็จ จะทำการเปลี่ยนสถานะให้เป็น LOW 
      ledState = LOW;
    }

    // สั่งให้ทำงานตามสถานะที่ได้รับจากการใช้งาน if ไปยังขาที่ได้กำหนดไว้
    digitalWrite(ledPin, ledState);
  }
}

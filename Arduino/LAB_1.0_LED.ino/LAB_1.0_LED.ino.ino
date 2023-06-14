#define ledpin 2  //ให้คำนิยาม ledpin ให้มีความหมาย 2 ซึ่งถ้าหากต้องการใช้ 2 ก็ให้เรียกใช้ ledpin ได้เลย
//int ledpin = 2; //กำหนดค่าให้กับตัวแปรชื่อ ledpin ให้มีค่าเท่ากับ 2

void setup() {
  // put your setup code here, to run once:
  pinMode(ledpin, OUTPUT);  
  /* 
  คำสั่ง pinMode เป็นการกำหนดให้ขาของบอร์ดมีรูปแบบเป็น OUTPUT, INPUT, INPUT_PULLUP 
  รูปแบบ pinMode(ขา, INPUT/OUTPUT/INPUT_PULLUP);
  โดยทั่วไปคำสั่งนี้ควรจะอยู่ใน setup
  */
  digitalWrite(ledpin, HIGH);
  /*
  คำสั่ง digitalWrite เป็นคำสั่งให้บอร์ดทำการจ่ายไฟฟ้าออกทางขาที่กำหนด โดยที่
  HIGH คือสั่งให้จ่ายไฟฟ้าออกมา หรืออาจใส่ 1 แทนก็ได้เช่นกัน
  LOW คือคำสั่งให้งดจ่ายไฟฟ้าออกมา หรืออาจใส่ 0 แทนก็ได้เช่นกัน
  */
}

void loop() {
  // put your main code here, to run repeatedly:

}

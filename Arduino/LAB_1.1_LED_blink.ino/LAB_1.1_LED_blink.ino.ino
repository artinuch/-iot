#define ledpin 2  
int interval = 1000;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledpin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledpin, HIGH);
  delay(interval);  // เป็นคำสั่งให้บอร์ดหยุดการทำงานรอเวลาตามที่กำหนด โดยที่หน่วยเป็นมิลลิวินาที รูปแบบ delay(เวลาที่ให้รอ)
  digitalWrite(ledpin,LOW);
  delay(interval);
}

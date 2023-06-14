int Relay1 = 2;
void setup()
{
  Serial.begin(9600);
  pinMode(Relay1, OUTPUT);
  digitalWrite(Relay1, HIGH);
  Serial.println("Relay Open in setup");
}
void loop()
{
  digitalWrite(Relay1, LOW); // ส่งให้ไฟติด
  Serial.println("Relay Open");
  delay(1000);
  digitalWrite(Relay1, HIGH); // ส่งให้ไฟดับ
  Serial.println("Relay Close");
  delay(1000); 
}

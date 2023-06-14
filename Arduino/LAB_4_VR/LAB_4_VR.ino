#define VR A0

void setup() {
  Serial.begin(9600);

  // ข้อสังเกต หากเป็นการรับค่าผ่านขา Analog ไม่จำเป็นต้องกำหนด pinMode ให้กับขา ซึ่งแตกต่างจากการรับค่าผ่านขา Digital
}

void loop() {
  int val = analogRead(VR);
  Serial.println(val);
  delay(100);
}

int analogPin = A5; //ประกาศตัวแปร ให้ analogPin แทนขา analog ขาที่5
int val = 0;
void setup() {
  pinMode(ledPin, OUTPUT); 
  Serial.begin(9600);
}

void loop() {
  val = analogRead(analogPin);
  Serial.print("val = ");
  Serial.println(val); 
  
  delay(100);
}

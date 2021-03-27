void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Empezamos");
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  while(Serial.available()){
    digitalWrite(LED_BUILTIN, HIGH); 
    char a=Serial.read();
   // Serial.print("leido: ");
    //Serial.println(a);
    //delay(2000);
  }
  //Serial.println("Cerrado");
  //delay(1000);
  digitalWrite(LED_BUILTIN, LOW); 
  
}

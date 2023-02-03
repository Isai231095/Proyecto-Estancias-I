void setup() {
   Serial.begin(115200);

   pinMode(2,OUTPUT);
}

void loop() {
  if(Serial.available()>0){
    switch(Serial.read()){
      case '1':
       digitalWrite(2,HIGH);
       break;
      case '0':
      digitalWrite(2,LOW);
       break;
    }
  }
}

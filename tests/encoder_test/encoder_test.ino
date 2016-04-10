void setup() {
pinMode(7, INPUT);
pinMode(8, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  Serial.print("7: ");
  if(digitalRead(7) == HIGH)
  {
    Serial.println("HIGH");
  }
  else
  {
    Serial.println("LOW");
  }

  
  Serial.print("8: ");
  if(digitalRead(8) == HIGH)
  {
    Serial.println("HIGH");
  }
  else
  {
    Serial.println("LOW");
  }
  delay(200);
}




void ultrasonic(){
  long duration, distance;

  // Generate a pulse on the trigger pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure the duration of the pulse on the echo pin
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate the distance in centimeters
  distance = duration * 0.034 / 2;

  // Print distance to serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Check if distance is within range
  if (distance < MAX_DISTANCE_CM) {
    // Turn on the buzzer
  //  tone(BUZZER_PIN, BUZZER_FREQ);
    Serial.println("Object detected!");
    client.publish("buta/jarak/status", "objek di kesan");
    digitalWrite(buzzer,HIGH);
    delay(200);
  } else {
    // Turn off the buzzer
  //  noTone(BUZZER_PIN);
   digitalWrite(buzzer,LOW);
  }
dtostrf(distance, 1, 2, varPotString);
client.publish("buta/jarak", varPotString);
client.publish("buta/jarak/status", "Normal");

}

void suisMsg(){
  int buttonState = digitalRead(BUTTON_PIN);
  Serial.println(buttonState);
  if (buttonState == LOW && (millis() - lastDebounceTime) > debounceDelay) {
    lastDebounceTime = millis();
    // Send message to Telegram
    digitalWrite(buzzer,HIGH);
    Serial.println("Button pressed, message sent");
    client.publish("buta/suis/status", "Button di tekan");
    delay(500);
    
  }

  else {
    client.publish("buta/suis/status", "Button Normal");
    digitalWrite(buzzer,LOW);
  }
  dtostrf(buttonState, 1,2, varPotString);
  client.publish("buta/suis", varPotString);
}

void suhu(){
   sensors.requestTemperatures(); 
   float temperatureC = sensors.getTempCByIndex(0);
    
   dtostrf(temperatureC, 1, 1, varPotString);
   Serial.print("Analog suhu: ");
   Serial.println(varPotString);
   client.publish("buta/suhu", varPotString);
    
}

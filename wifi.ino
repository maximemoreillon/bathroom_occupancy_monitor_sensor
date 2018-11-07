void wifi_setup(){
  WiFi.mode(WIFI_STA);
  
  // Turning LED ON before WiFI connect
  digitalWrite(LED_PIN,LOW);

  gotIpEventHandler = WiFi.onStationModeGotIP([](const WiFiEventStationModeGotIP& event) {
    // Turn LED OFF when WIFI connected
    Serial.print("STA connected, IP: ");
    Serial.println(WiFi.localIP());
    digitalWrite(LED_PIN,HIGH);
  });

  disconnectedEventHandler = WiFi.onStationModeDisconnected([](const WiFiEventStationModeDisconnected& event) {
    // Turn LED ON when WIFI disconnected
    Serial.println("STA disconnected");
    digitalWrite(LED_PIN,LOW);
  });

  Serial.println("Connecting to Wifi...");
  WiFi.begin(WIFI_STA_SSID, WIFI_STA_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(10);
  }

  
}




void wifi_setup(){
  WiFi.mode(WIFI_STA);
  
  // Turning LED ON before WiFI connect
  digitalWrite(LED_PIN,LOW);

  gotIpEventHandler = WiFi.onStationModeGotIP([](const WiFiEventStationModeGotIP& event) {
    // Debug message
    Serial.print("STA connected, IP: ");
    Serial.println(WiFi.localIP());

    // Turn LED OFF when WIFI connected
    digitalWrite(LED_PIN,HIGH);    
  });

  disconnectedEventHandler = WiFi.onStationModeDisconnected([](const WiFiEventStationModeDisconnected& event) {

    // Debug message
    Serial.println("STA disconnected");

    // Turn LED ON when WIFI disconnected
    digitalWrite(LED_PIN,LOW);
  });

  Serial.println("Connecting to Wifi...");
  WiFi.begin(WIFI_STA_SSID, WIFI_STA_PASSWORD);

  // No need to wait for connection?
}




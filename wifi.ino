void set_ap_mode(){
  Serial.println("Switching to AP mode");
  EEPROM.write(EEPROM_MODE_ADDRESS, 0x00);
  EEPROM.commit();
  ESP.restart();
}

void set_sta_mode(){
  Serial.println("Switching to STA mode");
  EEPROM.write(EEPROM_MODE_ADDRESS, 0x01);
  EEPROM.commit();
  ESP.restart();
}

void wifi_sta_setup(){
  WiFi.mode(WIFI_STA);
  
  // Turning LED ON before WiFI connect
  digitalWrite(LED_PIN,LOW);

  gotIpEventHandler = WiFi.onStationModeGotIP([](const WiFiEventStationModeGotIP& event) {
    Serial.println("STA connected");
    digitalWrite(LED_PIN,HIGH);
  });

  disconnectedEventHandler = WiFi.onStationModeDisconnected([](const WiFiEventStationModeDisconnected& event) {
    Serial.println("STA disconnected");
    digitalWrite(LED_PIN,LOW);
  });

  Serial.println("Connecting to Wifi...");
  WiFi.begin(STA_SSID, STA_PASSWORD);

  int attempt_count = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(1);
    attempt_count ++;
    if(attempt_count > 30000) {
      Serial.println("Failed to connect to WiFi, generating access point instead");
      set_ap_mode();
    }
  }
}

void wifi_ap_setup(){
  Serial.println("Creating access point");
  digitalWrite(LED_PIN,LOW); // LED ON to indicate AP mode
  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_SSID, AP_PASSWORD);
}



void wifi_setup(){

  int wifi_mode = EEPROM.read(EEPROM_MODE_ADDRESS);

  if(wifi_mode == 0x01){
    wifi_sta_setup();
  }
  else {
    wifi_ap_setup();
  }
}

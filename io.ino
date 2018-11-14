void read_sensor() {
  
  // Check the state of the door
  toilet_occupied = 1-digitalRead(SENSOR_PIN);

  static int last_toilet_occupied = -1;

  if(toilet_occupied != last_toilet_occupied){
    last_toilet_occupied = toilet_occupied;

    Serial.println("Occupancy changed");
    
    HTTP_send_occupancy();
    WS_send_occupancy();
    
  }
}


void IO_setup(){
  
  pinMode(SENSOR_PIN,INPUT_PULLUP);
  pinMode(LED_PIN,OUTPUT);

  // Turn LED OFF by default
  digitalWrite(LED_PIN,HIGH);
}


void HTTP_send_occupancy(){

  Serial.println("Sending status via HTTP");

  HTTPClient http;

  if(toilet_occupied == 1) {
    http.begin("http://192.168.4.1/status_update?occupied=1");
  }
  else if (toilet_occupied == 0){
    http.begin("http://192.168.4.1/status_update?occupied=0");
  }
  http.GET();
  http.end();
}

void WS_send_occupancy(){
  if(toilet_occupied == 1) {
    ws_server.broadcastTXT(OCCUPIED);
  }
  else if (toilet_occupied == 0){
    ws_server.broadcastTXT(VACANT);
  }
}


void IO_setup(){
  
  pinMode(SENSOR_PIN,INPUT_PULLUP);
  pinMode(LED_PIN,OUTPUT);
  digitalWrite(LED_PIN,HIGH);
}


void sendOccupancy(boolean occupied){

  HTTPClient http;

  if(occupied) {
    http.begin("http://192.168.4.1/status_update?occupied=1");
  }
  else {
    http.begin("http://192.168.4.1/status_update?occupied=0");
  }
  http.GET();
  http.end();
}

void IO_read() {

  int door_state_int = digitalRead(SENSOR_PIN);
  static int last_door_state_int = -1;
  
  // Check if door state changed
  if(door_state_int != last_door_state_int) {
    last_door_state_int = door_state_int;

    if(door_state_int) {
      Serial.println("Door is now open");
      door_state = "OPEN";
      ws_server.broadcastTXT(VACANT,strlen(VACANT));
      sendOccupancy(false);
    }
    else {
      Serial.println("Door is now closed");
      door_state = "CLOSED";
      ws_server.broadcastTXT(OCCUPIED,strlen(OCCUPIED));
      sendOccupancy(true);
      
    }
  }
}


// Libraries
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <EEPROM.h>
#include <ESP8266HTTPClient.h> // To make HTTP requests

// Wifi settings
#define STA_SSID "teliot"
#define STA_PASSWORD "poketenashi"

// AP settings
#define AP_SSID "teliotSensor01"
#define AP_PASSWORD "poketenashi"

// Web server setting
#define WWW_PORT 80
#define WS_PORT 81

// EEPROM parameters
#define EEPROM_MODE_ADDRESS 0x00 //0x00: ap, 0x01: sta

// IO
#define LED_PIN D4
#define SENSOR_PIN D2

// Wifi callbacks
WiFiEventHandler gotIpEventHandler;
WiFiEventHandler disconnectedEventHandler;

// Wifi client for HTTP requests
WiFiClient wifi_client;

// Web server
ESP8266WebServer www_server(WWW_PORT);
WebSocketsServer ws_server = WebSocketsServer(WS_PORT);

// Commands sent through Web Socket
const char VACANT[] = "vacant";
const char OCCUPIED[] = "occupied";

// Door related variables
char* door_state = "UNKNOWN";

void setup() {
  // Mandatory initial delay
  delay(10);

  EEPROM.begin(512);
  
  // Serial init
  Serial.begin(115200);
  Serial.println();
  Serial.println(); // Separate serial stream from initial gibberish
  Serial.println(F(__FILE__ " " __DATE__ " " __TIME__));

  IO_setup();
  wifi_setup();
  web_server_setup();
  websocket_setup();
}

void loop() {
  www_server.handleClient();
  ws_server.loop();
  IO_read();
}

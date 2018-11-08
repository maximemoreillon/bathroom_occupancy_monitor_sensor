/*
 * Flash settings:
 * Board type: Wemos D1 mini
 */

// Libraries
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <ESP8266HTTPClient.h> // To make HTTP requests


// Wifi settings
#define WIFI_STA_SSID "toiletIndicatorNorth"
#define WIFI_STA_PASSWORD "poketenashi"

// Web server setting
#define WWW_PORT 80
#define WS_PORT 81

// IO
#define LED_PIN D4
#define SENSOR_PIN D2

// Wifi callbacks
WiFiEventHandler gotIpEventHandler;
WiFiEventHandler disconnectedEventHandler;

// Wifi client for HTTP requests
WiFiClient wifi_client;

// Web server. mainly used for updates
ESP8266WebServer www_server(WWW_PORT);
WebSocketsServer ws_server = WebSocketsServer(WS_PORT);

// Commands sent through Web Socket
const char VACANT[] = "vacant";
const char OCCUPIED[] = "occupied";

// Toilet occupancy variable
// -1: unknown, 0: vacant, 1: occupied
int toilet_occupied = -1;

void setup() {
  // Mandatory initial delay
  delay(10);
  
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
  read_sensor();
}

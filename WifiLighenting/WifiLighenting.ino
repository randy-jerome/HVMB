#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#define LED_COUNT 600


#ifndef STASSID
#define STASSID "jhome"
#define STAPSK  "superman"
#endif

Adafruit_NeoPixel strip1(LED_COUNT, D1, NEO_GRB + NEO_KHZ800);
const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);

void setup() {
  // put your setup code here, to run once:
  strip1.begin();
  strip1.clear();
  strip1.show();

  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/light", []() {
    RunLight();
    for(int i=0;i<20;i++){
      int dur = random(5, 100);
      int level = random(20, 255);
      FlashStrip(level, dur);
    }
    server.send(200, "text/plain", "done");
  });

    server.begin();
  Serial.println("HTTP server started");
}


void loop() {
  server.handleClient();
  MDNS.update();
  // put your main code here, to run repeatedly:
}

void handleRoot() {
  
  server.send(200, "text/plain", "hello from esp8266!\r\n");
  
}

void RunLight(){
  for(int i = 0; i< LED_COUNT; i = i+7){
    strip1.setPixelColor(i, 0xFFFFFF);
    strip1.setPixelColor(i+1, 0xFFFFFF);
    strip1.setPixelColor(i+2, 0xFFFFFF);
    strip1.setPixelColor(i+3, 0xFFFFFF);
    strip1.setPixelColor(i+4, 0xFFFFFF);
    strip1.setPixelColor(i+5, 0xFFFFFF);
    strip1.setPixelColor(i+6, 0xFFFFFF);
    strip1.show();
  }
  strip1.clear();
  strip1.show();

}

void FlashStrip(int level, int duration){
  for(int i = 0; i< LED_COUNT; i++){
    strip1.setPixelColor(i, level, level, level);
  }
  strip1.show();
  delay(duration);
  strip1.clear();
  strip1.show();
}

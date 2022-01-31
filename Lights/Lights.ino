#include <Adafruit_NeoPixel.h>
//#include <ESP8266WiFi.h>
//#include <WiFiClient.h>
//#include <ESP8266WebServer.h>
//#include <WiFiUdp.h>

#define DEBUG true

#define INDICATOR_PIN D7
#define BUTTON_PIN D1
#define LIGHT_PIN D2
#define UDP_PORT 4210
 
#define LED_COUNT 200

#define STASSID "jhome"
#define STAPSK  "superman"

Adafruit_NeoPixel strip1(1, INDICATOR_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(LED_COUNT, LIGHT_PIN, NEO_GRB + NEO_KHZ800);
//ESP8266WebServer server(80);
//WiFiUDP Udp;

int btnState = 0;
int seq = 0;
bool buttonEventHandled = false;

void setup() {
  Serial.begin(115200);
  Serial.println("starting up");
  // put your setup code here, to run once:
  strip1.begin();
  strip1.clear();
  SetIndicator(0xFF0000); 
  
  strip2.begin();
  strip2.clear();
  strip2.show();

  pinMode(BUTTON_PIN, INPUT);

//  WiFi.mode(WIFI_STA);
//  WiFi.begin(STASSID, STAPSK);
//  
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.print(".");
//  }
//  Serial.print("Connected to ");
//  Serial.println(STASSID);
//  Serial.print("IP address: ");
//  Serial.println(WiFi.localIP());
//  server.begin();
//  Udp.begin(UDP_PORT);
  SetIndicator(0x008800);
    
//  server.on("/light", []() {
//    RunLights(); 
//    server.send(200, "text/plain", "done");
//  });
//
//  server.on("/status", []() {
//    
//  });
Serial.println("startup complete");
}

void loop() {
  //Serial.println("running");
  btnState = digitalRead(BUTTON_PIN);
  //server.handleClient();
 
//  int packetSize = Udp.parsePacket();
//  if (packetSize)
//  {
//    // receive incoming UDP packets
//    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
//    int len = Udp.read(incomingPacket, 255);
//    if (len > 0)
//    {
//      incomingPacket[len] = 0;
//    }
//    Serial.printf("UDP packet contents: %s\n", incomingPacket);
//
//    // send back a reply, to the IP address and port we got the packet from
//    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
//    Udp.write(replyPacket);
//    Udp.endPacket();
//  }


  if(btnState == HIGH && buttonEventHandled == false){
    buttonEventHandled = true;
    Serial.println("button triggered");
    SetIndicator(0x000088);
    int del = random(8000, 12000);
    Serial.printf("delay for %d ms", del);
    delay(del);
        
    Serial.println("Running lights");
    int r = random(40, 80);
    unsigned long t = (unsigned long)random(18, 24) * 1000;
    RunLights(r, t);
    //Serial.println("demo lights");
    //DemoLights();
    //Serial.println("spark");
    //RandomSpark();
    SetIndicator(0x008800);
  } 

  if(btnState == LOW && buttonEventHandled == true){
    buttonEventHandled = false;  
  }

  strip2.clear();
  strip2.show();
  
}

void SetIndicator(uint32_t color){
  strip1.setPixelColor(0, color);
  strip1.show();
}

void RunLights(int len, unsigned long tme){
  Serial.printf("Running lights for %ld \n", tme);
  unsigned long startms = millis();
  Serial.printf("startms %ld \n", startms);
  
  while(startms + tme > millis()){
    len = random(2, 50);
    Serial.printf("flashing for %d times\n", len);
    for(int i=0;i<len;i++){
        int dur = random(5, 100);
        int level = random(20, 255);
        FlashStrip(level, dur);
    }
    strip2.clear();
    strip2.show();
    int pause = random(500, 2000);
    delay(pause);
  }
}

void FlashStrip(int level, int duration){
  for(int i = 0; i< LED_COUNT; i++){
    strip2.setPixelColor(i, level, level, level);
  }
  strip2.show();
  delay(duration);
  strip2.clear();
  strip2.show();
}

void DemoLights(){
  Strike2(1);
  Strike2(2);
  Strike2(4);
  Strike2(8);
  Strike2(16);
}

void Strike2(int skp){
  for(int i=0; i< LED_COUNT; i++){
    strip2.setPixelColor(i, 0xFFFFFF);
    int m = i % skp;
    if(m == 0){
      Serial.println("show");
      Serial.println(i);
      strip2.show();
    }
  }
  strip2.show();
  strip2.clear();
  strip2.show();
  
}

void Strike(int skp){
  for(int i = 0; i< LED_COUNT; i = i+skp){
    for(int ii = 0; ii<skp; ii++){
      strip2.setPixelColor(i+ii, 0xFFFFFF);
      Serial.println(i+ii);
    }
    strip2.show();
  }
  strip2.clear();
  strip2.show();
}

void RandomCrazy(){
  
}

void RandomSpark(){
  for(int i=0; i<LED_COUNT * 100;i++){
     int rnd = random(0, LED_COUNT);
     strip2.setPixelColor(rnd, 0xFFFFFFF);
     strip2.show();
     strip2.clear();
     strip2.show();
  }
  strip2.clear();
  strip2.show();
}

//typedef struct{
//  char* Name;
//  char* Addr;
//}Panel;

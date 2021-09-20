#include <Adafruit_NeoPixel.h>
#define ONBOARDLED_COUNT 600

const int selectButtonPin = 19;
const int startButtonPin = 4;
int selectButtonState = 0;
int startButtonState = 0;
int currentState = 0;
bool selectButtonEventHandled = false;
bool startButtonEventHandled = false;

Adafruit_NeoPixel strip1(ONBOARDLED_COUNT, 6, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  pinMode(selectButtonPin, INPUT);
  pinMode(startButtonPin, INPUT);
  strip1.begin();
  strip1.clear();
  strip1.show();
  strip1.setBrightness(255);
}

void loop() {
  // put your main code here, to run repeatedly:
  startButtonState = digitalRead(startButtonPin);
  selectButtonState = digitalRead(selectButtonPin);

  if(startButtonState == LOW && startButtonEventHandled == false){
    startButtonEventHandled = true;
    RunLight();
    for(int i=0;i<20;i++){
      int dur = random(5, 100);
      int level = random(20, 255);
      FlashStrip(level, dur);
    }
    
    
//    RunLight();
//    delay(20);
//    RunLight();
//    delay(20);
//    RunLight();
  }

  if(startButtonState == HIGH){
    startButtonEventHandled = false;
  }

}

void FlashStrip(int level, int duration){
    for(int i = 0; i< ONBOARDLED_COUNT; i++){
    strip1.setPixelColor(i, level, level, level);
    //delay(1);
    //strip1.show();
  }
strip1.show();
delay(duration);
  strip1.clear();
  strip1.show();
}

void RunLight(){
  for(int i = 0; i< ONBOARDLED_COUNT; i = i+7){
    strip1.setPixelColor(i, 0xFFFFFF);
    strip1.setPixelColor(i+1, 0xFFFFFF);
    strip1.setPixelColor(i+2, 0xFFFFFF);
    strip1.setPixelColor(i+3, 0xFFFFFF);
    strip1.setPixelColor(i+4, 0xFFFFFF);
    strip1.setPixelColor(i+5, 0xFFFFFF);
    strip1.setPixelColor(i+6, 0xFFFFFF);
    //delay(1);
    strip1.show();
  }
//strip1.show();
  strip1.clear();
  strip1.show();
  //TurnOff();
}

void TurnOff(){
  for(int i = 0; i< ONBOARDLED_COUNT; i++){
    strip1.setPixelColor(i, 0x000000);
    
  }
  strip1.show();
}

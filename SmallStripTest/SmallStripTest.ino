#include <Adafruit_NeoPixel.h>

int ledcount = 29;
int startButtonState = 0;
int startButtonPin = 19;
bool startButtonEventHandled = false;

Adafruit_NeoPixel strip1(ledcount, 6, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once33:
  pinMode(startButtonPin, INPUT);
  strip1.begin();
  strip1.clear();
  strip1.show();
  strip1.setBrightness(255);

}

void loop() {
  // put your main code here, to run repeatedly:
  startButtonState = digitalRead(startButtonPin);
  if(startButtonState == LOW && startButtonEventHandled == false){
    startButtonEventHandled = true;
    RunLight();
    for(int i=0;i<200;i++){
      int dur = random(5, 100);
      int level = random(20, 255);
      FlashStrip(level, dur);
    }
  }

  if(startButtonState == HIGH){
    startButtonEventHandled = false;
  }
}


void FlashStrip(int level, int duration){
    for(int i = 0; i< ledcount; i++){
      strip1.setPixelColor(i, level, level, level);
    }
    strip1.show();
    delay(duration);
    strip1.clear();
    strip1.show();
}

void RunLight(){
  for(int i = 0; i< ledcount; i = i+7){
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

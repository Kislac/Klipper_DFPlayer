//#include <Arduino.h>
//
//#define PWMOutputTrack PA9
//#define PWMOutputVolume PA10
//void setup() {
//  // put your setup code here, to run once:
//  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
//  pinMode(PWMOutputTrack, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
//  pinMode(PWMOutputVolume, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
//
//}
//
//unsigned long previousMillis_LedTimer = 0;
//unsigned long previousMillis_AnalogChanger = 0;
//int counter = 0;
//void loop() {
// if (millis() - previousMillis_LedTimer >= 1000) { //led blink, just see there is no running issue
//        previousMillis_LedTimer = millis();
//        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
//  }
//
//  if (millis() - previousMillis_AnalogChanger >= 1000) { //led blink, just see there is no running issue
//        previousMillis_AnalogChanger = millis();
//        if(counter == 0){
//          counter = 1;
//          analogWrite(PWMOutputTrack,0);
//          analogWrite(PWMOutputVolume,0);
//        }else if (counter == 1){
//          counter = 2;
//          analogWrite(PWMOutputTrack,50);
//          analogWrite(PWMOutputVolume,50);
//        }else if (counter == 2){
//          counter = 3;
//          analogWrite(PWMOutputTrack,100);
//          analogWrite(PWMOutputVolume,100);
//        }else if (counter == 3){
//          counter = 4;
//          analogWrite(PWMOutputTrack,150);
//          analogWrite(PWMOutputVolume,150);
//        }else if (counter == 4){
//          counter = 5;
//          analogWrite(PWMOutputTrack,200);
//          analogWrite(PWMOutputVolume,200);
//        }else{
//          counter = 0;
//          analogWrite(PWMOutputTrack,255);
//          analogWrite(PWMOutputVolume,255);
//        }
//
//    }
//
//
//}


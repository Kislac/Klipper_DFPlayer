#include <Arduino.h>

#define PWMOutputTrack D5
#define PWMOutputVolume D6
#define AnalogIn A0
void setup() {
  Serial.begin(9600);
  Serial.printf("\nCode Started\n");
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(PWMOutputTrack, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(PWMOutputVolume, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(AnalogIn, INPUT);     // Initialize the LED_BUILTIN pin as an output

}

unsigned long previousMillis_LedTimer = 0;
unsigned long previousMillis_AnalogChanger = 0;
int counter = 0;
int prev_ReadedValue = 0;

void loop() {
 if (millis() - previousMillis_LedTimer >= 500) { //led blink, just see there is no running issue
        previousMillis_LedTimer = millis();
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }


int ReadedValue = analogRead(AnalogIn)/4;
if(abs(ReadedValue-prev_ReadedValue) >2 ){
  prev_ReadedValue = ReadedValue;
  Serial.printf("ReadedValue: %d\n",ReadedValue);
  analogWrite(PWMOutputTrack,ReadedValue);
}



if (Serial.available() > 0)
{
  char input = Serial.read();
  //if (input >= 48 && input <= 57) //[0,9]
  //{
  //  analogWrite(PWMOutputTrack,16*(input-48));
  //  Serial.printf("PWMOutputTrack: %d\n",16*(input-48));
  //}
  if (input == 'q'){analogWrite(PWMOutputVolume,0);Serial.printf("PWMOutputVolume: 0\n");}
  if (input == 'w'){analogWrite(PWMOutputVolume,30);Serial.printf("PWMOutputVolume: 30\n");}
  if (input == 'e'){analogWrite(PWMOutputVolume,50);Serial.printf("PWMOutputVolume: 50\n");}
  if (input == 'r'){analogWrite(PWMOutputVolume,70);Serial.printf("PWMOutputVolume: 70\n");}
  if (input == 't'){analogWrite(PWMOutputVolume,90);Serial.printf("PWMOutputVolume: 90\n");}
  if (input == 'z'){analogWrite(PWMOutputVolume,110);Serial.printf("PWMOutputVolume: 110\n");}
  if (input == 'u'){analogWrite(PWMOutputVolume,130);Serial.printf("PWMOutputVolume: 130\n");}
  if (input == 'i'){analogWrite(PWMOutputVolume,150);Serial.printf("PWMOutputVolume: 150\n");}
  if (input == 'o'){analogWrite(PWMOutputVolume,170);Serial.printf("PWMOutputVolume: 170\n");}
  if (input == 'p'){analogWrite(PWMOutputVolume,190);Serial.printf("PWMOutputVolume: 190\n");}
  if (input == 'l'){analogWrite(PWMOutputVolume,220);Serial.printf("PWMOutputVolume: 220\n");}






  if (input == 'a'){analogWrite(PWMOutputTrack,0);Serial.printf("PWMOutputTrack: 0\n");}
  if (input == 's'){analogWrite(PWMOutputTrack,75);Serial.printf("PWMOutputTrack: 75\n");}
  if (input == 'd'){analogWrite(PWMOutputTrack,125);Serial.printf("PWMOutputTrack: 125\n");}
  if (input == 'f'){analogWrite(PWMOutputTrack,175);Serial.printf("PWMOutputTrack: 175\n");}
  if (input == 'g'){analogWrite(PWMOutputTrack,225);Serial.printf("PWMOutputTrack: 225\n");}

  if (millis() - previousMillis_AnalogChanger >= 5000) { //led blink, just see there is no running issue
        previousMillis_AnalogChanger = millis();

        //if(counter == 0){
        //  counter = 1;
        //  analogWrite(PWMOutputTrack,0);
        //  analogWrite(PWMOutputVolume,0);
        //  Serial.printf("PWMOutputTrack-0\n");
        //}else if (counter == 1){
        //  counter = 2;
        //  analogWrite(PWMOutputTrack,50);
        //  analogWrite(PWMOutputVolume,50);
        //  Serial.printf("PWMOutputTrack-50\n");
        //}else if (counter == 2){
        //  counter = 3;
        //  analogWrite(PWMOutputTrack,100);
        //  analogWrite(PWMOutputVolume,100);
        //  Serial.printf("PWMOutputTrack-100\n");
        //}else if (counter == 3){
        //  counter = 4;
        //  analogWrite(PWMOutputTrack,150);
        //  analogWrite(PWMOutputVolume,150);
        //  Serial.printf("PWMOutputTrack-150\n");
        //}else if (counter == 4){
        //  counter = 5;
        //  analogWrite(PWMOutputTrack,200);
        //  analogWrite(PWMOutputVolume,200);
        //  Serial.printf("PWMOutputTrack-200\n");
        //}else{
        //  counter = 0;
        //  analogWrite(PWMOutputTrack,255);
        //  analogWrite(PWMOutputVolume,255);
        //  Serial.printf("PWMOutputTrack-255\n");
        //}

    }


}
}


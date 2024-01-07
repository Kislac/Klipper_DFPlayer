//pio device monitor -p COM6 -b 9600
//7E  FF  06  3F  00  00  01  EE  AA  EF
#include <Arduino.h>

#include "SoftwareSerial.h"
# define Start_Byte 0x7E
# define Version_Byte 0xFF
# define Command_Length 0x06
# define End_Byte 0xEF
# define Acknowledge 0x01 //Returns info with command 0x41 [0x01: info, 0x00: no info]


#define PWMInputTrack PA7
#define PWMInputVolume PA5
#define TestPWM PA6
unsigned long previousMillis_LedTimer = 0;
unsigned long Stabilizer_Timer = 0;
unsigned long previousMillis_PWMInput = 0;
unsigned long WaitForStab = 0;
unsigned long WaitForStab2 = 0;
bool Stabilizer_Flag = true;
bool Stabilizer_Flag2 = true;

int prev_PWMInputTrack = 1;
int prev_PWMInputVolume = 1;
int switchs = 0;
int Current_PWMInputTrack = 0;
int Current_PWMInputVolume = 0;


SoftwareSerial mySerial(PB1, PB0);    // RX pin = 10, TX pin = 11    //13/15
void execute_CMD(byte CMD, byte Par1, byte Par2);

void setup () {
  Serial.begin(9600);
  //Serial1.begin(9600);
  mySerial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(PWMInputTrack, INPUT_PULLDOWN);
  pinMode(PWMInputVolume, INPUT_PULLDOWN);
  pinMode(TestPWM, OUTPUT);
  analogWrite(TestPWM,0);
  Serial.printf("\nSend request for initialization parameters\n");
  execute_CMD(0x3F, 0, 0); // Send request for initialization parameters

  Serial.printf("Wait until initialization parameters are received (10 bytes)...\n");
  //while (mySerial.available()>0) // Wait until initialization parameters are received (10 bytes)
  //delay(30); // Pretty long delays between succesive commands needed (not always the same)
  //delay(500);
  // Initialize sound to very low volume. Adept according used speaker and wanted volume
  Serial.printf("Set the volume (0x00~0x30)\n");
  execute_CMD(0x06, 0, 15); // Set the volume (0x00~0x30)
  //for (byte k=0; k<100; k++){
  //  //execute_CMD(0x06, 0, 5); // Set the volume (0x00~0x30)
  //  Serial1.printf("Serial1: %d\n",k);
  //  mySerial.printf("mySerial: %d\n",k);
  //  Serial.printf("Serial0: %d\n",k);
  //  delay(100);
  //}
  
}



int VolumeState = 11;
int Change_Volume;
int TrackState;

void loop () {
  if (millis() - previousMillis_LedTimer >= 500) { //led blink, just see there is no running issue
        previousMillis_LedTimer = millis();
    
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }


  //  Current_PWMInputTrack = analogRead(PWMInputTrack)/4; 
  //if (abs(Current_PWMInputTrack-prev_PWMInputTrack) >= 10){
  //  prev_PWMInputTrack = Current_PWMInputTrack;
  //  Serial.printf("PWMInputTrack: %d\n", Current_PWMInputTrack);
  //}
//
  //  analogWrite(TestPWM,Current_PWMInputTrack);


//if (millis() - previousMillis_PWMInput >= 100) { //led blink, just see there is no running issue
//    previousMillis_PWMInput = millis();
//    int PWMInputVolume_value = analogRead(PWMInputVolume)/4;
//    int PWMInputVolume_per = PWMInputVolume_value*100/255;
//    //Serial.printf("PWMInputTrack: %d - %f% \n", analogRead(PWMInputTrack)/4, (analogRead(PWMInputTrack)/4)/255*100);
//    Serial.printf("PWMInputVolume: %d - %dS \n", PWMInputVolume_value, PWMInputVolume_per);
//  }


  Current_PWMInputVolume = analogRead(PWMInputVolume)/4; 
  //if (Current_PWMInputVolume != prev_PWMInputVolume){
  if (abs(Current_PWMInputVolume-prev_PWMInputVolume) > 5 ){
    prev_PWMInputVolume = Current_PWMInputVolume;
    //execute_CMD(0x06, 0, Change_Volume);
    Serial.printf("Current_PWMInputVolume: %d\n", Current_PWMInputVolume);
    WaitForStab = millis();
    Stabilizer_Flag = true;
  }


if( ((millis() - WaitForStab) >= 1000) && Stabilizer_Flag == true){
Stabilizer_Flag = false;



    
  if(Current_PWMInputVolume > 0 && 20 > Current_PWMInputVolume && VolumeState != 11){
      VolumeState = 11;
      Serial.printf("Change_Volume --> StandBy\n", Current_PWMInputVolume);
  }else if(Current_PWMInputVolume > 21 && 40 > Current_PWMInputVolume && VolumeState != 0){
      VolumeState = 0; Change_Volume = VolumeState*3;execute_CMD(0x06, 0, Change_Volume);Serial.printf("Volume changed to : %d\n", Change_Volume);
  }else if(Current_PWMInputVolume > 41 && 60 > Current_PWMInputVolume && VolumeState != 1){
      VolumeState = 1; Change_Volume = VolumeState*3;execute_CMD(0x06, 0, Change_Volume);Serial.printf("Volume changed to : %d\n", Change_Volume);
  }else if(Current_PWMInputVolume > 61 && 80 > Current_PWMInputVolume && VolumeState != 2){
      VolumeState = 2; Change_Volume = VolumeState*3;execute_CMD(0x06, 0, Change_Volume);Serial.printf("Volume changed to : %d\n", Change_Volume);
  }else if(Current_PWMInputVolume > 81 && 100 > Current_PWMInputVolume && VolumeState != 3){
      VolumeState = 3; Change_Volume = VolumeState*3;execute_CMD(0x06, 0, Change_Volume);Serial.printf("Volume changed to : %d\n", Change_Volume);
  }else if(Current_PWMInputVolume > 101 && 120 > Current_PWMInputVolume && VolumeState != 4){
      VolumeState = 4; Change_Volume = VolumeState*3;execute_CMD(0x06, 0, Change_Volume);Serial.printf("Volume changed to : %d\n", Change_Volume);
  }else if(Current_PWMInputVolume > 121 && 140 > Current_PWMInputVolume && VolumeState != 5){
      VolumeState = 5; Change_Volume = VolumeState*3;execute_CMD(0x06, 0, Change_Volume);Serial.printf("Volume changed to : %d\n", Change_Volume);
  }else if(Current_PWMInputVolume > 141 && 160 > Current_PWMInputVolume && VolumeState != 6){
      VolumeState = 6; Change_Volume = VolumeState*3;execute_CMD(0x06, 0, Change_Volume);Serial.printf("Volume changed to : %d\n", Change_Volume);
  }else if(Current_PWMInputVolume > 161 && 180 > Current_PWMInputVolume && VolumeState != 7){
      VolumeState = 7; Change_Volume = VolumeState*3;execute_CMD(0x06, 0, Change_Volume);Serial.printf("Volume changed to : %d\n", Change_Volume);
  }else if(Current_PWMInputVolume > 181 && 200 > Current_PWMInputVolume && VolumeState != 8){
      VolumeState = 8; Change_Volume = VolumeState*3;execute_CMD(0x06, 0, Change_Volume);Serial.printf("Volume changed to : %d\n", Change_Volume);
  }else if(Current_PWMInputVolume > 201 && 220 > Current_PWMInputVolume && VolumeState != 9){
      VolumeState = 9; Change_Volume = VolumeState*3;execute_CMD(0x06, 0, Change_Volume);Serial.printf("Volume changed to : %d\n", Change_Volume);
  }else if(Current_PWMInputVolume > 221 && 255 > Current_PWMInputVolume && VolumeState != 10){
      VolumeState = 10; Change_Volume = VolumeState*3;execute_CMD(0x06, 0, Change_Volume);Serial.printf("Volume changed to : %d\n", Change_Volume);
  }
}


  Current_PWMInputTrack = analogRead(PWMInputTrack)/4; 
  //if (Current_PWMInputVolume != prev_PWMInputVolume){
  if (abs(Current_PWMInputTrack-prev_PWMInputTrack) > 5 ){
    prev_PWMInputTrack = Current_PWMInputTrack;
    WaitForStab2 = millis();
    Stabilizer_Flag2 = true;
  }


if( ((millis() - WaitForStab2) >= 1000) && Stabilizer_Flag2 == true){
Stabilizer_Flag2 = false;

  if(prev_PWMInputTrack > 0 && 50 > prev_PWMInputTrack && TrackState != 0){
    TrackState = 0;
    Serial.printf("Track is 0 --> Standby %d\n", prev_PWMInputTrack); 
  }else if(prev_PWMInputTrack > 51 && 100 > prev_PWMInputTrack && TrackState != 1){
    TrackState = 1;
    execute_CMD(0x0F, 1, 1);
    Serial.printf("Play 1st sound; Print Started\n"); 
  }else if(prev_PWMInputTrack > 101 && 150 > prev_PWMInputTrack && TrackState != 2){
    TrackState = 2;
    execute_CMD(0x0F, 1, 2);
    Serial.printf("Play 2st sound; FilamentChange\n"); 
  }else if(prev_PWMInputTrack > 151 && 200 > prev_PWMInputTrack && TrackState != 3){
    TrackState = 3;
    execute_CMD(0x0F, 1, 3);
    Serial.printf("Play 3st sound; Print Ended\n"); 
  }else if(prev_PWMInputTrack > 201 && 255 > prev_PWMInputTrack && TrackState != 4){
    TrackState = 4;
    execute_CMD(0x0F, 1, 4);
    Serial.printf("Play 4st sound; Error\n"); 
  }
}



    

  

  //Serial.printf("PWMInputVolume: %d\n", Current_PWMInputVolume);
  //Serial.printf("PWMInputTrack: %d\n", Current_PWMInputTrack);
  //delay(100);
  //digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on by making the voltage LOW
  //Serial.printf("Alma\n");
  //mySerial.printf("Alma\n");
  //delay(500);
  //digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
  //delay(500);
  if (Serial.available())
  {
    //-------
    // Input Serial monitor: Command and the two parameters in decimal numbers (NOT HEX)
    // E.g. 3,0,1 (or 3 0 1 or 3;0;1) will play first track on the TF-card
    byte Command = Serial.parseInt();
    byte Parameter1 = Serial.parseInt();
    byte Parameter2 = Serial.parseInt();
    // Write the input at the screen
    Serial.print("Command : 0x");if (Command < 16) Serial.print("0"); Serial.print(Command, HEX);
    Serial.print("("); Serial.print(Command, DEC);
    Serial.print("); Parameter: 0x");if (Parameter1 < 16) Serial.print("0");Serial.print(Parameter1, HEX);
    Serial.print("("); Serial.print(Parameter1, DEC);
    Serial.print("), 0x");if (Parameter2 < 16) Serial.print("0");Serial.print(Parameter2, HEX);
    Serial.print("("); Serial.print(Parameter2, DEC);Serial.println(")");
    // Excecute the entered command and parameters
    execute_CMD(Command, Parameter1, Parameter2);
    //-------
    //byte StartBit = Serial.parseInt();
    //byte Ver = Serial.parseInt();
    //byte Len = Serial.parseInt();
    //byte CMD2 = Serial.parseInt();
    //byte Feedback = Serial.parseInt();
    //byte Param1 = Serial.parseInt();
    //byte Param2 = Serial.parseInt();
    //byte Check1 = Serial.parseInt();
    //byte Check2 = Serial.parseInt();
    //byte EndBit = Serial.parseInt();
    //byte Command_line[10] = { StartBit, Ver, Len, CMD2, Feedback,
    //  Param1, Param2, Check1, Check2, EndBit};
    ////Send the command line to the module
    //for (byte k=0; k<10; k++)
    //{
    //  mySerial.write( Command_line[k]);
    //}
  }

    if (mySerial.available()>=10)
  {
    // There is at least 1 returned message (10 bytes each)

    // Read the returned code
    byte Returned[10];
    for (byte k=0; k<10; k++)
      Returned[k] = mySerial.read();
    // Wtite the returned code at the screen
    Serial.print("Returned: 0x"); if (Returned[3] < 16) Serial.print("0"); Serial.print(Returned[3],HEX);
    Serial.print("("); Serial.print(Returned[3], DEC);
    Serial.print("); Parameter: 0x"); if (Returned[5] < 16) Serial.print("0"); Serial.print(Returned[5],HEX);
    Serial.print("("); Serial.print(Returned[5], DEC);
    Serial.print("), 0x"); if (Returned[6] < 16) Serial.print("0"); Serial.print(Returned[6],HEX);
    Serial.print("("); Serial.print(Returned[6], DEC); Serial.println(")");
  }

}

void execute_CMD(byte CMD, byte Par1, byte Par2)
  // Excecute the command and parameters
{
  // Calculate the checksum (2 bytes)
  word checksum = -(Version_Byte + Command_Length + CMD + Acknowledge + Par1 + Par2);
  // Build the command line
  byte Command_line[10] = { Start_Byte, Version_Byte, Command_Length, CMD, Acknowledge,
      Par1, Par2, highByte(checksum), lowByte(checksum), End_Byte};
  //Send the command line to the module
  for (byte k=0; k<10; k++)
  {
    mySerial.write( Command_line[k]);
  }
}
////pio device monitor -p COM4 -b 9600
////7E  FF  06  3F  00  00  01  EE  AA  EF
//#include <Arduino.h>
//
//#include "SoftwareSerial.h"
//# define Start_Byte 0x7E
//# define Version_Byte 0xFF
//# define Command_Length 0x06
//# define End_Byte 0xEF
//# define Acknowledge 0x01 //Returns info with command 0x41 [0x01: info, 0x00: no info]
//
//
//#define PWMInputTrack A0
//#define PWMInputVolume 4
//unsigned long previousMillis_LedTimer = 0;
//
//int prev_PWMInputTrack = 1;
//int prev_PWMInputVolume = 1;
//int switchs = 0;
//int Current_PWMInputTrack = 0;
//int Current_PWMInputVolume = 0;
//
//
//SoftwareSerial mySerial(14, 16);    // RX pin = 10, TX pin = 11    //13/15
//void execute_CMD(byte CMD, byte Par1, byte Par2);
//
//void setup () {
//  Serial.begin(9600);
//  //Serial1.begin(9600);
//  mySerial.begin(9600);
//  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
//  pinMode(PWMInputTrack, INPUT);
//  pinMode(PWMInputVolume, INPUT);
//  Serial.printf("\nSend request for initialization parameters\n");
//  execute_CMD(0x3F, 0, 0); // Send request for initialization parameters
//
//  Serial.printf("Wait until initialization parameters are received (10 bytes)...\n");
//  //while (mySerial.available()>0) // Wait until initialization parameters are received (10 bytes)
//  //delay(30); // Pretty long delays between succesive commands needed (not always the same)
//  //delay(500);
//  // Initialize sound to very low volume. Adept according used speaker and wanted volume
//  Serial.printf("Set the volume (0x00~0x30)\n");
//  execute_CMD(0x06, 0, 15); // Set the volume (0x00~0x30)
//  //for (byte k=0; k<100; k++){
//  //  //execute_CMD(0x06, 0, 5); // Set the volume (0x00~0x30)
//  //  Serial1.printf("Serial1: %d\n",k);
//  //  mySerial.printf("mySerial: %d\n",k);
//  //  Serial.printf("Serial0: %d\n",k);
//  //  delay(100);
//  //}
//  
//}
//
//
//
//
//void loop () {
//  if (millis() - previousMillis_LedTimer >= 500) { //led blink, just see there is no running issue
//        previousMillis_LedTimer = millis();
//        if(switchs == 0){
//          switchs = 1;
//          analogWrite(LED_BUILTIN,0);
//          //Serial.printf("analogWrite_LED_BUILTIN: 0\n");
//        }else if (switchs == 1){
//          switchs = 2;
//          analogWrite(LED_BUILTIN,100);
//          //Serial.printf("analogWrite_LED_BUILTIN: 100\n");
//        }else{
//          switchs = 0;
//          analogWrite(LED_BUILTIN,255);
//          //Serial.printf("analogWrite_LED_BUILTIN: 255\n");
//        }
//        
//        //digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
//  }
//
//
//    Current_PWMInputTrack = analogRead(PWMInputTrack); 
//  if (Current_PWMInputTrack != prev_PWMInputTrack){
//    prev_PWMInputTrack = Current_PWMInputTrack;
//    Serial.printf("PWMInputTrack: %d\n", Current_PWMInputTrack);
//  }
//
//  
//
//  Current_PWMInputVolume = analogRead(PWMInputVolume); 
//  if (Current_PWMInputVolume != prev_PWMInputVolume){
//    prev_PWMInputVolume = Current_PWMInputVolume;
//    Serial.printf("PWMInputVolume: %d\n", Current_PWMInputVolume);
//  }
//
//  //Serial.printf("PWMInputVolume: %d\n", Current_PWMInputVolume);
//  //Serial.printf("PWMInputTrack: %d\n", Current_PWMInputTrack);
//  //delay(100);
//  //digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on by making the voltage LOW
//  //Serial.printf("Alma\n");
//  //mySerial.printf("Alma\n");
//  //delay(500);
//  //digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
//  //delay(500);
//  if (Serial.available())
//  {
//    //-------
//    // Input Serial monitor: Command and the two parameters in decimal numbers (NOT HEX)
//    // E.g. 3,0,1 (or 3 0 1 or 3;0;1) will play first track on the TF-card
//    byte Command = Serial.parseInt();
//    byte Parameter1 = Serial.parseInt();
//    byte Parameter2 = Serial.parseInt();
//    // Write the input at the screen
//    Serial.print("Command : 0x");if (Command < 16) Serial.print("0"); Serial.print(Command, HEX);
//    Serial.print("("); Serial.print(Command, DEC);
//    Serial.print("); Parameter: 0x");if (Parameter1 < 16) Serial.print("0");Serial.print(Parameter1, HEX);
//    Serial.print("("); Serial.print(Parameter1, DEC);
//    Serial.print("), 0x");if (Parameter2 < 16) Serial.print("0");Serial.print(Parameter2, HEX);
//    Serial.print("("); Serial.print(Parameter2, DEC);Serial.println(")");
//    // Excecute the entered command and parameters
//    execute_CMD(Command, Parameter1, Parameter2);
//    //-------
//    //byte StartBit = Serial.parseInt();
//    //byte Ver = Serial.parseInt();
//    //byte Len = Serial.parseInt();
//    //byte CMD2 = Serial.parseInt();
//    //byte Feedback = Serial.parseInt();
//    //byte Param1 = Serial.parseInt();
//    //byte Param2 = Serial.parseInt();
//    //byte Check1 = Serial.parseInt();
//    //byte Check2 = Serial.parseInt();
//    //byte EndBit = Serial.parseInt();
//    //byte Command_line[10] = { StartBit, Ver, Len, CMD2, Feedback,
//    //  Param1, Param2, Check1, Check2, EndBit};
//    ////Send the command line to the module
//    //for (byte k=0; k<10; k++)
//    //{
//    //  mySerial.write( Command_line[k]);
//    //}
//  }
//
//    if (mySerial.available()>=10)
//  {
//    // There is at least 1 returned message (10 bytes each)
//
//    // Read the returned code
//    byte Returned[10];
//    for (byte k=0; k<10; k++)
//      Returned[k] = mySerial.read();
//    // Wtite the returned code at the screen
//    Serial.print("Returned: 0x"); if (Returned[3] < 16) Serial.print("0"); Serial.print(Returned[3],HEX);
//    Serial.print("("); Serial.print(Returned[3], DEC);
//    Serial.print("); Parameter: 0x"); if (Returned[5] < 16) Serial.print("0"); Serial.print(Returned[5],HEX);
//    Serial.print("("); Serial.print(Returned[5], DEC);
//    Serial.print("), 0x"); if (Returned[6] < 16) Serial.print("0"); Serial.print(Returned[6],HEX);
//    Serial.print("("); Serial.print(Returned[6], DEC); Serial.println(")");
//  }
//
//}
//
//void execute_CMD(byte CMD, byte Par1, byte Par2)
//  // Excecute the command and parameters
//{
//  // Calculate the checksum (2 bytes)
//  word checksum = -(Version_Byte + Command_Length + CMD + Acknowledge + Par1 + Par2);
//  // Build the command line
//  byte Command_line[10] = { Start_Byte, Version_Byte, Command_Length, CMD, Acknowledge,
//      Par1, Par2, highByte(checksum), lowByte(checksum), End_Byte};
//  //Send the command line to the module
//  for (byte k=0; k<10; k++)
//  {
//    mySerial.write( Command_line[k]);
//  }
//}
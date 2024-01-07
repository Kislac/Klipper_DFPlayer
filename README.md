# Klipper_DFPlayer
 Project to make a talikng printer with a speaker, rpi, microcontroller and klipper.
 ### Features:
 Volume control from (0-10 levels)
 
 There are 4 Music: (Hungarian and enlgish language as well)
- Start printing
- End of printing
- Filament replacement indication for M600 command
- Error indication for runout sensor
  

## Briefing:
The main idea is control 2 PWM outputs from RPI/Klipper/Fuidpi. Where one signal is the sound volume settings, the other is which audio file to play.
The PWM signal has been converted with a little electronics to analog voltage to make it possible to read by analog read by the Bluepill.
Bluepill is controlling the DFplayer via Serial communication.
I using SoftwareSerial (virtual serialm so any pins can be used.)
In this way, you can set the volume + play an audio file from GcodeMacro.

## HW reqs:
- Bluepill (STM32F103C8T6) Or any other micro, which support serial communicaltion (esp, arduino, etc...)
- Raspberry (Any version) - (Currently i am tested with Rpi 4b)
- 3 pcs 1kOhm resistor
- 2 pcs 200 Ohm resistor
- 2 pcs 100 uF condensator
- DFPlayer mini (Original or china clone is also ok)
- Speaker (max 3W) - (With bigger speaker an amplifier will be needed as well)

## Wiring:
![2024-01-07_18h53_00](https://github.com/Kislac/Klipper_DFPlayer/assets/34631881/3f55588a-4fd5-4846-93f1-a2d85a2430f6)
## Product:
![2024-01-02_15h49_26](https://github.com/Kislac/Klipper_DFPlayer/assets/34631881/312802f7-c534-4f50-a469-4c539690ccc7)

## How to:
### DFplayer
Copy the "01", "02" folders and audio files from Music folder to an SD card and insert into the DFplayer
- "01" Folder are included with Hungarian Audio files
- "01" Folder are included with English Audio files


### Klipper_Bluepill code
Use this code to upload to the bluepill or any other micro, which support serial communicaltion (esp, arduino, etc...)
You may modify only 2 things.
1. SerialPins
I have using SoftwareSerial (virtual serial). So you can wire the RX/TX wire to any GPIO pin)
row 31:
```
SoftwareSerial mySerial(PB1, PB0);    // RX pin = 10, TX pin = 11    //13/15
```
2. Hungarian/English audio files
From row 153-171 are playing the audio files.
```
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
```
Where following section is the playing the audio file
```
execute_CMD(0x0F, 1, 3);
```
- 1st parameter (0x0F) --> Playing command
- 2nd parameter (1)    --> Playing audio from "02" Folder
- 3th parameter (3)    --> Playing "003.mp3" audio

If you would like to play English audio files instead of Hungarian, than modify the second parameter to 2.
```
row 158: execute_CMD(0x0F, 2, 1);
row 162: execute_CMD(0x0F, 2, 2);
row 166: execute_CMD(0x0F, 2, 3);
row 170: execute_CMD(0x0F, 2, 4);
```

### Klipper_DFPlayer_ESP8226
I have builded a test bench with Bluepill and an ESP8266, where i used the ESP to simulate the RPI. Mostly i tested here the communication between Bluepill and DFplayer.
You can check this code as well, but its is not necessary to use it

#### Wiring for Test Setup 
![2024-01-07_21h17_53](https://github.com/Kislac/Klipper_DFPlayer/assets/34631881/5c4342fd-1eb5-4ce2-80aa-536579c32b3e)

### KlipperPrinterConfig

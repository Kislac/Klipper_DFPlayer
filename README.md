# Klipper_DFPlayer
 Project to make a talikng printer with a speaker, rpi, microcontroller and klipper.
 ###Features:
 Volume control from (0-10 levels)
 There are 4 Music: (Hungarian and enlgish language as well)
- Start printing
- End of printing
- Filament replacement indication for M600 command
- Error indication for runout sensor
  

##Briefing:
The main idea is control 2 PWM outputs from RPI/Klipper/Fuidpi. Where one signal is the sound volume settings, the other is which audio file to play.
The PWM signal has been converted with a little electronics to analog voltage to make it possible to read by analog read by the Bluepill.
Bluepill is controlling the DFplayer via Serial communication.
I using SoftwareSerial (virtual serialm so any pins can be used.)
In this way, you can set the volume + play an audio file from GcodeMacro.

##HW reqs:
- Bluepill (STM32F103C8T6) Or any other micro, which support serial communicaltion (esp, arduino, etc...)
- Raspberry (Any version) - (Currently i am tested with Rpi 4b)
- 3 pcs 1kOhm resistor
- 2 pcs 200 Ohm resistor
- 2 pcs 100 uF condensator
- DFPlayer mini (Original or china clone is also ok)
- Speaker (max 3W) - (With bigger speaker an amplifier will be needed as well)

##Wiring:
![2024-01-07_18h53_00](https://github.com/Kislac/Klipper_DFPlayer/assets/34631881/3f55588a-4fd5-4846-93f1-a2d85a2430f6)
##Product:
![2024-01-02_15h49_26](https://github.com/Kislac/Klipper_DFPlayer/assets/34631881/312802f7-c534-4f50-a469-4c539690ccc7)


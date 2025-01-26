# DrumRoller-AutomaticDiceTower
This is a project made during TAMUhack 2025 it is a dice rolling tower which will automatically roll a requested number of dice. 
Various modes for that are included which provide futher automation

The source code requires the Arduino IDE with the VarSpeedServo library installed to compile and upload to the board.
The board used for this project is the Atmega 2560, with a shield board used for conecting to the board. However the shield is not strictly necessary.
The servos used are the MicroServo 99 SG90. These are small, however they can max out the amperage supply on the board. In such an event the board tends to restart and mess with the servos.
It is highly recommended that a well charhed battery or higher voltage power supply is used to prevent this issue.

The keypad used is a simple 3x4 button keypad.
A continous servo is used to spin the drum when dispensing .


A demo and promotional video for this project is availible at https://www.youtube.com/@BrettDwyerTAMU

## Operation Instructions ##
With a fully assembled project, connect the power.

To dispense 1-6 dice press the corresponding key on the keypad.
    The correct number of dice will fall into the tray, then the drum will stop.
    
To return the dice to the cup, you have two options.
    Pressing 0 will automatically raise the tray and then lower it shortly after.
    Pressing * will raise the tray, and pressing # will lower it.
        These can be useful as manual overrides.
        
** Special Modes **

Pressing 7 will activate "Demo" Mode.
    You will need to press one of the number buttons to select the number of dice to roll.
    Once that is done, the dice will be dispensed then immediately returned to the cup.
    
Pressing 8 will activate "Timed Return" Mode.
    This acts like Demo Mode, but with a 7.5 second delay before returning the dice.
    This can be used to roll many dice quickly automatically.
    
Pressing 9 will activate "Empty to Table" Mode.
    This will raise the tray then spin the drum.
    This can be used to roll lots of dice without filling up the tray.
    
To exit any of these special modes press any button while the drum is spinning.
  



    

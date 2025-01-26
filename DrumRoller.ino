#include <VarSpeedServo.h>

// Extra modes,
// Demo mode, returns dice after all fall
// Timed Return, rolls some dice, waits then returns
// Lift up and return
// Continuous feed, Empty onto table
// Manual Up and Down

// Set up servo control classes
VarSpeedServo myservo;
VarSpeedServo Rposer;
VarSpeedServo Lposer;

// Setup for keypad reading
#include <Keypad.h>
const byte ROWS = 4; 
const byte COLS = 3; 
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {35, 33, 31, 29}; 
byte colPins[COLS] = {27, 25, 23}; 
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

// Constants for pins
const int checkPin = 37;
// Constants for servo speeds and positions
const int liftspeed = 100, drumSpeedGo = 120, drumSpeedStop = 90; 
const int Rdown = 25, Ldown=132, Rup=115, Lup = 35;
// Variables
int numtoroll = 0;
char customKey ='0';

void setup() {
  // Set up 
  pinMode(checkPin, INPUT); 

  // The servo control wire is connected to Arduino D2 pin.
  myservo.attach(36);
  Rposer.attach(42);
  Lposer.attach(48);
  // Servo is stationary.
  myservo.write(90);
  Rposer.write(Rdown,10,false);
  Lposer.write(Ldown,10, false);
}

void returnToDrum(){
  Rposer.write(Rup,liftspeed,false);
  Lposer.write(Lup,liftspeed,false);
  Rposer.wait();
  Lposer.wait();
  delay(1000);
  Rposer.write(Rdown,liftspeed,false);
  Lposer.write(Ldown,liftspeed,false);
  return;
};

void continuousRoll(){
  // Lift tray
  Rposer.write(Rup,liftspeed,false);
  Lposer.write(Lup,liftspeed,false);
  delay(500); // Wait for key to be released
  myservo.write(drumSpeedGo); // start drum
  while(customKeypad.getKey() == 0){ // While No button is pressed on the keypad
  }
  // Key pressed, stop all actions immediatly
  myservo.write(drumSpeedStop); // stop drum
  // Drop Tray
  Rposer.write(Rdown,liftspeed,false);
  Lposer.write(Ldown,liftspeed,false);
  return;
};

void demoMode(char numindrum, int waittime){
  delay(500); // Wait for key to be released
  int numberRolled=0;
  myservo.write(drumSpeedGo); // start drum
  while(customKeypad.getKey() == 0){ // While No button is pressed on the keypad
    if (digitalRead(checkPin)==0){ // If the sensor shows logical LOW, a die has passed it
      numberRolled++; // Count how many dice have been dispensed
      delay(250); // Wait to be sure that the die is gone
    }
    // Wait, then Return the dice to the drum when all out
    if(numberRolled == numindrum - '0'){
      numberRolled = 0;
      myservo.write(drumSpeedStop); // stop drum
      delay(waittime);
      returnToDrum();
      myservo.write(drumSpeedGo); // start drum
    }
  }
  // Key pressed, stop all actions immediatly
  myservo.write(drumSpeedStop); // stop drum
  return;
};

void loop() {
  // Read keypad input
  customKey = customKeypad.getKey();

  if ((customKey != '*' && customKey != '#' && customKey != '0' && customKey != '7' && customKey != '8' && customKey != '9') && numtoroll <= 0){
    numtoroll = customKey - '0';
  }else if(customKey == '*' && numtoroll <= 0){ // Lift Up
    Rposer.write(Rup,liftspeed,false);
    Lposer.write(Lup,liftspeed,false);
  }else if(customKey == '#' && numtoroll <= 0){ // Put Down
    Rposer.write(Rdown,liftspeed,false);
    Lposer.write(Ldown,liftspeed,false);
  }else if(customKey == '0' && numtoroll <= 0){  // Automatic return
    returnToDrum();
  }else if(customKey == '7'){ // Demo Mode, Auto return and replacement of dice after all are dispensed
    // Get the number of dice to roll in this mode
    do{
      customKey = customKeypad.getKey();
    }while(!(customKey == '1' || customKey == '2' || customKey == '3' || customKey == '4' || customKey == '5' || customKey == '6' ));
    demoMode(customKey, 0);
  }else if(customKey == '8'){ // Speed Catan Mode, Same as 
    // Get the number of dice to roll in this mode
    do{
      customKey = customKeypad.getKey();
    }while(!(customKey == '1' || customKey == '2' || customKey == '3' || customKey == '4' || customKey == '5' || customKey == '6' ));
    demoMode(customKey, 75000); // Same code as Demomode, but with wait time
  }else if(customKey == '9'){ // Continuous Feed, Lift tray to top position, then start rolling.
    continuousRoll();
  }

  customKey = 0;

  if (numtoroll > 0){
    // Start release action
    myservo.write(120); // Spin Drum
  }else{
    // Stop drum
    myservo.write(90);
  }

  if (digitalRead(checkPin)==0){ // If the sensor shows logical LOW
    numtoroll--;
    delay(250);
  }
  
}
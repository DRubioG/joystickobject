#include <PS2X_lib.h>  //for v1.6

#include "Joystick.h"

#define PS2_DAT        13  //14    
#define PS2_CMD        11  //15
#define PS2_SEL        10  //16
#define PS2_CLK        12  //17

#define pressures   false
#define rumble      false

PS2X ps2x; // create PS2 Controller Class
Joystick j;
int error = 0;
byte type = 0;
byte vibrate = 0;

void setup(){
  Serial.begin(57600);
  delay(300);
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  if(error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  type = ps2x.readType(); 
  switch(type) {
    case 0:
      Serial.print("Unknown Controller type found ");
      break;
    case 1:
      Serial.print("DualShock Controller found ");
      break;
   }
}

void loop() {
  if(error == 1) //skip loop if no controller found
    return; 
  
  else { 
    ps2x.read_gamepad(false, vibrate); 
    if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) { 
      j.leer(255, ps2x.Analog(PSS_LY), ps2x.Analog(PSS_LX), 50);
    }     
  }
  delay(50);  
}

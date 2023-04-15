#include <Arduino.h>
#include "Joystick.h"
/*
  gnd ---> gnd
  +5v ---> 3v(recommend)
  vrx ---> pin support adc
  vry ---> pin support adc
  sw  ---> pin support digital
*/
int x = 4;
int y = 2;
int sw = 32;
Joystick joy(x, y, sw);

void setup()
{
  Serial.begin(115200);
  joy.begin();
  joy.onEvent([](){Serial.println("Left");}, 
  [](){Serial.println("Right");}, 
  [](){Serial.println("Up");}, 
  [](){Serial.println("Down");}
  );
//   joy.onEvent_Left([](){
//     Serial.println("Left");
//   });
//     joy.onEvent_Right([](){
//     Serial.println("Right");
//   });
//     joy.onEvent_Up([](){
//     Serial.println("Up");
//   });
//     joy.onEvent_Down([](){
//     Serial.println("Down");
//   });
  joy.onEvent_UpLeft([](){Serial.println("UpLeft");});
  joy.onEvent_UpRight([](){Serial.println("UpRight");});
  joy.onEvent_DownLeft([](){Serial.println("DownLeft");});
  joy.onEvent_DonwRight([](){Serial.println("DownRight");});
  joy.onEvent_SW([](boolean sw)
  {Serial.println("SW is: "+String(sw));
  });
}

void loop()
{
  joy.handle();
  delay(50);
}


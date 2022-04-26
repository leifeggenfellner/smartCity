#include "Display.h"

static Zumo32U4LCD display;


void displayMaxSpeed(int maximum_speed){
    display.clear();
    display.gotoXY(0,0);
    display.print(maximum_speed);
}

/*
void sendToDisplay(int display_mode){
  switch (display_mode)
    {
    case 0:
        display.clear();
        display.gotoXY(0,0);
        display.print("hei");
        break;
    
    default:
        break;
    }
}
*/
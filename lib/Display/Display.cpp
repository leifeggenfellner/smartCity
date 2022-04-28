#include "Display.h"

static Zumo32U4LCD display;



void displayTopScreen(int top_parameter){
    display.clear();
    display.gotoXY(0,0);
    display.print(top_parameter);
}

void displayBottomScreen(float bottom_parameter){
    display.clear();
    display.gotoXY(0,0);
    display.print(bottom_parameter);

}


void displayRotation(uint8_t display_mode){
    switch (display_mode)
    {
    case 0:
        /* code */
        break;
    
    default:
        break;
    }

}

/*
void displayCurrentSpeed(int vehicle_speed){
    display.clear();
    display.gotoXY(0,0);
    display.print(vehicle_speed);

}

void displayMaxSpeed(int maximum_speed){
    display.clear();
    display.gotoXY(0,0);
    display.print(maximum_speed);
}
*/
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
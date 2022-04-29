#include "Display.h"
#include <Zumo32U4LCD.h>

Display::Display(int maximum_speed, int display_mode, Zumo32U4LCD display)
{
    this->maximum_speed = maximum_speed;
    this->display_mode = display_mode;
    this->display = display;
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
void Display::displayMaxSpeed()
{
    display.clear();
    display.gotoXY(0, 0);
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
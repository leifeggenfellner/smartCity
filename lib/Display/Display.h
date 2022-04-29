#pragma once

class Display
{

private:
    int maximum_speed;
    Zumo32U4LCD display;

public:
    int display_mode;

//void displayMaxSpeed(int maximum_speed);
//void sendToDisplay(int display_mode);

void displayRotation(uint8_t display_mode);
    Display(int maximum_speed, int display_mode, Zumo32U4LCD display);
    void displayMaxSpeed();
};

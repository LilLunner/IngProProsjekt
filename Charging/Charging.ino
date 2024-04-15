#include <IRremote.h>
#include <Wire.h>
#include <Zumo32U4.h>
#include <EEPROM.h>
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4ButtonC buttonC;
Zumo32U4LineSensors lineSensors;
Zumo32U4OLED display;
Zumo32U4Buzzer buzzer;
Zumo32U4Encoders encoder;

int battery = 20;
int amount = 40;
int max = 80;

float distMeasure()
{
static long int rotLeft = 0;
static long int rotRight = 0;
int currRotLeft = encoder.getCountsAndResetLeft();              
int currRotRight = encoder.getCountsAndResetRight();
rotLeft += abs(currRotLeft);
rotRight += abs(currRotRight);
float leftDist = ((rotLeft + abs(currRotLeft))*3.1415*0.039)/910;
float rightDist = ((rotRight + abs(currRotRight))*3.1415*0.039)/910;
float distTot = (leftDist + rightDist)/2;
return distTot;
}

int batteryStatus(battery) {
    float dist = distMeasure();
    battery = battery - 4*dist;
    return battery;
}

int charge(amount, battery) {
    battery = battery + amount;
    if(battery>max)
        battery = max;
    return battery;
}

void setup() {

}

void loop() {

}
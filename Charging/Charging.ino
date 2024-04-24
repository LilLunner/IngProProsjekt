#include <IRremote.h>
#include <Wire.h>
#include <Zumo32U4.h>
#include <EEPROM.h>
#include <WiFi.h>
 
const char* ssid = "NTNU-IOT";
const char* password = "";
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4ButtonC buttonC;
Zumo32U4LineSensors lineSensors;
Zumo32U4OLED display;
Zumo32U4Buzzer buzzer;
Zumo32U4Encoders encoder;


int power;
int amount = 40;
int max = 80;
float totalDistance;

float distMeasure()
{
int currRotLeft = encoder.getCountsAndResetLeft();              
int currRotRight = encoder.getCountsAndResetRight();
float leftDist = ((abs(currRotLeft))*3.1415*0.039)/910;
float rightDist = ((abs(currRotRight))*3.1415*0.039)/910;
float distTot = totalDistance + 10*(leftDist + rightDist)/2;
EEPROM.write(1, distTot);
return distTot;
}

int batteryDrain(int battery) {
    battery = max - 2*totalDistance;
    if (battery < 0) {
        battery = 0;
    }
    EEPROM.write(0, battery);
    return battery;
}

/*int price() {
    if(totalDistance=< 20) {
        price = 63;
    }
    else {
        price = 
    }
}*/

int charge(int battery) {
    battery = battery + amount;
    if(battery>max) {
        battery = max;
    }
    return battery;
}

void showBattery() {
    int disShow = 10*totalDistance;
    display.gotoXY(0, 0); 
    display.print(F("Power: ")); 
    display.println(power); 
    display.gotoXY(0, 1); 
    display.print("Distance drove; "); 
    display.print(disShow); 
    display.print("km");
}

void setup() {
    Serial.begin(115200);
    display.setLayout21x8();
    /*Serial.println("Try Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password); // Connect to your wi-fi modem
 
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected successfully");
    Serial.print("Got IP: ");
    Serial.println(WiFi.localIP());  //Show ESP32-IP on serialmonitor
    delay(100);*/

    EEPROM.write(0, 80);
    EEPROM.write(1, 0);
    power = EEPROM.read(0);
    totalDistance = EEPROM.read(1);
}

void loop() {
    motors.setSpeeds(100,100);
    totalDistance = distMeasure();
    power = batteryDrain(power);
    showBattery();
}
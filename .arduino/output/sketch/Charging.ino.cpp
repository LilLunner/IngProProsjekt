#include <Arduino.h>
#line 1 "C:\\Users\\Magnus\\Documents\\IngProProsjekt\\Charging\\Charging.ino"
#include <IRremote.h>
#include <Wire.h>
#include <Zumo32U4.h>
#include <EEPROM.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WebServer.h>
 
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

int battery = 80;
int amount = 40;
int max = 80;
int priceBase =

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

int batteryDrain(battery) {
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
    Serial.begin(115200);
  
    Serial.println("Try Connecting to ");
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
    delay(100);
}

void loop() {

}

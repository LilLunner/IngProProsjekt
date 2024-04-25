# 1 "C:\\Users\\Magnus\\Documents\\IngProProsjekt\\Charging\\Charging.ino"
# 2 "C:\\Users\\Magnus\\Documents\\IngProProsjekt\\Charging\\Charging.ino" 2
# 3 "C:\\Users\\Magnus\\Documents\\IngProProsjekt\\Charging\\Charging.ino" 2
# 4 "C:\\Users\\Magnus\\Documents\\IngProProsjekt\\Charging\\Charging.ino" 2
# 5 "C:\\Users\\Magnus\\Documents\\IngProProsjekt\\Charging\\Charging.ino" 2
# 6 "C:\\Users\\Magnus\\Documents\\IngProProsjekt\\Charging\\Charging.ino" 2

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


int power, distMultiplier;
int amount = 40;
int max = 80;
float partDisGlobal, totalDistance;

float distMeasure()
{
int currRotLeft = encoder.getCountsAndResetLeft();
int currRotRight = encoder.getCountsAndResetRight();
float leftDist = ((((currRotLeft)>0?(currRotLeft):-(currRotLeft)))*3.1415*0.039)/910;
float rightDist = ((((currRotRight)>0?(currRotRight):-(currRotRight)))*3.1415*0.039)/910;
if (partDisGlobal>=255) {
    distMultiplier += 1;
    partDisGlobal -= 255;
}
float distPart = partDisGlobal + (10*(leftDist + rightDist)/2);
EEPROM.write(1, partDisGlobal);
EEPROM.write(2, distMultiplier);
Serial.println(distPart);
return distPart;
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
    display.gotoXY(0, 0);
    display.print((reinterpret_cast<const __FlashStringHelper *>(
# 69 "C:\\Users\\Magnus\\Documents\\IngProProsjekt\\Charging\\Charging.ino" 3
                 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 69 "C:\\Users\\Magnus\\Documents\\IngProProsjekt\\Charging\\Charging.ino"
                 "Power: "
# 69 "C:\\Users\\Magnus\\Documents\\IngProProsjekt\\Charging\\Charging.ino" 3
                 ); &__c[0];}))
# 69 "C:\\Users\\Magnus\\Documents\\IngProProsjekt\\Charging\\Charging.ino"
                 )));
    display.println(power);
    display.gotoXY(0, 1);
    display.print("Distance drove; ");
    display.print(10*totalDistance);
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
    EEPROM.write(2,0);
    power = EEPROM.read(0);
    partDisGlobal = EEPROM.read(1);
    distMultiplier = EEPROM.read(2);
}

void loop() {
    motors.setSpeeds(100,100);
    partDisGlobal = distMeasure();
    totalDistance = partDisGlobal+(distMultiplier*255);
    power = batteryDrain(power);
    showBattery();
}

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

int power;
int amount = 40;
int max = 80;

float distMeasure()
{
static long int rotLeft = 0;
static long int rotRight = 0;
int currRotLeft = encoder.getCountsAndResetLeft();
int currRotRight = encoder.getCountsAndResetRight();
rotLeft += ((currRotLeft)>0?(currRotLeft):-(currRotLeft));
rotRight += ((currRotRight)>0?(currRotRight):-(currRotRight));
float leftDist = ((rotLeft + ((currRotLeft)>0?(currRotLeft):-(currRotLeft)))*3.1415*0.039)/910;
float rightDist = ((rotRight + ((currRotRight)>0?(currRotRight):-(currRotRight)))*3.1415*0.039)/910;
float distTot = (leftDist + rightDist)/2;
return distTot;
}

int batteryDrain(int battery) {
    float dist = distMeasure();
    battery = battery - 4*dist;
    EEPROM.write(0, battery);
    return battery;
}

int charge(amount; int battery) {
    battery = battery + amount;
    if(battery>max) {
        battery = max;
    }
    return battery;
}

void showBattery() {
    display.gotoXY(0, 0);
    display.print((reinterpret_cast<const __FlashStringHelper *>(
# 53 "C:\\Users\\Magnus\\Documents\\IngProProsjekt\\Charging\\Charging.ino" 3
                 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 53 "C:\\Users\\Magnus\\Documents\\IngProProsjekt\\Charging\\Charging.ino"
                 "Power: "
# 53 "C:\\Users\\Magnus\\Documents\\IngProProsjekt\\Charging\\Charging.ino" 3
                 ); &__c[0];}))
# 53 "C:\\Users\\Magnus\\Documents\\IngProProsjekt\\Charging\\Charging.ino"
                 )));
    display.println(power);
    display.gotoXY(0, 1);
    display.print("Distance left; ");
    display.print(power/0.2);
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
    Serial.println(WiFi.localIP()); //Show ESP32-IP on serialmonitor
    delay(100);

    EEPROM.write(0, 80);
    power = EEPROM.read(0);
}

void loop() {
    motors.setSpeeds(100,100);
    power = batteryDrain(power);
    showBattery();
}

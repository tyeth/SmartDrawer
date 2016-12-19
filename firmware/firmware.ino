/*
  IoT Smart Drawer
  version 1.0
  copyright 2016 (c) Tyler Spadgenske
*/

#define LEDPIN 7
#define BATTERYSENSOR 0
#define STAMPSSENSORA 4
#define STAMPSSENSORB 2

//initialize variables
int stampSensorCount = 0;
int stampCount = 100;

void setup() {
    // initialize the LED pin as an output:
    pinMode(LEDPIN, OUTPUT);
    // initialize the sensors
    pinMode(BATTERYSENSOR, INPUT);
    digitalWrite(BATTERYSENSOR, HIGH);
    pinMode(STAMPSSENSORA, INPUT);
    digitalWrite(STAMPSSENSORA, HIGH);
    pinMode(STAMPSSENSORB, INPUT);
    digitalWrite(STAMPSSENSORB, HIGH);

    Serial.begin();
}

void loop(){
    //poll sensors
    //check batteries
    if (digitalRead(BATTERYSENSOR) == HIGH) {
        Serial.println("Low on batteries");
    }
    //check stamps
    if (digitalRead(STAMPSSENSORA) == 0 and digitalRead(STAMPSSENSORB) == 0) {
        delay(30);
        stampSensorCount += 1;
        if (stampSensorCount > 5) {
            stampSensorCount = 0;
            stampCount -= 1;
            Serial.println("Stamp used");
        }
    }
    //Check total stamp count
    if (stampCount <= 0) {
        Serial.println("Out of stamps");
    }
}

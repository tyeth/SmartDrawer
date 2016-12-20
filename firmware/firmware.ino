/*
  IoT Smart Drawer
  version 1.0
  copyright 2016 (c) Tyler Spadgenske
*/

#define LEDPIN 7
#define BATTERYSENSOR 0
#define STAMPSSENSORA 4
#define STAMPSSENSORB 2
#define POSTITSENSOR A0
#define PAPERCLIPSENSOR A1

//initialize variables
int stampSensorCount = 0;
int stampCount = 100;
int PAPERCLIP_THRESHOLD = 3400;
int POSTIT_THRESHOLD = 350;

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
    pinMode(POSTITSENSOR, INPUT);
    digitalWrite(POSTITSENSOR, HIGH);
    pinMode(PAPERCLIPSENSOR, INPUT);
    digitalWrite(PAPERCLIPSENSOR, HIGH);

    Serial.begin();
}

void loop(){
    //poll sensors
    //check batteries
    if (digitalRead(BATTERYSENSOR) == HIGH) {
        Serial.println("Out of batteries");
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
        Serial.println("Low on stamps");
    }
    //check paperclips
    if (analogRead(PAPERCLIPSENSOR) < PAPERCLIP_THRESHOLD) {
        Serial.println("Low on paper clips");
    }
    //check postit! notes
    if (analogRead(POSTITSENSOR) > POSTIT_THRESHOLD) {
        Serial.println("Low on postit! notes");
    }

}

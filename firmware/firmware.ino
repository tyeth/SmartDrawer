/*
  IoT Smart Drawer
  version 1.0
  copyright (c) 2016 Tyler Spadgenske
*/

#include "HX711.h"

#define LEDPIN 7
#define BATTERYSENSOR 0
#define STAMPSSENSORA 4
#define STAMPSSENSORB 2
#define POSTITSENSOR A0
#define PAPERCLIPSENSOR A1
#define PAPERCLK A4
#define PAPERDAT A3

//initialize the hx711
#define calibration_factor -7050.0
HX711 scale(PAPERDAT, PAPERCLK);

//initialize variables
int stampSensorCount = 0;
int stampCount = 10;
int PAPERCLIP_THRESHOLD = 3400;
int POSTIT_THRESHOLD = 1000;
float SCALE_THRESHOLD = 10.0;

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

    //setup the load cell
    scale.set_scale(calibration_factor);
    scale.tare();

    Serial.begin();
}

void loop(){
    //poll sensors
    //check batteries
    if (digitalRead(BATTERYSENSOR) == HIGH) {
        Serial.println("Out of batteries");
        Particle.publish("Batteries");
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
        Particle.publish("Stamps");
    }
    //check paperclips
    if (analogRead(PAPERCLIPSENSOR) < PAPERCLIP_THRESHOLD) {
        Serial.println("Low on paper clips");
        Particle.publish("Paperclips");
    }
    //check postit! notes
    if (analogRead(POSTITSENSOR) > POSTIT_THRESHOLD) {
        Serial.println("Low on postit! notes");
        Particle.publish("PostIt");
    }
    //check paper
    if (scale.get_units() > SCALE_THRESHOLD) {
        Serial.println("Low on paper");
        Particle.publish("Paper");
    }
    delay(10000);
}

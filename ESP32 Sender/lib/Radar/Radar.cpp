#include "Arduino.h"
#include "Radar.h"
// #define RADAR_DEBUG

void Radar_Setup()
{
    pinMode(ULTRASONIC_TRIG_PIN, OUTPUT); // Sets the trigPin as an Output
    pinMode(ULTRASONIC_ECHO_PIN, INPUT);  // Sets the echoPin as an Input
}

void Radar_Loop()
{
    digitalWrite(ULTRASONIC_TRIG_PIN, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(ULTRASONIC_TRIG_PIN, HIGH);
    delay(500);
    digitalWrite(ULTRASONIC_TRIG_PIN, LOW);

    duration = pulseIn(ULTRASONIC_ECHO_PIN, HIGH);
    distanceCm = duration * ULTRASONIC_SOUND_SPEED / 2;

    #ifdef RADAR_DEBUG
    Serial.println(distanceCm);
    #endif
}

float Radar_GetDistance()
{
    digitalWrite(ULTRASONIC_TRIG_PIN, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(ULTRASONIC_TRIG_PIN, HIGH);
    delay(500);
    digitalWrite(ULTRASONIC_TRIG_PIN, LOW);

    duration = pulseIn(ULTRASONIC_ECHO_PIN, HIGH);
    return duration * (ULTRASONIC_SOUND_SPEED / 2);
}
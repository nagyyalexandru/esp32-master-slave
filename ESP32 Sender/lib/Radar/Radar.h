#ifndef Radar_h
#define Radar_h

#define ULTRASONIC_TRIG_PIN 21
#define ULTRASONIC_ECHO_PIN 15
#define ULTRASONIC_SOUND_SPEED 0.034

static long duration;
static float distanceCm;

void Radar_Setup();

void Radar_Loop();

float Radar_GetDistance();

#endif
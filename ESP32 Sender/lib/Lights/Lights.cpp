#include "Arduino.h"
#include "Lights.h"
// #define LIGHTS_DEBUG

void Lights_Setup()
{
  pinMode(LOW_BEAM_BUTTON_PIN, INPUT_PULLUP);
  pinMode(HIGH_BEAM_BUTTON_PIN, INPUT_PULLUP);
  pinMode(LOW_BEAM_LED_PIN, OUTPUT);
  pinMode(HIGH_BEAM_LED_PIN, OUTPUT);

  currentButtonState[LOW_BEAM] = digitalRead(LOW_BEAM_BUTTON_PIN);
  currentButtonState[HIGH_BEAM] = digitalRead(HIGH_BEAM_BUTTON_PIN);
}

void Lights_Loop()
{
  lastButtonState[LOW_BEAM] = currentButtonState[LOW_BEAM];   // save the last state
  currentButtonState[LOW_BEAM] = digitalRead(LOW_BEAM_BUTTON_PIN);   // read new state
  lastButtonState[HIGH_BEAM] = currentButtonState[HIGH_BEAM]; // save the last state
  currentButtonState[HIGH_BEAM] = digitalRead(HIGH_BEAM_BUTTON_PIN); // read new state

  if (lastButtonState[LOW_BEAM] == HIGH && currentButtonState[LOW_BEAM] == LOW)
  {
    // toggle state of low beam
    u8LowBeamState = !u8LowBeamState;
  }

  if (lastButtonState[HIGH_BEAM] == HIGH && currentButtonState[HIGH_BEAM] == LOW)
  {
    // toggle state of high beam
    u8HighBeamState = !u8HighBeamState;
  }
#ifdef LIGHTS_DEBUG
  if (u8LowBeamState)
  {
    Serial.println("Low Beam ON");
  }
  else if (!u8LowBeamState)
  {
    Serial.println("Low Beam OFF");
  }

  if (u8HighBeamState)
  {
    Serial.println("High Beam ON");
  }
  else if (!u8HighBeamState)
  {
    Serial.println("High Beam OFF");
  }
#endif
}

uint8_t Lights_GetLowBeamState()
{
  lastButtonState[LOW_BEAM] = currentButtonState[LOW_BEAM];   // save the last state
  currentButtonState[LOW_BEAM] = digitalRead(LOW_BEAM_BUTTON_PIN);   // read new state

  if (lastButtonState[LOW_BEAM] == HIGH && currentButtonState[LOW_BEAM] == LOW)
  {
    // toggle state of low beam
    u8LowBeamState = !u8LowBeamState;
    digitalWrite(LOW_BEAM_LED_PIN, u8LowBeamState);
  }
  return u8LowBeamState;
}

uint8_t Lights_GetHighBeamState()
{
  lastButtonState[HIGH_BEAM] = currentButtonState[HIGH_BEAM];   // save the last state
  currentButtonState[HIGH_BEAM] = digitalRead(HIGH_BEAM_BUTTON_PIN);   // read new state

  if (lastButtonState[HIGH_BEAM] == HIGH && currentButtonState[HIGH_BEAM] == LOW)
  {
    // toggle state of low beam
    u8HighBeamState = !u8HighBeamState;
    digitalWrite(HIGH_BEAM_LED_PIN, u8HighBeamState);
  }
  return u8HighBeamState;
}
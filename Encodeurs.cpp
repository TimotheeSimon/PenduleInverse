#include "Encodeurs.h"

void setupEncodeurs() {
  pinMode(encodeurA1, INPUT_PULLUP);
  pinMode(encodeurB1, INPUT_PULLUP);
  pinMode(encodeurA2, INPUT_PULLUP);
  pinMode(encodeurB2, INPUT_PULLUP);
  // Setup interruption encodeurs
  attachInterrupt(digitalPinToInterrupt(encodeurA1), isrEncodeur1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encodeurA2), isrEncodeur2, CHANGE);
}

void updateMotorSpeed(double motorSpeed[]) {

  previousAngleA = AngleA;
  previousAngleB = AngleB;
  
  AngleA = (float)cptA*360/CPR * alpha + previousAngleA * (1 - alpha);
  AngleB = (float)cptB*360/CPR * alpha + previousAngleB * (1 - alpha);

  motorSpeed[0] = (AngleA - previousAngleA) / (CONTROL_PERIODE_MS * 1e-3);
  motorSpeed[1] = (AngleB - previousAngleB) / (CONTROL_PERIODE_MS * 1e-3);
}



void isrEncodeur1() {
  if (bool(PINA & 0B000000001) == bool(PIND & 0B00001000)) { // if interrupt on CHANGE (Multiplier dans ce cas CPR par 2)
  // if ((PINA & 0B000000001) == 1) { // if interrupt on RISING
    cptA++;
  }
  else {
    cptA--;
  }
}

void isrEncodeur2() {
  if ( bool(PINA & 0B00000010) == bool(PIND & 0B000000100)) { // if interrupt on CHANGE (Multiplier dans ce cas CPR par 2)
  // if ((PINA & 0B00000010) == 2) { // if interrupt on RISING
    cptB++;
  }
  else {
    cptB--;
  }
}

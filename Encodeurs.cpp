#include "Encodeurs.h"

void setupEncodeurs() {
  pinMode(encodeurA1, INPUT_PULLUP);
  pinMode(encodeurB1, INPUT_PULLUP);
  pinMode(encodeurA2, INPUT_PULLUP);
  pinMode(encodeurB2, INPUT_PULLUP);
  // Setup interruption encodeurs
  attachInterrupt(digitalPinToInterrupt(encodeurA1), isrEncodeur1, RISING);
  attachInterrupt(digitalPinToInterrupt(encodeurA2), isrEncodeur2, RISING);
  setupTimer4(); // Pour calcul de la vitesse de rotation des moteurs
}

void updateMotorSpeed(double motorSpeed[]) {
  if (10 < memClockA and memClockA < clockThreshold) {
    motorSpeedA = dirA * 2 * PI * clockFrequency / (memClockA * 224.4);
  }
  else {
    motorSpeedA = 0;
  }
  if (10 < memClockB and memClockB < clockThreshold) {
    motorSpeedB = dirB * 2 * PI * clockFrequency / (memClockB * 224.4);
  }
  else {
    motorSpeedB = 0;
  }
  motorSpeed[0] = motorSpeedA;
  motorSpeed[1] = motorSpeedB;
}



void isrEncodeur1() {
  // if (bool(PINA & 0B000000001) == bool(PIND & 0B00001000)) { // if interrupt on CHANGE
  if ((PINA & 0B000000001) == 1) { // if interrupt on RISING
    dirA = 1;
  }
  else {
    dirA = -1;
  }
  memClockA = clockA;
  clockA = 0;
}

void isrEncodeur2() {
  // if ( bool(PINA & 0B00000010) == bool(PIND & 0B000001000)) { // if interrupt on CHANGE
  if ((PINA & 0B00000010) == 2) { // if interrupt on RISING
    dirB = 1;
  }
  else {
    dirB = -1;
  }
  memClockB = clockB;
  clockB = 0;
}



void setupTimer4() {
  cli(); // disable global interrupts
  TCCR4A = 0; // set entire TCCR2A register to 0
  TCCR4B = 0;
  TCNT4 = 0; // Définit le point de départ du comptage
  OCR4A = 100; // Définit la valeur seuil
  TCCR4B |= (1 << CS40);
  // TCCR4B |= (1 << CS41);
  TIMSK4 = (1 << OCIE4A); // enable timer compare interrupt
  sei(); // allow interrupts
}


ISR(TIMER4_COMPA_vect) {
  TCNT4 = 0;
  clockA++;
  clockB++;
}

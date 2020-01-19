#ifndef DEF_Encodeurs
#define DEF_Encodeurs

#include <Arduino.h>

// Paramètres
#ifndef CONTROL_PERIODE_MS
  #define CONTROL_PERIODE_MS (10)
#endif

#define encodeurA1 18 // Pin 18, INT3
#define encodeurB1 22

#define encodeurA2 19 // Pin 19, INT2
#define encodeurB2 23

const float CPR = 224.4 * 2;
const float alpha = 0.8;
static volatile int cptA = 0;
static volatile int cptB = 0;
static volatile float motorSpeedA = 0;
static volatile float motorSpeedB = 0;
static volatile float previousAngleA, AngleA = 0;
static volatile float previousAngleB, AngleB = 0;


// Fonctions

void setupEncodeurs();
void isrEncodeur1();
void isrEncodeur2();
void updateMotorSpeed(double motorSpeed[]);


#endif

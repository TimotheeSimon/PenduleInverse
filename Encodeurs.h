#ifndef DEF_Encodeurs
#define DEF_Encodeurs

#include <Arduino.h>

// Paramètres

#define encodeurA1 18 // Pin 18, INT3
#define encodeurB1 22

#define encodeurA2 19 // Pin 19, INT2
#define encodeurB2 23

#define clockFrequency  375000L
#define clockThreshold 10000

static volatile int8_t dirA = 1;
static volatile int8_t dirB = 1;
static volatile int clockA = 0;
static volatile int clockB = 0;
static volatile float motorSpeedA = 0;
static volatile float motorSpeedB = 0;
static volatile int memClockA = 0;
static volatile int memClockB = 0;


// Fonctions

void setupEncodeurs();
void isrEncodeur1();
void isrEncodeur2();
void setupTimer4();
void updateMotorSpeed(double motorSpeed[]);


#endif

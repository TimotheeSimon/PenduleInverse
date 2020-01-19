#ifndef DEF_Moteurs
#define DEF_Moteurs

#include <Arduino.h>
#include <movingAvg.h>

#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

// Paramètres

#define dirMoteurA 12
#define pwmMoteurA 3 // INT5 inutilisable
#define currentSensorA A0
// 0x04 divider -> 32
// Ox03 divider -> 58
// 0x02 divider -> 132 
// 0x01 divider -> 146
#define pwmThresholdA 32 

#define dirMoteurB 13
#define pwmMoteurB 11
#define currentSensorB A1
#define pwmThresholdB 32

#define sampleNumber 500

// current filter


static movingAvg currentAverageA(sampleNumber);
static movingAvg currentAverageB(sampleNumber);


// Fonctions

void setupMoteurs();
void runMoteurs(int pwmValueA, int pwmValueB);
void updateCurrent(double current[]);



#endif

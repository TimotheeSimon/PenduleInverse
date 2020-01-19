#include "Moteurs.h"
#include "Encodeurs.h"

void setupMoteurs() {
  pinMode(dirMoteurA, OUTPUT);
  pinMode(dirMoteurB, OUTPUT);
  pinMode(pwmMoteurA, OUTPUT);
  pinMode(pwmMoteurB, OUTPUT);
  pinMode(currentSensorA, INPUT);
  pinMode(currentSensorB, INPUT);

  // PWM divider
  // 0x01 => divise par 1
  // 0x02 => divise par 8 // 3.9 KHz
  // 0x03 => divise par 63 ... etc

  TCCR3B = TCCR3B & 0b11111000 | 0x04; // Prescaler timer 3, pin 2, 3 et 5
  TCCR1B = TCCR1B & 0b11111000 | 0x04; // Prescaler timer 1, pin 11, 12 et 13

  // Modifie la fréquence à laquelle le CAN peut faire ses acquisitions du courant
  // 0x01 => divise par 2
  // 0x02 => divise par 4
  // 0x03 => divise par 8 ... etc

  ADCSRA = ADCSRA & 0b11111000 | 0x01;
  currentAverageA.begin();
  currentAverageB.begin();
}

void runMoteurs(int pwmValueA, int pwmValueB) {
  // Moteur A
  if (pwmValueA + pwmThresholdA > 255) {
    pwmValueA = 255 - pwmThresholdA;
  }
  if (pwmValueA - pwmThresholdA < -255) {
    pwmValueA = -255 + pwmThresholdA;
  }

  if (pwmValueA > 0) {
    digitalWrite(dirMoteurA, LOW);
    sbi(TCCR3A, COM3C1);
    OCR3C = pwmValueA + pwmThresholdA;
  }
  else if (pwmValueA < 0){
    digitalWrite(dirMoteurA, HIGH);
    sbi(TCCR3A, COM3C1);
    OCR3C = - (pwmValueA - pwmThresholdA);
  }
  else {
    sbi(TCCR3A, COM3C1);
    OCR3C = 0;
  }

  // Moteur B
  if (pwmValueB + pwmThresholdB > 255) {
    pwmValueB = 255 - pwmThresholdB;
  }
  if (pwmValueB - pwmThresholdB < -255) {
    pwmValueB = -255 + pwmThresholdB;
  }
  if (pwmValueB > 0) {
    digitalWrite(dirMoteurB, LOW);
    sbi(TCCR1A, COM1A1);
    OCR1A = pwmValueB + pwmThresholdB;
  }
  else if (pwmValueB < 0) {
    digitalWrite(dirMoteurB, HIGH);
    sbi(TCCR1A, COM1A1);
    OCR1A = - (pwmValueB - pwmThresholdB);
  }
  else {
    sbi(TCCR1A, COM1A1);
    OCR1A = 0;
  }
}



void updateCurrent(double current[]) {
  // 5 V / 1024 ADC counts = 4.88 mV per count
  // 3.3 V = 2.0 A; 3.3 V / 4.88 mv per count = 676 counts
  // 2.0 A / 676 counts = 2.96 mA per count
  current[0] = dirA * analogRead(currentSensorA) * 0.001  * 2.96;
  current[1] = dirB * analogRead(currentSensorB) * 0.001 * 2.96;
}

#ifndef DEF_Angles
#define DEF_Angles

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

#define BNO055_SAMPLERATE_DELAY_MS (10)

static Adafruit_BNO055 BNO055 = Adafruit_BNO055();


void setupBNO();

void updateEuler(double euler[]);
void updateGyro(double gyro[]);

#endif

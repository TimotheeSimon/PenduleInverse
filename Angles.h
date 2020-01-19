#ifndef DEF_Angles
#define DEF_Angles

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

#define CONTROL_PERIODE_MS (10)

static Adafruit_BNO055 BNO055 = Adafruit_BNO055();

static const float beta = 0.8;

static double lastGyroA = 0;
static double lastGyroB = 0; 

void setupBNO();

void updateEuler(double euler[]);
void updateGyro(double gyro[]);

#endif

#include "Angles.h"

void setupBNO(){
  
  BNO055.begin();
  delay(500);
  int8_t temperature = BNO055.getTemp();
  BNO055.setExtCrystalUse(true);
}

void updateEuler(double euler[]){
  imu::Vector<3> eulerVector = BNO055.getVector(Adafruit_BNO055::VECTOR_EULER);
  euler[0] = eulerVector(1);
  euler[1] = eulerVector(2);
}

void updateGyro(double gyro[]){

  lastGyroA = gyro[0];
  lastGyroB = gyro[1];
  
  imu::Vector<3> gyroVector = BNO055.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
  
  gyro[0] = - gyroVector(1) * beta + lastGyroA * (1-beta);
  gyro[1] = - gyroVector(0) * beta + lastGyroB * (1-beta);

  
}

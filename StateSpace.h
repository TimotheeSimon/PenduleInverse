#ifndef DEF_StateSpace
#define DEF_StateSpace

#include <Arduino.h>
#include <StateSpaceControl.h>
// Paramètres

const int dimInput = 2;
const int dimState = 8;
const int dimOutput = 8;


const float Lp = 0.232; // centre de gravité bas
const float Lr = 0.238; // centre de gravité bas
const float Ip = 1.55 * 10e-3; // centre de gravité bas
const float Ir = 1.79 * 10e-4;
const float mp = 0.471;
const float mr = 0.102;
const float rho = 0.0294;

const float K = 0.12224;
const float R = 2.1204;
const float L = 0.020253;
const float f = 0.00010191;


const float g = 9.81;
const float ml = Lr * mr + Lp * mp;
const float I = mr * Lr * Lr + mp * Lp * Lp + Ip + Ir;


struct InvertedPendulumModel :  public Model<dimOutput, dimInput>
{
  InvertedPendulumModel()
  {
   
    A << 0, 1, 0, 0, 0, 0, 0, 0,
        ml*g/(I-Ir), 0, f/(I-Ir), -K/(rho*(I-Ir)), 0, 0, 0, 0,
        -ml*g/(I - Ir), 0, -f*I / (Ir * (I - Ir)), K*I/(rho*Ir*(I-Ir)), 0, 0, 0, 0,
        0, 0, -K*rho/L, -R/L, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 0, 0, ml*g/(I-Ir), 0, f/(I-Ir), -K/(rho*(I-Ir)),
        0, 0, 0, 0, -ml*g/(I-Ir), 0, -f*I/(Ir*(I-Ir)), K*I/(rho*Ir*(I-Ir)),
        0, 0, 0, 0, 0, 0, -K*rho/L, -R/L;
  
    B << 0, 0,
         0, 0,
         0, 0,
         1/L, 0,
         0, 0,
         0, 0,
         0, 0,
         0, 1/L;

    C << 1, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 0, 1;

    D = Zeros<dimOutput, dimInput>();

  }
};



// Affichage 

void stateDisplayer(Matrix<dimOutput> y);



#endif

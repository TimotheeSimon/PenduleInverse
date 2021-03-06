#include "StateSpace.h"
#include "Moteurs.h"
#include "Angles.h"
#include "Encodeurs.h"


int8_t state = 0;

static InvertedPendulumModel model;
//bool EnableEstimation=false, bool EnableIntegralControl=false, bool EnableReferenceTracking=true>
static StateSpaceController<dimState, dimInput, dimOutput, false, true, true> controller(model);  
static Matrix<dimOutput> y;

double current[2];
double motorSpeed[2];
double euler[2];
double gyro[2];

void setup()
{
  Serial.begin(115200);
  
  setupMoteurs();
  setupEncodeurs();
  setupBNO();


  
  controller.K << -0.3594, -0.0569, -0.0003, 1.5661, 0, 0, 0, 0,     
                  0, 0, 0, 0, -0.3594, -0.0569, -0.0003, 1.5661;


  controller.I << 0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0;

  controller.r << 0.00;
                  0.00;
                  0.00;
                  0.00;
                  0.00;
                  0.00;
                  0.00;
                  0.00;
               
  controller.initialise();
 
  

  Serial.println(F("\nEntrez un caractère pour commencer"));
  while (Serial.available() && Serial.read()); // empty buffer
  while (!Serial.available());                 // wait for data
  while (Serial.available() && Serial.read()); // empty buffer again

}


void loop()
{
  unsigned long tStart = micros();

  if (Serial.available() > 0) {
    state = Serial.read();
  }
  
  updateMotorSpeed(motorSpeed);
  updateCurrent(current, motorSpeed);
  updateEuler(euler);
  updateGyro(gyro);

  y(0) = euler[0];
  y(1) = gyro[0];
  y(2) = motorSpeed[0];
  y(3) = current[0];
  y(4) = euler[1];
  y(5) = gyro[1];
  y(6) = motorSpeed[1];
  y(7) = current[1];

  controller.update(y, CONTROL_PERIODE_MS * 1e-3);

  

  if (state == 32) {
    // Commande des moteurs selon la commande calculée
    runMoteurs(-(int)controller.u(0)*255/12, -(int)controller.u(1)*255/12);
  }
  else {
    runMoteurs(0, 0);

  }
  stateDisplayer(y);
  
  while ((micros() - tStart) < (CONTROL_PERIODE_MS * 1e3))
  {
    //poll until the next sample is ready
  }

}

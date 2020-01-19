#include "StateSpace.h"
#include "Moteurs.h"
#include "Angles.h"
#include "Encodeurs.h"

float controlSampleTime = BNO055_SAMPLERATE_DELAY_MS * 1e-3;
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


  
  controller.K << -3.63765402e+01, -5.76162892e+00, -1.82990705e-02, 1.98775374e+00, 0, 0, 0, 0,     
                  0, 0, 0, 0, -3.63765402e+01, -5.76162892e+00, -1.82990705e-02, 1.98775374e+00;


  controller.I << 5, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 5, 0, 0, 0;

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

  updateCurrent(current);
  updateMotorSpeed(motorSpeed);
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

  controller.update(y, controlSampleTime);

  

  if (state == 32) {

    // Commande des moteurs selon la commande calculée
    runMoteurs(-(int)controller.u(0)*255/12, -(int)controller.u(1)*255/12);
  }
  else {
    runMoteurs(0, 0);

  }
  stateDisplayer(y);



  
  while ((micros() - tStart) < (controlSampleTime * 1e6))
  {
    //poll until the next sample is ready
  }

}

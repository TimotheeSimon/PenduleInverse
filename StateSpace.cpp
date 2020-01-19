#include "StateSpace.h"

void stateDisplayer(Matrix<dimOutput> y) {
  Serial.print(y(0));
  Serial.print(",");
  Serial.print(y(1));
  Serial.print(",");
  Serial.print(y(2));
  Serial.print(",");
  Serial.print(y(3));
  Serial.print(",");
  Serial.print(y(4));
  Serial.print(",");
  Serial.print(y(5));
  Serial.print(",");
  Serial.print(y(6));
  Serial.print(",");
  Serial.println(y(7));
}

#include "perifericos.h"

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  Test sla(500);

  Serial.printf("\n%d",sla.getNumero());

  sla.setNumero(999);

  Serial.printf("\n%d",sla.getNumero());
  
}

void loop() {
  // put your main code here, to run repeatedly:

}

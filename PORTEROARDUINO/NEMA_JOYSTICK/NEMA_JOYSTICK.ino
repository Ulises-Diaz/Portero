#include <AccelStepper.h>

#define dirPin 3
#define stepPin 2

AccelStepper stepper(AccelStepper::DRIVER, stepPin, dirPin);

void setup() {
  stepper.setMaxSpeed(1000); // Ajusta según tus necesidades
  stepper.setAcceleration(1000); // Ajusta según tus necesidades
}

void loop() {
  int xPosition = analogRead(A0);

  // Definir un rango muerto
  int threshold = 50;
  int speed;
  
  if (xPosition > (512 + threshold)) {
    // Mover en una dirección
    speed = map(xPosition, 512 + threshold, 1023, 0, 1000); 
  } 
  else if (xPosition < (512 - threshold)) {
    // Mover en la otra dirección
    speed = map(xPosition, 0, 512 - threshold, -1000, 0);
  } else {
    // Dentro del rango muerto, no moverse
    speed = 0;
  }

  stepper.setSpeed(speed);
  stepper.runSpeed();
}


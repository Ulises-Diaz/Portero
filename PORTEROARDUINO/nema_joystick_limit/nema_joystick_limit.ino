#include <AccelStepper.h>

#define dirPin 3
#define stepPin 2
#define limitSwitchPin 7 // Limit switch para el lado derecho
#define limitSwitchPin2 6 // Limit switch para el lado izquierdo

int solenoidPin = 7;
int zPin = 8;

int zPosition;

AccelStepper stepper(AccelStepper::DRIVER, stepPin, dirPin);

void setup() {

  Serial.begin(9600);

  pinMode(solenoidPin, OUTPUT);
  pinMode(zPin, INPUT_PULLUP);
  stepper.setMaxSpeed(1000); // Set max speed of the stepper motor
  stepper.setAcceleration(500); // Set acceleration of the stepper motor

  pinMode(limitSwitchPin, INPUT_PULLUP); // Configure right limit switch pin as input with pull-up
  pinMode(limitSwitchPin2, INPUT_PULLUP); // Configure left limit switch pin as input with pull-up
}

void loop() {
  // Read the state of the limit switches
  bool limitSwitchPressedRight = digitalRead(limitSwitchPin) == LOW;
  bool limitSwitchPressedLeft = digitalRead(limitSwitchPin2) == LOW;

  // Read the potentiometer position
  int xPosition = analogRead(A0);

  // Define a dead zone
  int threshold = 50;
  int speed;


  if (xPosition > (512 + threshold)) {
    // Attempt to move to the right
    speed = map(xPosition, 512 + threshold, 1023, 0, 1000);
    if (limitSwitchPressedRight) {
      // If the right limit switch is pressed, do not allow movement to the right
      speed = 0;
    }
  } else if (xPosition < (512 - threshold)) {
    // Attempt to move to the left
    speed = map(xPosition, 0, 512 - threshold, -1000, 0);
    if (limitSwitchPressedLeft) {
      // If the left limit switch is pressed, do not allow movement to the left
      speed = 0;
    }
  } else {
    // Within the dead zone, do not move
    speed = 0;
  }

  if (zPosition == HIGH) {
    digitalWrite(solenoidPin, LOW);
  } else {
    // Si el botón no está presionado, apagar el LED
    digitalWrite(solenoidPin, HIGH);
  }

  stepper.setSpeed(speed); // Set the motor speed
  stepper.runSpeed(); // Run the motor at the set speed
}
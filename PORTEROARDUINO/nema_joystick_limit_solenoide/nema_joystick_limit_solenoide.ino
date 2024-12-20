#include <AccelStepper.h>

//cambiar define por int es lo mismo. 
#define dirPin 3
#define stepPin 2
#define limitSwitchPin 5 // Limit switch for the right side
#define limitSwitchPin2 6 // Limit switch for the left side
#define zPin 7

int solenoidPin = 8;


AccelStepper stepper(AccelStepper::DRIVER, stepPin, dirPin);
//crea un objeto stepper de la clase AccelStepper.
//AccelStepper::DRIVER es el controlador de pulsos y direccion. 
//damos el stepPin como pulsos
//el dirPin como direccion del pin

void setup() {
  Serial.begin(9600);

  pinMode(solenoidPin, OUTPUT);
  pinMode(zPin, INPUT_PULLUP);
  stepper.setMaxSpeed(300); // Set max speed of the stepper motor
  stepper.setAcceleration(50); // Set acceleration of the stepper motor

  pinMode(limitSwitchPin, INPUT_PULLUP); // Configure right limit switch pin as input with pull-up
  pinMode(limitSwitchPin2, INPUT_PULLUP); // Configure left limit switch pin as input with pull-up
}

void loop() {
  
  // Leer el estado de los interruptores de límite derecho e izquierdo
  // y almacenar el resultado en variables booleanas.
  // limitSwitchPressedRight es true si el interruptor derecho está presionado (pin en LOW).
  // limitSwitchPressedLeft es true si el interruptor izquierdo está presionado (pin en LOW).

  bool limitSwitchPressedRight = digitalRead(limitSwitchPin) == LOW;
  bool limitSwitchPressedLeft = digitalRead(limitSwitchPin2) == LOW;

  // Read the state of the zPin
  bool zPinState = digitalRead(zPin);

  // Control the solenoid based on the state of the zPin
  if (zPinState == HIGH) {
    digitalWrite(solenoidPin, LOW);
  } else {
    digitalWrite(solenoidPin, HIGH);
  }

  // Read the potentiometer position
  int xPosition = analogRead(A0);

  // Define a dead zone
  int threshold = 50;
  int speed;

  if (xPosition > (512 + threshold)) {
    // Attempt to move to the right
    speed = map(xPosition, 512 + threshold, 1023, 0, 1000); 
    //xposition: valor de entrada a mapear. Valor actual de x
    //512 + threshold: limit inferior de entrada. Potenciometro regresa valores de 0-1023
    //1023: limite de rango entrada superior para lectura analogica. 
    //0: limite inferior salida. En este caso velocidad minima que asignamos
    //1000: valor maximo de salida. Velocidad max que asignamos
    if (limitSwitchPressedLeft) {
      // If the right limit switch is pressed, do not allow movement to the right
      speed = 0;
    }
  } else if (xPosition < (512 - threshold)) { //
    // Attempt to move to the left
    speed = map(xPosition, 0, 512 - threshold, -1000, 0); //lectura analogica 512
    if (limitSwitchPressedRight) {
      // If the left limit switch is pressed, do not allow movement to the left
      speed = 0;
    }
  } else {
    // Within the dead zone, do not move
    speed = 0;
  }

  stepper.setSpeed(speed); // Set the motor speed
  stepper.runSpeed(); // Run the motor at the set speed
}

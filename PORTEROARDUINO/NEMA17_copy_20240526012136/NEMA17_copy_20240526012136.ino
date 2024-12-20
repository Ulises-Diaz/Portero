#define stepPin 2
#define dirPin 5
#define enablePin 8
#define ms1Pin 9
#define ms2Pin 10
#define ms3Pin 11

#define xPin A0
#define yPin A1
#define zPin A2

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(ms1Pin, OUTPUT);
  pinMode(ms2Pin, OUTPUT);
  pinMode(ms3Pin, OUTPUT);

  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(zPin, INPUT);

  digitalWrite(enablePin, LOW);

  // Configura microstepping (1/4 microstepping para A4988)
  digitalWrite(ms1Pin, LOW);
  digitalWrite(ms2Pin, HIGH);
  digitalWrite(ms3Pin, LOW);
}

void loop() {
  int xPosition = analogRead(xPin);
  int yPosition = analogRead(yPin);
  int zPosition = analogRead(zPin);

  if (xPosition > 512) {
    digitalWrite(dirPin, HIGH);
  } else {
    digitalWrite(dirPin, LOW);
  }

  // Reduce el mínimo de speed para aumentar la velocidad
  int speed = map(yPosition, 0, 1023, 500, 50);

  digitalWrite(stepPin, HIGH);
  delayMicroseconds(speed);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(speed);
}



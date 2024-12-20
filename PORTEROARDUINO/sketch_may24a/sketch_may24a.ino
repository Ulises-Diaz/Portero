// Define ports:
int xPin = A1;
int yPin = A0;
int zPin = 2;

// Declare variables for positions:
int xPosition, yPosition, zPosition;

void setup() {
  // Initialize serial communications at 9600 bps:
  Serial.begin(9600);

  // Initialize pin modes:
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(zPin, INPUT_PULLUP);
}

void loop() {
  // Read values from analogic port:
  xPosition = analogRead(xPin);
  yPosition = analogRead(yPin);
  // Read value from digital port:
  zPosition = digitalRead(zPin);

  // Remap (0, 1023) -> (0, 255):
  xPosition = map(xPosition, 0, 1023, 0, 255); // Remapeamos para que sea de entrada analógica a digital. 1023 es el máx y lo cambiamos a 255 máx de PWM.
  yPosition = map(yPosition, 0, 1023, 0, 255);
  
  
  // Print (x, y) values:
  Serial.print("x = ");
  Serial.println(xPosition);
  delay(1000);
  Serial.print("y = ");
  Serial.println(yPosition);
  delay(1000);

  // Print z value:
  Serial.print("z = ");
  Serial.println(zPosition); // Agregamos el punto y coma al final de la línea

  delay(1000);
}

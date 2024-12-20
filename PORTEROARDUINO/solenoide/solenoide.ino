int solenoidPin = 8;
int zPin = 7 ;

int zPosition;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(solenoidPin, OUTPUT);
  pinMode(zPin, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  zPosition = digitalRead(zPin);
  
  if (zPosition == HIGH) {
    digitalWrite(solenoidPin, LOW);
  } else {
    // Si el botón no está presionado, apagar el LED
    digitalWrite(solenoidPin, HIGH);
  }
}


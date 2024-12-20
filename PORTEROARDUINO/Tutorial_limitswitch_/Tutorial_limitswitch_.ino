int Lswitch = 2;  
int led = 13 ; //this pin is related to the pin of the arduino 
int flag = 0; // stop unecessary repetition of code. Not sure how it works 
//flag se usa para conocer el estado de la puerta


void setup() {
  // put your setup code here, to run once:

Serial.begin(9600); //inicia la comunicacion serial a 9600 bits por segundo. Deja que el arduino se comunique con la compu
pinMode(Lswitch, INPUT);
pinMode(led, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

// este if checa si el Swtich es LOW (la puerta esta cerrada) y si flag es 0, la puerta printea (door is closed)
//Luego setea flag a 1 y espera 20 mms.
if ( (digitalRead(Lswitch) == LOW) && (flag ==0) ){

Serial.print("door is closed");
flag = 1; 
delay(20);

}

//si switch es HIGH (si esta abierto) y  flag es 1 (del codigo pasado), se printea (door is open)
//regresa el valor de flag a 0
if((digitalRead(Lswitch) == HIGH) && (flag ==1))
{

Serial.print("door is open");
flag =0;
delay(20);

}


//Si flag es 1 (la puerta esta cerrada) turnea el led on por 1 segundo y luego lo apaga por 1 segundo.
if (flag ==1){ //if door is closed
  digitalWrite(led,HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(1000);
}


//apaga el led si flag es 1. 
if ( flag ==1){
  digitalWrite(led,LOW);

}
}

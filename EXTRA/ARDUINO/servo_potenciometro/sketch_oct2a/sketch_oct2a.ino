#include <Servo.h>

int value, mapped_value;
Servo servo;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo.attach(6);
  servo.write(0);
}

void loop() {
  // put your main code here, to run repeatedly:

  // Controle de valor de entrada 
  value = analogRead(A0);
  mapped_value = map(value, 0, 1023, 0, 180);

  servo.write(mapped_value);

  Serial.print(value); 
  Serial.print("\t");
  Serial.print(mapped_value);
  Serial.print("\n");
  // delay(200); 
}

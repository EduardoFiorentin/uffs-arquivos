int a = 2;
int b = 3; 
int c = 4;
int d = 5;
int e = 6;
int f = 7;
int g = 8;
int h = 9;
int i = 10;

void coracaoPulsante() {
  int delayTime = 200;

  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  delay(delayTime);

  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  delay(delayTime);

  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  delay(delayTime);

  digitalWrite(g, HIGH);
  digitalWrite(h, HIGH);
  delay(delayTime);

  digitalWrite(i, HIGH);
  delay(delayTime);

  // Desliga os LEDs em ordem inversa para simular o batimento do coração
  digitalWrite(i, LOW);
  delay(delayTime);
  
  digitalWrite(h, LOW);
  digitalWrite(g, LOW);
  delay(delayTime);
  
  digitalWrite(f, LOW);
  digitalWrite(e, LOW);
  delay(delayTime);
  
  digitalWrite(d, LOW);
  digitalWrite(c, LOW);
  delay(delayTime);
  
  digitalWrite(b, LOW);
  digitalWrite(a, LOW);
  delay(delayTime);
}

void ondas() {
  int delayTime = 100;
  
  for (int i = 0; i < 3; i++) {
    digitalWrite(a, HIGH);
    delay(delayTime);
    digitalWrite(a, LOW);
    
    digitalWrite(b, HIGH);
    delay(delayTime);
    digitalWrite(b, LOW);
    
    digitalWrite(c, HIGH);
    delay(delayTime);
    digitalWrite(c, LOW);
    
    digitalWrite(d, HIGH);
    delay(delayTime);
    digitalWrite(d, LOW);
    
    digitalWrite(e, HIGH);
    delay(delayTime);
    digitalWrite(e, LOW);
    
    digitalWrite(f, HIGH);
    delay(delayTime);
    digitalWrite(f, LOW);
    
    digitalWrite(g, HIGH);
    delay(delayTime);
    digitalWrite(g, LOW);
    
    digitalWrite(h, HIGH);
    delay(delayTime);
    digitalWrite(h, LOW);
    
    digitalWrite(i, HIGH);
    delay(delayTime);
    digitalWrite(i, LOW);
  }
}

void estrelaCintilante() {
  int leds[] = {a, b, c, d, e, f, g, h, i};
  for (int i = 0; i < 50; i++) {
    int randomLed = random(0, 9);
    digitalWrite(leds[randomLed], HIGH);
    delay(100);
    digitalWrite(leds[randomLed], LOW);
    delay(100);
  }
}

void corridaDeLuz() {
  int delayTime = 100;

  // Vai da esquerda para a direita
  for (int i = a; i <= i; i++) {
    digitalWrite(i, HIGH);
    delay(delayTime);
    digitalWrite(i, LOW);
  }

  // Volta da direita para a esquerda
  for (int i = i; i >= a; i--) {
    digitalWrite(i, HIGH);
    delay(delayTime);
    digitalWrite(i, LOW);
  }
}

void preenchimentoDeLuz() {
  int delayTime = 200;

  // Acende da borda para o centro
  digitalWrite(a, HIGH);
  digitalWrite(i, HIGH);
  delay(delayTime);
  
  digitalWrite(b, HIGH);
  digitalWrite(h, HIGH);
  delay(delayTime);
  
  digitalWrite(c, HIGH);
  digitalWrite(g, HIGH);
  delay(delayTime);
  
  digitalWrite(d, HIGH);
  digitalWrite(f, HIGH);
  delay(delayTime);
  
  digitalWrite(e, HIGH);
  delay(delayTime);

  // Apaga do centro para a borda
  digitalWrite(e, LOW);
  delay(delayTime);
  
  digitalWrite(d, LOW);
  digitalWrite(f, LOW);
  delay(delayTime);
  
  digitalWrite(c, LOW);
  digitalWrite(g, LOW);
  delay(delayTime);
  
  digitalWrite(b, LOW);
  digitalWrite(h, LOW);
  delay(delayTime);
  
  digitalWrite(a, LOW);
  digitalWrite(i, LOW);
  delay(delayTime);
}

void pinguePongue() {
  int delayTime = 100;
  
  // Vai da esquerda para a direita
  for (int i = a; i <= i; i++) {
    digitalWrite(i, HIGH);
    delay(delayTime);
    digitalWrite(i, LOW);
  }
  
  // Volta da direita para a esquerda
  for (int i = i; i >= a; i--) {
    digitalWrite(i, HIGH);
    delay(delayTime);
    digitalWrite(i, LOW);
  }
}


void setup() {
  // put your setup code here, to run once:
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(h, OUTPUT);
  pinMode(i, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  // digitalWrite(a, HIGH);
  // digitalWrite(b, HIGH);
  // digitalWrite(c, HIGH);
  // digitalWrite(d, HIGH);
  // digitalWrite(e, HIGH);
  // digitalWrite(f, HIGH);
  // digitalWrite(g, HIGH);
  // digitalWrite(h, HIGH);
  // digitalWrite(i, HIGH);
  
  coracaoPulsante();
  
  // ondas();
  // estrelaCintilante();
  // corridaDeLuz();
  // preenchimentoDeLuz();
  // pinguePongue();

}

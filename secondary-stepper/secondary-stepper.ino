// TB-6600 driver pins
#define dirpin 8 // DIR
#define steppin 9 // PUL
#define enable 7 // ENA

#define input 13

// Define variables for distance
long duration;
int distance = 10;
boolean running = true;
int triggerState = 0;

void setup() {
  pinMode(dirpin, OUTPUT);
  pinMode(steppin, OUTPUT);
  pinMode(enable, OUTPUT);
  digitalWrite(enable, LOW);
  
  
  digitalWrite(dirpin, HIGH); // Set the direction.
  pinMode(input, INPUT);
  
  Serial.begin(9600);
  delay(750); 
}

void loop() {

  checkTriggerState();
  //triggerState = digitalRead(input);
  
  //while (triggerState == 0) {
  //  triggerState = digitalRead(input);
  //  Serial.println("Waiting for trigger");
  //  digitalWrite(enable, HIGH);
  //}
  
  

  vibrate(60);
  shuffle(2);
  step(2000, 5000);
}

void shuffle(int* count) {
  for (int i = 0; i < count; i++) {
    digitalWrite(dirpin, LOW);
    step(1000, 100);
    digitalWrite(dirpin, HIGH);
    step(900, 100);
  }
}

void vibrate(int* count) {
  for (int i = 0; i < count; i++) {
    int speed = 80;
    int steps = 325;
    digitalWrite(dirpin, LOW);
    step(steps, speed);
    digitalWrite(dirpin, HIGH);
    step(steps, speed);
  }
}

void step(int* steps, int* speed) {
  for (int i = 0; i < steps; i++) {
    digitalWrite(steppin, LOW); // This LOW to HIGH change is what creates the step
    delayMicroseconds(speed);
    digitalWrite(steppin, HIGH);
    checkTriggerState();
  }
}

void checkTriggerState() {
  while (digitalRead(input) == 0) {
    Serial.println("Pause...");
    digitalWrite(enable, HIGH);
  }
  digitalWrite(enable, LOW);
}

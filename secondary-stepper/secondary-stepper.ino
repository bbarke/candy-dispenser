/**
 * Code for the Candy Dispenser - Secondary stepper board
 * Created by Brent Barker (Barkers' Random Projects)
 * 
 * The purpose of this board is to turn on and off the stepper motor
 * depending on if it is told to do so from the main arduino board
 * 
 * Checkout out the YouTube video to see it working!!
 * 
 */



// Stepper driver (TB-6600) driver pins
#define dirpin 8 // DIR
#define steppin 9 // PUL
#define enable 7 // ENA

// Input from main arduino board
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
  // The sequnece that the stepper motor goes through to drive the belt
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
    digitalWrite(steppin, LOW); // This LOW to HIGH switch is what creates the step
    delayMicroseconds(speed);
    digitalWrite(steppin, HIGH);
    // Check if the main arduino board has told us to pause between each step
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

// Pin for other Arduino
#define output 13

#define btnIn 12
#define btnOut 11
#define ledPinNeg 10
#define ledPinPos 9

// Define Trig and Echo pin for HC-SR04:
#define trigPin 2
#define echoPin 3
#define power 4 // VCC for HC-SR04

// IR Beam Sensor
#define beamNeg 8
#define beamPos 7
#define beamInput 6



// Define variables for distance
long duration;
float distance = 10;
boolean running = true;
int buttonState = 0;
int threshold = 15;
void setup() {
  
  pinMode(power, OUTPUT);
  digitalWrite(power, HIGH);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(output, OUTPUT);

  pinMode(btnIn, INPUT);
  pinMode(btnOut, OUTPUT);
  digitalWrite(btnOut, HIGH);


  pinMode(ledPinPos, OUTPUT);
  digitalWrite(ledPinPos, HIGH);

  pinMode(ledPinNeg, OUTPUT);
  digitalWrite(ledPinNeg, LOW);


  // IR Beam Sensor
  pinMode(beamPos, OUTPUT);
  digitalWrite(beamPos, HIGH);

  pinMode(beamNeg, OUTPUT);
  digitalWrite(beamNeg, LOW);
  pinMode(beamInput, INPUT);
  digitalWrite(beamInput, HIGH);

  //Begin Serial communication at a baudrate of 9600:
  Serial.begin(9600);
  delay(500); 
}

void loop() {

  buttonState = digitalRead(btnIn);
  
  Serial.println("Loop");
  turnOff();
  delay(250);
  digitalWrite(ledPinPos, HIGH);

  while (buttonState == 0) {
    buttonState = digitalRead(btnIn);
    Serial.print("Waiting for button: ");
    Serial.println(isBeamBroken());
    //getDistance();
    //threshold = distance - 2;
  }

  //digitalWrite(power, HIGH);
  //delay(500);

  digitalWrite(ledPinPos, LOW);
  digitalWrite(output, HIGH);
  //getDistance();
  
  // Candy is here!
  //while (distance > threshold && distance < 100) {
  //  getDistance();
  //}

  while (!isBeamBroken()) {
    Serial.println(isBeamBroken());
  }
  turnOff();
  delay(300);

  while (isBeamBroken()) {
    Serial.println(isBeamBroken());
    turnOn();
    delay(40);
    turnOff();
    delay(350);
  }

  // Candy dropped!
  //while (distance <= threshold) {
  //  Serial.println("Wait for drop");
  //  getDistance();
  //}
}

bool isBeamBroken() {
  return !digitalRead(beamInput);
}

void turnOff() {
  digitalWrite(output, LOW);
}

void turnOn() {
  digitalWrite(output, HIGH);
}


void getDistance() {

  // Clear the trigPin by setting it LOW:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  
  // Trigger the sensor by setting the trigPin high for 10 microseconds:
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echoPin, pulseIn() returns the duration (length of the pulse) in microseconds:
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance:
  distance = duration*0.034/2;
  
  // Print the distance on the Serial Monitor (Ctrl+Shift+M):
  Serial.print("Distance = ");
  Serial.print(distance);
  Serial.print(" cm");
  Serial.print(" threshold = ");
  Serial.println(threshold);
  delay(50); 
}

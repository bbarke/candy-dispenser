/**
 * Code for the Candy Dispenser - Main sesnors board (Touchless version)
 * Created by Brent Barker (Barkers Random Projects)
 * 
 * The purpose of this board is to wait until something goes in front of the
 * ultrasonic distance sensor, then send a single to a secondary arduino board 
 * telling it to turn on and off a stepper motor, and waits for a IR break 
 * sensor to be tripped. 
 * 
 * Checkout out the YouTube video to see it working!!
 * 
 */


// Pin that talks to other Arduino
#define output 13

// Button led light and input
#define btnIn 12
//#define btnOut 11
#define ledPinRed 11
#define ledPinGreen 10
#define ledPinPos 9

// IR Beam Sensor
#define beamNeg 8
#define beamPos 7
#define beamInput 6

// Ultrasonic Sensor
#define ultraTrigPin 2
#define ultraEchoPin 3
#define ultraGnd 4
#define ultraVcc 5



// Define variables for distance
long duration;
int distance = 0;
boolean running = true;
//int buttonState = 0;
int threshold = 15;
void setup() {
  
  pinMode(output, OUTPUT);

  pinMode(btnIn, INPUT);
  //pinMode(btnOut, OUTPUT);
  //digitalWrite(btnOut, HIGH);
  
  pinMode(ledPinRed, OUTPUT);
  digitalWrite(ledPinRed, LOW);


  pinMode(ledPinPos, OUTPUT);
  digitalWrite(ledPinPos, HIGH);

  pinMode(ledPinGreen, OUTPUT);
  digitalWrite(ledPinGreen, LOW);


  // IR Beam Sensor
  pinMode(beamPos, OUTPUT);
  digitalWrite(beamPos, HIGH);

  pinMode(beamNeg, OUTPUT);
  digitalWrite(beamNeg, LOW);
  pinMode(beamInput, INPUT);
  digitalWrite(beamInput, HIGH);

  // Ultrasonic Sensor
  pinMode(ultraTrigPin, OUTPUT);
  pinMode(ultraEchoPin, INPUT);

  pinMode(ultraGnd, OUTPUT);
  digitalWrite(ultraGnd, LOW);
  pinMode(ultraVcc, OUTPUT);
  digitalWrite(ultraVcc, HIGH);
  
  //Begin Serial communication at a baudrate of 9600:
  Serial.begin(9600);
  delay(500); 
}

void loop() {

  Serial.println("Loop");
  turnOffStepper();
  delay(250);


  // Prevent kids from holding the button down
  distance = getDistanceAvg();
  
  while (distance < 30) {
    distance = getDistanceAvg();
    Serial.println("Wait for their hand to move");
    delay(500);
  }
  turnOnGreenLed();
  delay(250);
  while (distance > 30) {
    distance = getDistanceAvg();
    Serial.println("Waiting for trigger...");
  }

  turnOnRedLed();
  turnOnStepper();

  // Wait for beam to be broken
  while (!isBeamBroken()) {
    Serial.println(isBeamBroken());
  }
  turnOffStepper();
  delay(300);

  // Wait for beam to reconnect
  while (isBeamBroken()) {
    Serial.println(isBeamBroken());
    turnOnStepper();
    delay(40);
    turnOffStepper();
    delay(350);
  }
}

int getButtonState() {
  return digitalRead(btnIn);
}

bool isBeamBroken() {
  return !digitalRead(beamInput);
}

void turnOffStepper() {
  digitalWrite(output, LOW);
}

void turnOnStepper() {
  digitalWrite(output, HIGH);
}

int getDistance() {
  int distance = 0;
  // Clear the trigPin by setting it LOW:
  digitalWrite(ultraTrigPin, LOW);
  delayMicroseconds(5);
  // Trigger the sensor by setting the trigPin high for 10 microseconds:
  digitalWrite(ultraTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultraTrigPin, LOW);
  // Read the echoPin, pulseIn() returns the duration (length of the pulse) in microseconds:
  duration = pulseIn(ultraEchoPin, HIGH);
  // Calculate the distance:
  distance = duration*0.034/2;
  return distance;
}

void turnOnGreenLed() {                                                                                          
  digitalWrite(ledPinRed, HIGH);
  digitalWrite(ledPinGreen, LOW);
}

void turnOnRedLed() {
  digitalWrite(ledPinRed, LOW);
  digitalWrite(ledPinGreen, HIGH);
}

int getDistanceAvg() {

  int count = 10;
  int distanceAdd = 0;
  for(int i = 0; i < count; i++) {
    distanceAdd += getDistance();
  }
  Serial.print("Avg distance: ");
  Serial.print(distanceAdd / count);
  Serial.print(" ");
  return distanceAdd / count;
}

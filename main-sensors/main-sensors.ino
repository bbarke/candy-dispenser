/**
 * Code for the Candy Dispenser - Main sesnors board
 * Created by Brent Barker (Barkers' Random Projects)
 * 
 * The purpose of this board is to wait for the classic arcade button to be pushed,
 * send a single to a secondary arduino board tellint it to turn on and off a stepper
 * motor, and waits for a IR break sensor to be tripped. 
 * 
 * Checkout out the YouTube video to see it working!!
 * 
 */


// Pin that talks to other Arduino
#define output 13

// Button led light and input
#define btnIn 12
#define btnOut 11
#define ledPinNeg 10
#define ledPinPos 9

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
  turnOffStepper();
  delay(250);
  digitalWrite(ledPinPos, HIGH);

  // Prevent kids from holding the button down
  buttonState = getButtonState();
  while (buttonState == 1) {
    buttonState = getButtonState();
  }
  
  while (buttonState == 0) {
    buttonState = getButtonState();
    Serial.print("Waiting for button: ");
    Serial.println(isBeamBroken());
  }

  digitalWrite(ledPinPos, LOW);
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

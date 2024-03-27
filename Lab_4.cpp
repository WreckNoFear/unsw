// --------------------------
// Motor Controller Interface
// Written by Adam Schon
// --------------------------

// Motor pin variables
int motorLogicLeftPin1 = 3;
int motorLogicLeftPin2 = 9;
int motorLogicRightPin1 = 10;
int motorLogicRightPin2 = 11;

// PWM cycle variable
int pwmDutyCycle = 255;
char currentDirection;

// Init
void setup() {
  // Initialise serial connection
  Serial.begin(9600);
  
  // Initialisation text
  Serial.println("---------------");
  Serial.println("Initialising...");
  
  // Assign pin modes for motors
  pinMode(motorLogicLeftPin1, OUTPUT);
  pinMode(motorLogicLeftPin2, OUTPUT);
  pinMode(motorLogicRightPin1, OUTPUT);
  pinMode(motorLogicRightPin2, OUTPUT);
  
  // Confirm initilisation
  Serial.println("Initialisation complete.");
}

// Main
void loop() {
  // Check if character is inputted into serial monitor
  if (Serial.available()) {
    char input = Serial.read();
    Serial.println(input);
    
    // What character was inputted?
    switch (input) {
      // Movements
      case 'f':
      	motorForward();
      	currentDirection = 'f';
      	break;
      case 'b':
        motorBackward();
      	currentDirection = 'b';
      	break;
      case 'l':
        motorLeft();
      	currentDirection = 'l';
      	break;
      case 'r':
        motorRight();
      	currentDirection = 'r';
      	break;
      
      // Speed changes
      case '0':
      	Serial.println("Stop");
      	pwmDutyCycle = 0;
      	updateMotors();
      	break;
      case '1':
      	Serial.println("Speed = 10%");
      	pwmDutyCycle = 25.5;
      	updateMotors();
      	break;
      case '2':
        Serial.println("Speed = 20%");
      	pwmDutyCycle = 51;
      	updateMotors();
      	break;
      case '3':
        Serial.println("Speed = 30%");
      	pwmDutyCycle = 76.5;
      	updateMotors();
      	break;
      case '4':
        Serial.println("Speed = 40%");
      	pwmDutyCycle = 102;
      	updateMotors();
      	break;
      case '5':
        Serial.println("Speed = 50%");
      	pwmDutyCycle = 127.5;
      	updateMotors();
      	break;
      
      // If character that does not match any case
      default:
      	Serial.println("Invalid character input.");
      	break;
    }
  }
}

// Update motors immediately after speed change
void updateMotors() {
  switch(currentDirection) {
    case 'f':
      motorForward();
      break;
    case 'b':
      motorBackward();
      break;
    case 'l':
      motorLeft();
      break;
    case 'r':
      motorRight();
      break;
  }
}

// Motor movement functions
void motorForward() {
  Serial.println("Forwards");
  analogWrite(motorLogicLeftPin1, 0);
  analogWrite(motorLogicRightPin1, 0);
  analogWrite(motorLogicLeftPin2, pwmDutyCycle);
  analogWrite(motorLogicRightPin2, pwmDutyCycle);
}
void motorBackward() {
  Serial.println("Backwards");
  analogWrite(motorLogicLeftPin1, pwmDutyCycle);
  analogWrite(motorLogicRightPin1, pwmDutyCycle);
  analogWrite(motorLogicLeftPin2, 0);
  analogWrite(motorLogicRightPin2, 0);
}
void motorLeft() {
  Serial.println("Turn Left");
  analogWrite(motorLogicLeftPin1, pwmDutyCycle);
  analogWrite(motorLogicRightPin1, 0);
  analogWrite(motorLogicLeftPin2, 0);
  analogWrite(motorLogicRightPin2, pwmDutyCycle);
}
void motorRight() {
  Serial.println("Turn Right");
  analogWrite(motorLogicLeftPin1, 0);
  analogWrite(motorLogicRightPin1, pwmDutyCycle);
  analogWrite(motorLogicLeftPin2, pwmDutyCycle);
  analogWrite(motorLogicRightPin2, 0);
}

// -----------------------------
// Motor Controller Interface v2
// Written by Adam Schon
// -----------------------------

// Define motor PWM pins
#define motorLogicLeftPin1 3
#define motorLogicLeftPin2 9
#define motorLogicRightPin1 10
#define motorLogicRightPin2 11

// Define ultrasonic sensor PWM pins
#define trigPin 6
#define echoPin 5

// Set global variables and inital values
int pwmDutyCycle = 255;
int warningDistance = 30;
bool keyboardControl = true;
bool warned = false;
char currentDirection;

// ---------------------------------------------------
// Setup function runs once and initilises the program
// ---------------------------------------------------
void setup() {
  // Initialise serial monitor connection
  Serial.begin(9600);
  
  // Print text showing initialisation started
  Serial.println("---------------");
  Serial.println("Initialising...");

  // Set pin modes for motor logic and sensor pins
  initialisePins();
  
  // Confirm initilisation has completed
  Serial.println("Initialisation complete.");
}

// -------------------------------------------------------
// Loop function runs repeatedly and contains main program
// -------------------------------------------------------
void loop() {
  // Check if any object within 30cm of sensor and show warning
  checkWarning();

  // Check for serial monitor input
  char command = receiveCommand();

  // Ensure serial monitor input is of acceptable type
  if (!isAlphaNumeric(command)) return;

  // Check if command is to toggle keyboard control mode
  if (command == 'x') {
    keyboardControl = toggleMode();
  }

  // Check if keyboard control is active, if not, do not continue
  if (!keyboardControl) return;

  // Update direction and speed of motors if keyboard control is active
  updateDirection(command);
  updateSpeed(command, currentDirection);

  // Delay to allow time for serial monitor input
  delay(10);
}

// Assign pin modes to motor logic and ultrasonic sensor pins
void initialisePins() {
  // Assign pin modes for motor logic
  pinMode(motorLogicLeftPin1, OUTPUT);
  pinMode(motorLogicLeftPin2, OUTPUT);
  pinMode(motorLogicRightPin1, OUTPUT);
  pinMode(motorLogicRightPin2, OUTPUT);
  
  // Assign pin modes for ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

// Checks if serial monitor input is avaiable, reads it, and returns the value
char receiveCommand() {
  if (Serial.available() > 0) {
    char input = Serial.read();
  	return input;
  }
}

// Toggles between keyboard control enabled and disabled modes
bool toggleMode() {
  if (keyboardControl) {
    Serial.println("Exited keyboard control");
    return false;
  } else {
    Serial.println("Enabled keyboard control");
    return true;
  }
}



// Checks if any object is within 30cm of the sensor and issues warning if within
void checkWarning() {
  // Send ultrasonic pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Call calculateDistance function
  int distance = calculateDistance();

  // Check if object within 30cm and if a warning was already issued, and return appropriate response
  if (distance <= warningDistance && warned == false) {
    warned = true;
    Serial.println("!!! WARNING !!! Object ahead within 30cm.");
  } else if (distance > warningDistance && warned == true) {
  	warned = false;
    Serial.println("Object no longer in warning range.");
  }
}

// Calculate distance between any object infront and the sensor
int calculateDistance() {
	int duration = pulseIn(echoPin, HIGH);
  	return (duration * 0.034)/2;
}


// Updates motor direction based on inputted command
// Sets current direction and calls corresponding motor function
char updateDirection(char command) {
  switch(command) {
    // Fowards
    case 'f':
      Serial.println("Forwards");
      motorForward();
      currentDirection = 'f';
      break;
    // Backwards
    case 'b':
      Serial.println("Backwards");
      motorBackward();
      currentDirection = 'b';
      break;
    // Left
    case 'l':
      Serial.println("Left");
      motorLeft();
      currentDirection = 'l';
      break;
    // Right
    case 'r':
      Serial.println("Right");
      motorRight();
      currentDirection = 'r';
      break;
  }
}

// Updates motor speed based on inputted command
// Sets PWM cycle and updates motor speed immediately by calling function with current direction
int updateSpeed(char command, char currentDirection) {
  switch(command) {
    // Stop motors
    case '0':
      Serial.println("Stop");
      pwmDutyCycle = 0;
      updateMotors(currentDirection);
      break;
    // 10% Speed
    case '1':
      Serial.println("Speed = 10%");
      pwmDutyCycle = 25.5;
      updateMotors(currentDirection);
      break;
    // 20% Speed
    case '2':
      Serial.println("Speed = 20%");
      pwmDutyCycle = 51;
      updateMotors(currentDirection);
      break;
    // 30% Speed
    case '3':
      Serial.println("Speed = 30%");
      pwmDutyCycle = 76.5;
      updateMotors(currentDirection);
      break;
    // 40% Speed
    case '4':
      Serial.println("Speed = 40%");
      pwmDutyCycle = 102;
      updateMotors(currentDirection);
      break;
    // 50% Speed
    case '5':
      Serial.println("Speed = 50%");
      pwmDutyCycle = 127.5;
      updateMotors(currentDirection);
      break;
  }
}

// Update motors with current direction after speed has been changed
void updateMotors(char currentDirection) {
  switch(currentDirection) {
    // Forwards
    case 'f':
      motorForward();
      break;
    // Backwards
    case 'b':
      motorBackward();
      break;
    // Left
    case 'l':
      motorLeft();
      break;
    // Right
    case 'r':
      motorRight();
      break;
  }
}

// Motor movement functions move motors to appropriate directions
// Forwards
void motorForward() {
  analogWrite(motorLogicLeftPin1, 0);
  analogWrite(motorLogicRightPin1, 0);
  analogWrite(motorLogicLeftPin2, pwmDutyCycle);
  analogWrite(motorLogicRightPin2, pwmDutyCycle);
}
// Backwards
void motorBackward() {
  analogWrite(motorLogicLeftPin1, pwmDutyCycle);
  analogWrite(motorLogicRightPin1, pwmDutyCycle);
  analogWrite(motorLogicLeftPin2, 0);
  analogWrite(motorLogicRightPin2, 0);
}
// Left
void motorLeft() {
  analogWrite(motorLogicLeftPin1, pwmDutyCycle);
  analogWrite(motorLogicRightPin1, 0);
  analogWrite(motorLogicLeftPin2, 0);
  analogWrite(motorLogicRightPin2, pwmDutyCycle);
}
// Right
void motorRight() {
  analogWrite(motorLogicLeftPin1, 0);
  analogWrite(motorLogicRightPin1, pwmDutyCycle);
  analogWrite(motorLogicLeftPin2, pwmDutyCycle);
  analogWrite(motorLogicRightPin2, 0);
}

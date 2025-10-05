#include <Stepper.h>

// Correct steps per revolution for 28BYJ-48 with 64:1 gear reduction
const int stepsPerRevolution = 2048;

// Define pins connected to ULN2003 driver
const int in1Pin = 8;
const int in2Pin = 9;
const int in3Pin = 10;
const int in4Pin = 11;

// Create Stepper object (pin order important for 28BYJ-48)
Stepper myStepper(stepsPerRevolution, in1Pin, in3Pin, in2Pin, in4Pin);

void setup() {
  Serial.begin(9600);
  myStepper.setSpeed(10); // motor speed in RPM
  
  Serial.println("Stepper Motor Control Ready!");
  Serial.println("Enter command: rotate <degrees>");
  Serial.println("Example: rotate 180   or   rotate -270");
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n'); // read until newline
    
    command.trim(); // remove spaces/newlines
    
    if (command.startsWith("rotate")) {
      // Extract angle after the word "rotate"
      int angle = command.substring(6).toInt();
      
      // Convert angle to steps
      long steps = (long)angle * stepsPerRevolution / 360;
      
      // Rotate motor
      myStepper.step(steps);
      
      // Feedback
      Serial.print("Rotated ");
      Serial.print(angle);
      Serial.println(" degrees");
    } else {
      Serial.println("Invalid command. Use: rotate <degrees>");
    }
  }
}

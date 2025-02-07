// #include <Servo.h>
#include <ESP32Servo.h>

// Create Servo objects for 6 servos
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

#define MIN -45
#define MAX 45

const byte numChars = 50;
char receivedChars[numChars];
char tempChars[numChars]; // Temporary array for use when parsing

float ANGLE[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}; // Array to store angles
boolean newData = false;  // Flag for new data

void setup() {
  // Attach each servo to the corresponding pin
  servo1.attach(5);  // Example pin numbers, change as needed
  servo2.attach(18);
  servo3.attach(19);
  servo4.attach(21);
  servo5.attach(22);
  servo6.attach(23);

  Serial.begin(38400);
  Serial.println("Yash's Stewart Platform Program: Send data in form of <Angles, 12.1, 10.1, 23.1, 12.0, 25.184, 150.1>");
}

void loop() {
  recvWithStartEndMarkers();
  if (newData == true) {
    strcpy(tempChars, receivedChars);
    parseData();
    newData = false;
  }

  //showAngles();

  // Map the angles to PWM signals for the servos
  servo1.write(90.0 - constrain(ANGLE[0], MIN, MAX));
  servo2.write(90.0 + constrain(ANGLE[1], MIN, MAX));
  servo3.write(90.0 - constrain(ANGLE[2], MIN, MAX));
  servo4.write(90.0 + constrain(ANGLE[3], MIN, MAX));
  servo5.write(90.0 - constrain(ANGLE[4], MIN, MAX));
  servo6.write(90.0 + constrain(ANGLE[5], MIN, MAX));
  //constrain()
}

// Parse the data received from the PC
void parseData() {
  char * strtokIndx;
  strtokIndx = strtok(tempChars, ",");
  strtokIndx = strtok(NULL, ",");
  ANGLE[0] = atof(strtokIndx);
  
  strtokIndx = strtok(NULL, ",");
  ANGLE[1] = atof(strtokIndx);
  
  strtokIndx = strtok(NULL, ",");
  ANGLE[2] = atof(strtokIndx);
  
  strtokIndx = strtok(NULL, ",");
  ANGLE[3] = atof(strtokIndx);
  
  strtokIndx = strtok(NULL, ",");
  ANGLE[4] = atof(strtokIndx);
  
  strtokIndx = strtok(NULL, ",");
  ANGLE[5] = atof(strtokIndx);
}

// Receive data with start and end markers
void recvWithStartEndMarkers() {
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (recvInProgress == true) {
      if (rc != endMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      }
      else {
        receivedChars[ndx] = '\0'; // terminate the string
        recvInProgress = false;
        ndx = 0;
        newData = true;
      }
    }
    else if (rc == startMarker) {
      recvInProgress = true;
    }
  }
}

// Display the angles
void showAngles() {
  Serial.print("Angles: ");
  for (int i = 0; i < 6; i++) {
    Serial.print(ANGLE[i]);
    if (i < 5) Serial.print(", ");
  }
  Serial.println();
}

#include <Wire.h>
#include <FirebaseArduino.h>

// Firebase configuration
#define FIREBASE_HOST "your-firebase-project.firebaseio.com"
#define FIREBASE_AUTH "your-firebase-auth-token"

// Analog input pins
int glucoinput1 = 0;
int glucoinput2 = 1;

// Other variables
int differential_data;
unsigned long int avgValue;
float volt_gluco;
float gluco;
float gluco_mmol;

void setup() {
  Serial.begin(9600);

  // Set up Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  pinMode(glucoinput1, INPUT);
  pinMode(glucoinput2, INPUT);
}

void loop() {
  // Read sensor values
  differential_data = chan_diff();

  for (int i = 0; i < 10; i++) {
    // Additional processing if needed
    delay(10);
  }

  for (int i = 0; i < 9; i++) {
    // Additional processing if needed
  }

  avgValue = 0;
  for (int i = 2; i < 8; i++)
    avgValue += buf[i];

  volt_gluco = avgValue * 5.0 / 1023.0;
  gluco = (volt_gluco - 2.6835) / 0.00185;
  gluco_mmol = gluco / 18;

  // Send data to Firebase
  sendDataToFirebase();

  delay(5000); // Wait for 5 seconds before sending the next data
}

int chan_diff() {
  analogRead(glucoinput1);
  delay(10);
  int ch1 = analogRead(glucoinput1);
  analogRead(glucoinput2);
  delay(10);
  int ch2 = analogRead(glucoinput2);
  ch1 += analogRead(glucoinput1);
  ch1 >>= 1;
  return ch1 - ch2;
}

void sendDataToFirebase() {
  // Create a path in your Firebase Realtime Database
  String path = "/glucose_data";

  // Set the glucose level values
  Firebase.setFloat(path + "/gluco_mgdl", gluco);
  Firebase.setFloat(path + "/gluco_mmol", gluco_mmol);

  // Print the sent values to Serial Monitor
  Serial.println("Data sent to Firebase:");
  Serial.print("Glucose level (mg/dL): ");
  Serial.println(gluco);
  Serial.print("Glucose level (mmol/L): ");
  Serial.println(gluco_mmol);
}


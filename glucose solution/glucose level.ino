#include <Wire.h>

int glucoinput1 = 0;
int glucoinput2 = 1;
int differential_data;
int push_button = 4;
int buttonval = 0;
int state = 0;

unsigned long int avgValue;  // Store the average value of the sensor feedback
float volt_gluco;             // Voltage generated from the reaction
float gluco;                  // Glucose level in mg/dL
float gluco_mmol;             // Glucose level in mmol/L

void setup() {
  Serial.begin(9600);
  pinMode(push_button, INPUT);
}

void loop() {
  buttonval = digitalRead(push_button);

  if (state == 0) {
    if (buttonval == 0) {
      delay(1000);
      state = 1;
    }
  } else if (state == 1) {
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

    if (avgValue >= 570 && avgValue <= 670) {
      state = 2;
    }
  } else if (state == 2) {
    state = 3;
  } else if (state == 3) {
    Serial.print("Glucose level (mg/dL): ");
    Serial.println(gluco);        // Output glucose level in mg/dL

    Serial.print("Glucose level (mmol/L): ");
    Serial.println(gluco_mmol);   // Output glucose level in mmol/L

    delay(2000);
  }
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


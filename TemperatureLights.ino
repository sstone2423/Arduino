const int sensorPin = A0;
const float baselineTemp = 20.0;
const int redLEDpin = 9;
const int blueLEDpin = 10;
const int greenLEDpin = 11;
int sensorVal = 0;
int redValue = 0;
int blueValue = 100;
int greenValue = 0;
float tempAverage = 21.0;
float totalTemp = 0.0;
int totalTemps = 0;
float temporaryTemp;

void setup() {
  // Set serial port speed
  Serial.begin(9600);
  
  // Set pin numbers
  for(int pinNumber = 9; pinNumber < 12; pinNumber++){
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
  }
}

void loop() {
  // Store sensor value
  sensorVal = analogRead(sensorPin);
  delay(5);
  
  // Print sensor value
  Serial.print("Sensor Value: ");
  Serial.print(sensorVal);
  
  // Convert the ADC reading to voltage
  float voltage = (sensorVal / 1024.0) * 5.0;
  
  // Print sensor voltage
  Serial.print(", Volts: ");
  Serial.print(voltage);
  
  // Create and convert temperature into Celsius
  float temperature = (voltage - .5) * 100;
  Serial.print(", degrees C: ");
  Serial.println(temperature);

  // Print new color values
  Serial.print("Mapped sensor values:\tRed: ");
  Serial.print(redValue);
  Serial.print("\t Blue: ");
  Serial.print(blueValue);
  Serial.print("\t Green: ");
  Serial.println(greenValue);
  
  // If the total count of temperatures is less than 5, increment the counter and average
  if(totalTemps < 5){
    totalTemps++;
    totalTemp += temperature;
    tempAverage = totalTemp / totalTemps;
     // If temp average is greater than baseline, show blue
    if(tempAverage > baselineTemp && tempAverage < baselineTemp + 4.5) {
      redValue = 0;
      greenValue = 0;
      blueValue = 100;
    } else if(tempAverage > baselineTemp + 4.5){ // change to red
      redValue = 100;
      greenValue = 0;
      blueValue = 0;
    }
  } else { // If the total count of temperatures is 5+, reset the totalTemps count, totalTemp sum, and tempAverage
    totalTemps = 0;
    totalTemp = 0;
    temporaryTemp = tempAverage; // Set a temporary variable to save the previous tempAverage while it resets in the next loop iteration
    tempAverage = 0;
     // If temp average is greater than baseline, show blue
    if(temporaryTemp > baselineTemp && temporaryTemp < baselineTemp + 4.5) {
      redValue = 0;
      greenValue = 0;
      blueValue = 100;
    } else if(temporaryTemp > baselineTemp + 4.5){ // change to red
      redValue = 100;
      greenValue = 0;
      blueValue = 0;
    }
  }

  Serial.print("Total number of temps: ");
  Serial.println(totalTemps);
  Serial.print("Total temperature sum: ");
  Serial.println(totalTemp);
  Serial.print("Temp average: ");
  Serial.println(tempAverage);
  
  // Change the LEDpin values
  analogWrite(redLEDpin, redValue);
  analogWrite(greenLEDpin, greenValue);
  analogWrite(blueLEDpin, blueValue);
}

// Libraries for controlling the stepper motor and the DHT sensor
#include <AccelStepper.h>
#include "DHT.h"

// Variables for the pin # and the DHT type (I am using DHT 11)
#define DHTPIN 2
#define DHTTYPE DHT11

// DHT library setup with pin # and type of DHT sensor
DHT dht(DHTPIN, DHTTYPE);

int n = 0;
float avg = 0;

// Setting up the pins that I am using on the microcontroller
AccelStepper stepper(AccelStepper::HALF4WIRE,
                     7, 5, 6, 4);


 // USER SETS DESIRED TEMPERATURE HERE
  int IdealTemp = 75;

  // Setting the reading confirmation variables
  int LowerCounter = 0;
  int RaiseCounter = 0;

  // Setting the default as lowered; This tells the microcontroller whether to raise or lower the blinds
  bool raised = false;
  bool lowered = false;

void setup() {

  // Stepper motor max speed/acceleration
  stepper.setMaxSpeed(1500);
  stepper.setAcceleration(500);

  // Serial monitor baud 9600
  Serial.begin(9600);
  // Setup the dht sensor
  dht.begin();
}

void loop() {

  Serial.print("RaiseCounter: ");
  Serial.println(RaiseCounter);
  Serial.print("LowerCounter: ");
  Serial.println(LowerCounter);  
  Serial.print("Current pos: ");
  Serial.println(stepper.currentPosition());

  stepper.run();

  delay(1500);

// Setting the variable to whatever the DHT sensor reads 

  // Farenheit reading
    float temperature = dht.readTemperature(true);

  // Celsius reading
    // float temperature = dht.readTemperature();


  if (isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Printing the temperature read by the DHT sensor
  Serial.print("\nTemperature: ");
  Serial.print(temperature);
  Serial.print("°\n");

  n += 1; 
  avg += temperature;
  Serial.print("Average Temp: ");
  Serial.println(avg / n);

  // If the temperature is higher than the ideal temp, the system will attempt to lower the blinds; If the temp is lower than the ideal temp, the system will attempt to raise the blinds
   if (temperature >= IdealTemp) {
      LowerCounter += 1;
      RaiseCounter = 0;
      //                                                                                                                   LOWER BLIND COUNTER
    } else{ 
      RaiseCounter += 1;
      LowerCounter = 0;
      //                                                                                                                   RAISE BLIND COUNTER
   }


  // Require several confirmation readings before lowering/raising the blinds
  if (RaiseCounter > 3){
    Serial.println("Raising Blinds");
        stepper.moveTo(16384);
        stepper.runToPosition();
        lowered = false;
        raised = true;  
        RaiseCounter = 0;  

  } else if (LowerCounter > 3){
    Serial.println("Lowering Blinds");
    stepper.moveTo(0);
    stepper.runToPosition();
    lowered = true;
    raised = false;
    LowerCounter = 0;
  }

  delay(5000);
  
}

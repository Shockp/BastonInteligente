#include <Arduino.h>
#include "../../src/Config/Config.h"
#include "../../src/Actuators/VibrationAlert.h"
#include "../../src/Communication/SMSCommunicator.h"

// Instantiate with Mock/Test interfaces
VibrationAlert vibrationAlert(PIN_VIBRATION);
SMSCommunicator smsCommunicator(Serial); // Inject Serial to see AT commands

void setup() {
    Serial.begin(9600);
    Serial.println("--- Starting Smart Cane Simulation ---");
    
    // Initialize modules
    vibrationAlert.init();
    smsCommunicator.init();
    
    Serial.println("Modules Initialized.");
    Serial.println("--------------------------------------");
}

void loop() {
    // --- Scenario 1: Obstacle Approach ---
    Serial.println("\n[Scenario 1] Obstacle Approach Simulation");
    
    long testDistances[] = {250, 150, 50, 10};
    
    for (int i = 0; i < 4; i++) {
        long dist = testDistances[i];
        Serial.print("Distance: ");
        Serial.print(dist);
        Serial.println(" cm");
        
        // Simulate running for 1 second at this distance
        unsigned long startTime = millis();
        int vibrationCount = 0;
        bool lastState = false;
        
        while (millis() - startTime < 1000) {
            vibrationAlert.update(dist);
            bool currentState = vibrationAlert.getMotorState();
            
            if (currentState != lastState && currentState == true) {
                vibrationCount++;
                Serial.print("."); // Visual indicator of pulse
            }
            lastState = currentState;
            delay(10);
        }
        Serial.println();
        Serial.print("Vibration Pulses in 1s: ");
        Serial.println(vibrationCount);
    }

    // --- Scenario 2: Emergency SOS ---
    Serial.println("\n[Scenario 2] Emergency Button Pressed");
    Serial.println("Simulating Button Press...");
    
    // Simulate GPS coordinates
    double fakeLat = 40.416775;
    double fakeLon = -3.703790;
    
    Serial.println("Sending SOS...");
    smsCommunicator.sendSOS(fakeLat, fakeLon);
    
    Serial.println("\n--- Simulation Complete ---");
    while(1); // Stop
}

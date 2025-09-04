#include <Servo.h>

// GPIO pin definitions
#define RAIN_IR_PIN 0    // GPIO0 = D3 (IR sensor D0/OUT, connected to HW-028)
#define SERVO_PIN   5    // GPIO5 = D1 (Servo)

Servo wiperServo;

bool wiperActive = false;
unsigned long lastWipeTime = 0;
unsigned long wipeInterval = 2000;  
unsigned long signalStartTime = 0;  
bool signalLow = false;             
const unsigned long RAIN_THRESHOLD = 3000;  
const unsigned long DEBOUNCE_TIME = 50;    

void setup() {
  Serial.begin(9600);
  pinMode(RAIN_IR_PIN, INPUT);
  wiperServo.attach(SERVO_PIN);
  wiperServo.write(90);  
  
  Serial.println("Smart Wiper Initialized");
}

void loop() {
  static int lastSignalState = HIGH;
  int signalState = digitalRead(RAIN_IR_PIN); 

  // Debounce signal
  static unsigned long lastChangeTime = 0;
  if (signalState != lastSignalState && millis() - lastChangeTime > DEBOUNCE_TIME) {
    lastSignalState = signalState;
    lastChangeTime = millis();
  }

  // Debug output
  Serial.print("Signal (D3): ");
  Serial.println(signalState == LOW ? "RAIN OR OBSTACLE" : "CLEAR");

  // Track signal duration
  if (signalState == LOW && !signalLow) {
    signalLow = true;
    signalStartTime = millis();
  } else if (signalState == HIGH && signalLow) {
    signalLow = false;
  }

  if (signalLow) {
    unsigned long signalDuration = millis() - signalStartTime;
    
    if (signalDuration >= RAIN_THRESHOLD) {  // Persistent LOW = rain
      if (!wiperActive) {
        wiperActive = true;
        Serial.println("Rain detected! Activating wiper.");
      }
      if (millis() - lastWipeTime >= wipeInterval) {
        executeWipe();
        lastWipeTime = millis();
      }
    } else {  // Brief LOW = obstacle
      if (wiperActive) {
        wiperActive = false;
        wiperServo.write(90);
        Serial.println("Obstacle detected! Wiper paused.");
      }
    }
  } else {  // Signal HIGH = no rain or obstacle
    if (wiperActive) {
      wiperActive = false;
      Serial.println("No rain or obstacle. Stopping wiper.");
      wiperServo.write(90);
    }
  }
  delay(100);  // Reduced delay for responsiveness
}

void executeWipe() {
  Serial.println("Executing wipe...");
  wiperServo.write(175); delay(600);  // Simplified for lower IRAM
  wiperServo.write(5);   delay(600);
  wiperServo.write(90);  delay(600);
  Serial.println("Wipe complete!");
}
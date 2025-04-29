#include <math.h>
#include <SPI.h>
#include <Wire.h>
#include <LoRa.h>

#define LORA_SS 53
#define LORA_RST 9
#define LORA_DIO0 8

int rad;
int degree;

int motor1IN1 = 29;  // Connect to D2
int motor1IN2 = 31;  // Connect to D3
int motor1PWM = 11; // Connect to D9 for PWM

int motor2IN1 = 33;  // Connect to D5 NOT FUCTIONING
int motor2IN2 = 35;  // Connect to D6
int motor2PWM = 11; // Connect to D10 for PWM

int motor3IN1 = 32;  // Connect to D2
int motor3IN2 = 34;  // Connect to D3
int motor3PWM = 13; // Connect to D9 for PWM

int motor4IN1 = 28;  // Connect to D5
int motor4IN2 = 30;  // Connect to D6
int motor4PWM = 12; // Connect to D10 for PWM

byte localAddress = 0xBB;

// Define dead zone threshold
int deadZoneX = 20;  // Adjust this based on the tolerance for small variations

unsigned long lastDataReceivedTime = 0;
const unsigned long timeoutPeriod = 5000;

void setup() {
  pinMode(LORA_SS, OUTPUT);
  digitalWrite(LORA_SS, HIGH);

  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);

  Serial.begin(9600);

  pinMode(motor1IN1, OUTPUT);
  pinMode(motor1IN2, OUTPUT);
  pinMode(motor1PWM, OUTPUT);

  pinMode(motor2IN1, OUTPUT);
  pinMode(motor2IN2, OUTPUT);
  pinMode(motor2PWM, OUTPUT);

  pinMode(motor3IN1, OUTPUT);
  pinMode(motor3IN2, OUTPUT);
  pinMode(motor3PWM, OUTPUT);

  pinMode(motor4IN1, OUTPUT);
  pinMode(motor4IN2, OUTPUT);
  pinMode(motor4PWM, OUTPUT);

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed. Check your connections. Resetting...");
    delay(1);                    // Add a delay to allow the message to be printed
    asm volatile("  jmp 0");      // Perform a software reset
  }
  else{
    Serial.println("LoRa init succeeded.");

  }
  
}

void loop() {
  int packetSize = LoRa.parsePacket();

  if (packetSize) {
    byte sender = LoRa.read();
    byte recipient = LoRa.read();
    byte msgId = LoRa.read();
    byte length = LoRa.read();

    String receivedMessage = "";

    while (LoRa.available()) {
      receivedMessage += (char)LoRa.read();
    }

    if (recipient == localAddress) {
      Serial.println("Received message from sender " + String(sender));
      Serial.println("Message ID: " + String(msgId));
      Serial.println("Message length: " + String(length));
      Serial.println("Received message: " + receivedMessage);

      // Extract joystick values from the received message
      int commaIndex1 = receivedMessage.indexOf(',');
      int joyValX1 = receivedMessage.substring(0, commaIndex1).toInt();
      int joyValY1 = receivedMessage.substring(commaIndex1 + 1).toInt();

      int commaIndex2 = receivedMessage.indexOf(',', commaIndex1 + 1);
      int commaIndex3 = receivedMessage.indexOf(',', commaIndex2 + 1);
      int joyValX2 = receivedMessage.substring(commaIndex2 + 1, commaIndex3).toInt();
      int joyValY2 = receivedMessage.substring(commaIndex3 + 1).toInt();

      rad = (atan2(joyValX1, joyValY1));
      degree = rad * 180 / PI;
      //Serial.println(degree);
      Serial.println(joyValX1);
      Serial.println(joyValY1);
      Serial.println(joyValX2);
      Serial.println(joyValY2);


      // Forward
      if ((joyValX1 < -30) && (degree > -135) && (degree < -45)) {
        analogWrite(motor1PWM, map(joyValX1, 0, -526, 60, 255));
        digitalWrite(motor1IN1, HIGH);
        digitalWrite(motor1IN2, LOW);

        analogWrite(motor2PWM, map(joyValX1, 0, -500, 60, 255));
        digitalWrite(motor2IN1, HIGH);
        digitalWrite(motor2IN2, LOW);

        // Backward
      } else if ((joyValX1 > 30) && (degree > 45) && (degree < 135)) {
        analogWrite(motor1PWM, map(joyValX1, 0, 497, 60, 255));
        digitalWrite(motor1IN1, HIGH);
        digitalWrite(motor1IN2, LOW);

        analogWrite(motor2PWM, map(joyValX1, 0, 497, 60, 255));
        digitalWrite(motor2IN1, HIGH);
        digitalWrite(motor2IN2, LOW);
      // Spin Left
      } else if ((joyValY1 > 30) && (degree > -45) && (degree < 45)) {
        analogWrite(motor1PWM, map(joyValY1, 0, 506, 60, 255));
        digitalWrite(motor1IN1, HIGH);
        digitalWrite(motor1IN2, LOW);

        analogWrite(motor2PWM, map(joyValY1, 0, 506, 60, 255));
        digitalWrite(motor2IN1, HIGH);
        digitalWrite(motor2IN2, LOW);

        // Spin Right
      } else if ((joyValY1 < -30) && (degree > 114) || (degree < -136)) {
        analogWrite(motor1PWM, map(joyValY1, 0, -517, 60, 255));
        digitalWrite(motor1IN1, HIGH);
        digitalWrite(motor1IN2, LOW);

        analogWrite(motor2PWM, map(joyValY1, 0, -517, 60, 255));
        digitalWrite(motor2IN1, HIGH);
        digitalWrite(motor2IN2, LOW);

      } else if (joyValX2 < -50) {
        analogWrite(motor3PWM, map(joyValX2, 0, -514, 60, 255));
        digitalWrite(motor3IN1, HIGH);
        digitalWrite(motor3IN2, LOW);

        analogWrite(motor4PWM, map(joyValX2, 0, -514, 60, 255));
        digitalWrite(motor4IN1, HIGH);
        digitalWrite(motor4IN2, LOW);

      } else if (joyValX2 > 50) {
        analogWrite(motor3PWM, map(joyValX2, 0, 520, 60, 255));
        digitalWrite(motor3IN1, HIGH);
        digitalWrite(motor3IN2, LOW);

        analogWrite(motor4PWM, map(joyValX2, 0, 509, 60, 255));
        digitalWrite(motor4IN1, HIGH);
        digitalWrite(motor4IN2, LOW);

      } else {
        digitalWrite(motor1IN1, LOW);
        digitalWrite(motor1IN2, LOW);

        digitalWrite(motor2IN1, LOW);
        digitalWrite(motor2IN2, LOW);

        digitalWrite(motor3IN1, LOW);
        digitalWrite(motor3IN2, LOW);

        digitalWrite(motor4IN1, LOW);
        digitalWrite(motor4IN2, LOW);
      }
      lastDataReceivedTime = millis();

      Serial.println();
    }
  }

  // Check for timeout and reset the Arduino if needed
  if (millis() - lastDataReceivedTime > timeoutPeriod) {
    Serial.println("No data received for a while. Resetting...");
    delay(25);                    // Add a delay to allow the message to be printed
    asm volatile("  jmp 0");      // Perform a software reset
  }

  delay(50);  // Adjust the delay based on your application needs
}


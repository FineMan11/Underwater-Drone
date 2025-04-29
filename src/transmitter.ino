#include <SPI.h>
#include <Wire.h>
#include <LoRa.h>

int joyX1 = A0;
int joyY1 = A1;
int joyX2 = A2;
int joyY2 = A3;

int joyValX1;
int joyValY1;
int joyValX2;
int joyValY2;

String outgoing;

byte msgCount = 0;
byte localAddress = 0xBB;
byte destination = 0xFF;

unsigned long lastDataSentTime = 0;
const unsigned long timeoutPeriod = 5000;

void setup() {
  Serial.begin(9600);

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed. Check your connections. Resetting...");
    delay(25);
    asm volatile("  jmp 0");
  }

  Serial.println("LoRa init succeeded.");
}

void loop() {
  joyValX1 = analogRead(joyX1);
  joyValY1 = analogRead(joyY1);
  joyValX2 = analogRead(joyX2);
  joyValY2 = analogRead(joyY2);

  // Subtract 500 from both X and Y values
  joyValX1 -= 508;
  joyValY1 -= 500;
  joyValX2 -= 498;
  joyValY2 -= 493;

  // Construct the message with modified values
  outgoing = String(joyValX1) + "," + String(joyValY1) + "," + String(joyValX2) + "," + String(joyValY2);

  // Send the message
  sendMessage(outgoing);
  Serial.println("Sending " + outgoing);

  // Reset the timer for data transmission
  lastDataSentTime = millis();

  delay(80);

  // Check for timeout and reset the Arduino if needed
  if (millis() - lastDataSentTime > timeoutPeriod) {
    Serial.println("No data sent for a while. Resetting...");
    delay(25);
    asm volatile("  jmp 0");
  }
}

void sendMessage(String outgoing) {
  LoRa.beginPacket();
  LoRa.write(destination);
  LoRa.write(localAddress);
  LoRa.write(msgCount);
  LoRa.write(outgoing.length());

  for (int i = 0; i < outgoing.length(); i++) {
    LoRa.write(outgoing[i]);
  }

  LoRa.endPacket();
  msgCount++;
}

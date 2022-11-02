#include <SoftwareSerial.h>

const byte rxPin = 10;
const byte txPin = 14;
const uint16_t BAUDRATE = 9600;
char c = ' ';
String command;

SoftwareSerial SerialBT = SoftwareSerial(rxPin, txPin);

void setup() {
  // Define pin modes for rxPin and txPin
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  Serial.begin(BAUDRATE);
  SerialBT.begin(BAUDRATE);
  delay(500);
  Serial.println("Enter AT commands:");
}

void loop() {
  if(SerialBT.available()) {
    c = SerialBT.read();
    Serial.print(c);
  }
  if(Serial.available()) {
    // Read user input
    c = Serial.read();
    // Do not send newline ('\n') and/or carriage return ('\r') characters
    if(c != 10 && c != 13) {
      SerialBT.print(c);
      command += c;
    }
    if (c == 10) {
      // Print sent command
      Serial.print("\r\nCommand: " + command);
      command = "";
      // Create carriage return and prefix new line with '> '
      Serial.print("\r\n> ");
    }
  }
}

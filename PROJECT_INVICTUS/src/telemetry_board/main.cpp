#include <Arduino.h>
#include <packet.h>
#include <commands.h>
#include <communications.h>

#define LED_PIN 2

void communications_task() {
  Serial.println("Communications task started");
  while (1) {
    Packet packet;
    CommunicationStatus read_status = read_packet(&packet, INTERFACE_UART);
  }
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  //communications_task();
  pinMode(LED_PIN, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);
  delay(1000);
}


#include <Arduino.h>
#include <packet.h>
#include <commands.h>
#include <communications.h>

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
  communications_task();
}

void loop()
{

}


#include <Arduino.h>

// custom lib includes
#include <packet.h>
#include <communications.h>
#include <commands.h>
#include "state_machine.h"

RocketState state = IDLE;

void setup()
{
   
}

void loop()
{
  Packet packet;
  RocketState cmd_state, event_state; 
  CommunicationStatus status = read_packet(&packet, INTERFACE_UART);
  if(status == PACKET_OK)
  {
    cmd_state = get_next_state(state, (cmd_type)packet.contents.fields.command);
  } 
}


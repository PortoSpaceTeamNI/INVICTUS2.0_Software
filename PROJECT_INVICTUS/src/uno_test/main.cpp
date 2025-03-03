#include <Arduino.h>
#include <packet.h>
#include <commands.h>

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200); 
}

void loop()
{
  if (Serial.available() > 0)
  {
    byte incomingByte = Serial.read();
    static Packet packet;
    static packet_state state = SYNC;
    static byte payload[MAX_PAYLOAD_SIZE];
    static byte payload_index = 0;

    switch (state)
    {
    case SYNC:
      if (incomingByte == START_BYTE)
      {
        packet.fields.start_byte = incomingByte;
        state = CMD;
      }
      break;
    case CMD:
      packet.fields.command = incomingByte;
      state = TARGET_ID;
      break;
    case TARGET_ID:
      packet.fields.target_id = incomingByte;
      state = SENDER_ID;
      break;
    case SENDER_ID:
      packet.fields.sender_id = incomingByte;
      state = SIZE;
      break;
    case SIZE:
      packet.fields.payload_length = incomingByte;
      payload_index = 0;
      state = H_CRC1;
      break;
    case H_CRC1:
      packet.fields.h_crc1 = incomingByte;
      state = H_CRC2;
      break;
    case H_CRC2:
      packet.fields.h_crc2 = incomingByte;
      state = PAYLOAD;
      break;
    case PAYLOAD:
      if (payload_index < packet.fields.payload_length)
      {
        packet.fields.payload[payload_index++] = incomingByte;
        if (payload_index == packet.fields.payload_length)
        {
          state = CRC1;
        }
      }
      break;
    case CRC1:
      packet.fields.crc1 = incomingByte;
      state = CRC2;
      break;
    case CRC2:
      packet.fields.crc2 = incomingByte;
      // Packet received completely, process it
      Serial.print("Received Packet: ");
      for (size_t i = 0; i < sizeof(packet.raw); i++)
      {
        Serial.write(packet.raw[i]);
      }
      // Acknowledge the packet
      Packet ack_packet;
      create_packet(packet.fields.command + 1, packet.fields.sender_id, packet.fields.target_id, 0, NULL, &ack_packet);
      Serial.print("Acknowledgment Packet: ");
      for (size_t i = 0; i < sizeof(ack_packet.raw); i++)
      {
        Serial.write(ack_packet.raw[i]);
      }
      state = SYNC;
      break;
    }
  }
}


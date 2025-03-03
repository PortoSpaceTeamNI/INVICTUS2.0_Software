#include <packet.h>
#include <stdlib.h>

void create_packet(byte command, byte target_id, byte sender_id, byte payload_length, byte payload[], Packet *packet)
{
    // creates a packet with the given parameters
    packet->contents.fields.start_byte = START_BYTE;
    packet->contents.fields.version = PACKET_VERSION;
    packet->contents.fields.command = command;
    packet->contents.fields.target_id = target_id;
    packet->contents.fields.sender_id = sender_id;
    packet->contents.fields.payload_length = payload_length;
    for (size_t i = 0; i < payload_length; i++)
    {
        packet->contents.fields.payload[i] = payload[i];
    }
    // TODO: calculate the checksums
    packet->contents.fields.h_crc1 = 0xA5;
    packet->contents.fields.h_crc2 = 0xA5;
    packet->contents.fields.crc1 = 0x5A;
    packet->contents.fields.crc2 = 0x5A;
}
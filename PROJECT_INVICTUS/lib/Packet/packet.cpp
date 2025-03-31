#include <Arduino.h>
#include <stdlib.h>

#include <commands.h>
#include <packet.h>
#include <CRC.h>

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

/// @brief Fills buffer with the content of the packet (the payload is stored in memory with fixed size, but only the content should be transmitted)
/// @param packet the packet with the content
/// @param buffer the buffer to fill. ! Min Buffer Size = Max Payload Size !
/// @return 0 if OK, Non-zero otherwise
int packet_to_buffer(Packet *packet, byte buffer[]) {
    PacketFields fields = packet->contents.fields;
    buffer[0] = fields.start_byte;
    buffer[1] = fields.command;
    buffer[2] = fields.target_id;
    buffer[3] = fields.sender_id;
    buffer[4] = fields.version;
    buffer[5] = fields.payload_length;
    buffer[6] = fields.h_crc1;
    buffer[7] = fields.h_crc2;
    for (int i = 0; i < fields.payload_length; i++) {
        buffer[8 + i] = fields.payload[i];
    }
    buffer[8 + fields.payload_length] = fields.crc1;
    buffer[9 + fields.payload_length] = fields.crc2;
    return 0;
}

bool check_crc(Packet *packet)
{
    // check the packet's CRCs
    uint16_t crc1, crc2;
    crc1 = packet->contents.fields.crc1 << 8 | packet->contents.fields.crc2;
    crc2 = crc((byte *)packet->contents.raw, sizeof(packet->contents.raw) - 2);
    return (crc1 == crc2);
}

bool check_h_crc(Packet *packet)
{
    // check the packet's header CRCs
    uint16_t crc1, crc2;
    crc1 = packet->contents.fields.h_crc1 << 8 | packet->contents.fields.h_crc2;
    crc2 = crc((byte *)packet->contents.raw, HEADER_SIZE);
    return (crc1 == crc2);
}

//testing functions
void generate_mock_packet(Packet *packet)
{
    // Fill the buffer with a mock packet for testing
    randomSeed(millis());
    byte mock_command = random(0, cmd_size);
    byte mock_payload_size = rand() % MAX_PAYLOAD_SIZE;
    byte mock_payload[mock_payload_size];
    for (byte i = 0; i < mock_payload_size; i++)
    {
        mock_payload[i] = rand() % 255;
    }
    create_packet(mock_command, 0, 3, mock_payload_size, mock_payload, packet);
}
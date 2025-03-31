#include <packet.h>
#include <stdlib.h>
#include <commands.h>
#include <communications.h>

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
}

//testing functions
void generate_mock_packet(Packet *packet)
{
    // Fill the buffer with a mock packet for testing
    byte mock_command = (rand() % cmd_size);
    byte mock_payload_size = rand() % MAX_PAYLOAD_SIZE;
    byte mock_payload[mock_payload_size];
    for (byte i = 0; i < mock_payload_size; i++)
    {
        mock_payload[i] = rand() % 255;
    }
    create_packet(mock_command, ID_MC_Telemetry, ID_R_Telemetry, mock_payload_size, mock_payload, packet);
}
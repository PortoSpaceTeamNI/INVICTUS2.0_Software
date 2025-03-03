#include <Arduino.h>
#include <communications.h>
#include <packet.h>
#include <stdlib.h>

CommunicationStatus write_packet(Packet *packet, InterfaceType interface)
{
    // write the packet to the specified interface
    switch(interface)
    {
        case INTERFACE_LORA:
            break;
        case INTERFACE_RS485:
            break;
        case INTERFACE_UART:
            Serial.write(packet->contents.raw, sizeof(packet->contents.raw));
            break;
        default:
            return INTERFACE_NOT_FOUND;
    }
    return PACKET_OK;
}

CommunicationStatus read_packet(Packet *packet, InterfaceType interface)
{
    static PacketState states[interface_count] = {SYNC};
    
    PacketState *state = &states[interface];

    // read the packet from the specified interface
    switch(interface) 
    {
        case INTERFACE_LORA:
            break;
        case INTERFACE_RS485:
            break;
        case INTERFACE_UART:
            while (Serial.available() > 0)
            {
                byte incomingByte = Serial.read();
                Serial.println(*state);
                *state = parse_byte(*state, incomingByte, packet);
            }
            break;
        default:
            return INTERFACE_NOT_FOUND;
    }
    return PACKET_OK;
}

PacketState parse_byte(PacketState state, byte incomingByte, Packet *packet)
{
    switch (state)
    {
    case SYNC:
        if (incomingByte == START_BYTE)
        {
            state = CMD;
            memset(packet->contents.fields.payload, 0, sizeof(packet->contents.fields.payload));
            packet->payload_index = 0;
            packet->begin = clock();
        }
        break;
    case CMD:
        packet->contents.fields.command = incomingByte;
        state = TARGET_ID;
        break;
    case TARGET_ID:
        packet->contents.fields.target_id = incomingByte;
        state = SENDER_ID;
        break;
    case SENDER_ID:
        packet->contents.fields.sender_id = incomingByte;
        state = SIZE;
        break;
    case SIZE:
        packet->contents.fields.payload_length = incomingByte;
        state = H_CRC1;
        break;
    case H_CRC1:
        packet->contents.fields.h_crc1 = incomingByte;
        state = H_CRC2;
        break;
    case H_CRC2:
        packet->contents.fields.h_crc2 = incomingByte;
        if(check_h_crc(packet))
            state = PAYLOAD;
        else
            state = SYNC;
        break;
    case PAYLOAD:
        if (packet->contents.fields.payload_length > 0)
        {
            packet->contents.fields.payload[packet->payload_index++] = incomingByte;
            if (packet->payload_index >= packet->contents.fields.payload_length)
            {
                state = CRC1;
            }
        }
        break;
    case CRC1:
        packet->contents.fields.crc1 = incomingByte;
        state = CRC2;
        break;
    case CRC2:
        packet->contents.fields.crc2 = incomingByte;
        state = SYNC;
        break;
    }
    return state;
}

bool check_crc(Packet *packet) {
    // check the packet's CRCs
    uint16_t crc1, crc2;
    crc1 = packet->contents.fields.crc1 << 8 | packet->contents.fields.crc2;
    crc2 = crc((byte *)packet->contents.raw, sizeof(packet->contents.raw) - 2);
    return (crc1 == crc2);
}

bool check_h_crc(Packet *packet) {
    // check the packet's header CRCs
    uint16_t crc1, crc2;
    crc1 = packet->contents.fields.h_crc1 << 8 | packet->contents.fields.h_crc2;
    crc2 = crc((byte *)packet->contents.raw, HEADER_SIZE);
    return (crc1 == crc2);
}

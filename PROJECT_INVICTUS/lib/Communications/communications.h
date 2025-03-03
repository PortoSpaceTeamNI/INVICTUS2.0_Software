#ifndef COMMUNICATIONS_H
#define COMMUNICATIONS_H

#include <packet.h>
#include <CRC.h>

typedef enum {
    INTERFACE_LORA,
    INTERFACE_RS485,
    INTERFACE_UART,
    interface_count
} InterfaceType;

typedef enum {
    PACKET_OK,
    PACKET_ERROR,
    PACKET_TIMEOUT,
    PACKET_EMPTY,
    INTERFACE_NOT_FOUND,
} CommunicationStatus;

// write packet to the specified interface returning the status of the operation
CommunicationStatus write_packet(Packet *packet, InterfaceType interface);

// read packet from the specified interface returning the status of the operation and writing to the packet pointer
CommunicationStatus read_packet(Packet *packet, InterfaceType interface); 

PacketState parse_byte(PacketState state, byte incomingByte, Packet *packet);

bool check_crc(Packet *packet);
bool check_h_crc(Packet *packet);


#endif // COMMUNICATIONS_H
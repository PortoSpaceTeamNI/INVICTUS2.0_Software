#ifndef PACKET_H
#define PACKET_H

#include <stdint.h>

#define MAX_PACKET_SIZE 255 // 255 bytes is the maximum packet size
#define MAX_PAYLOAD_SIZE MAX_PACKET_SIZE - 10 // 10 bytes are used for the header and footer
#define HEADER_SIZE 6 // 8 - 2 bytes for the CRC
#define START_BYTE 0x55
#define PACKET_VERSION 0x01

typedef uint8_t byte; // easier to read than uint8_t
typedef unsigned long clock_t; // easier to read than unsigned long

typedef struct // __atribute__((packed)) // don't know if this is safe to use as it may cause invalid pointers and SIGSEV errors
// this struct is used to access the packet's fields
{
    byte start_byte, version;
    byte command, target_id, sender_id;
    byte payload_length;
    byte h_crc1, h_crc2;
    byte payload[MAX_PAYLOAD_SIZE];
    byte crc1, crc2;
} PacketFields;

typedef union
// being a union, raw and fields share the same memory space which allows for easy conversion between the two
{
    PacketFields fields;
    byte raw[sizeof(PacketFields)];
} PacketContents;

typedef struct
{
    PacketContents contents;
    clock_t begin;
    byte payload_index;
} Packet;

// Packet read/write state
typedef enum {
    SYNC = 0,
    CMD,
    TARGET_ID,
    SENDER_ID,
    SIZE,
    H_CRC1,
    H_CRC2,
    PAYLOAD,
    CRC1,
    CRC2,
    END
} PacketState;

void create_packet(byte command, byte target_id, byte sender_id, byte payload_length, byte payload[], Packet *packet);

#endif // PACKET_H
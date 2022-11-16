#ifndef _PKTFORMAT_H
#define _PKTFORMAT_H

#include <stdio.h>

//packet format [0xAA] [CMD_H]  [CMD_L] [Payload_Len]  [Payload .... ]

#define FRAME_MAX_LEN        512

#define PACKET_HEADER_LEN    4 // start + cmd_h + cmd_l + len
#define PAYLOAD_MAX_LEN      200
#define PACKET_MAX_LEN       (PAYLOAD_MAX_LEN + PACKET_HEADER_LEN)
#define PACKET_START         0xAA

#define ERR_NO_ERR           0 // No error
#define ERR_INV_FRAME        1 // invalid frame
#define ERR_OUT_OF_MEM       2 // cant aquire memory from system 
#define ERR_PKT_INV_LEN      3 // Invalid lenght of packet
#define ERR_PKT_INV_START    4 // invalid start byte for packet

// hold packet parameters
struct rec_packet_params
{
	uint16_t cmd;        // command id 
	uint8_t* payloadp;   // pointer to the payload in heap memory
	uint8_t len;         // payload len  
	uint8_t start;       // start byte
};

extern struct rec_packet_params rec_pkt_params;
////////////////////////////////////
int8_t is_pkt_valid();
#endif

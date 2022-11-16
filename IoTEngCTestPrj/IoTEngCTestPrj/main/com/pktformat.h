#ifndef _PKTFORMAT_H
#define _PKTFORMAT_H

#include <stdio.h>
/*
  1) Frame format: 
      [Start] [CMD_H]  [CMD_L] [Payload_Len]  [Payload .... ][EoF-1][EoF-2]
      
  2) Start byte is 0xAA (one byte)
  3) Command id is two bytes.
  4) Maximum payload is 200 bytes 
  5) Maximum packet length is limmited to 206 bytes
  6) End of frame indicator are two bytes [\r][\n]
*/
#define FRAME_MAX_LEN        512

#define PACKET_HEADER_LEN    4 // start + cmd_h + cmd_l + len
#define PAYLOAD_MAX_LEN      200
#define PACKET_FOOTER_LEN    2
#define PACKET_MAX_LEN       (PAYLOAD_MAX_LEN + PACKET_HEADER_LEN + PACKET_FOOTER_LEN)
#define PACKET_START         0xAA
#define PACKET_EOF1         0x0D   //   \r
#define PACKET_EOF2         0x0A    //  \n

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
void extract_packet_params(uint8_t* packet);
#endif

#ifndef _PKTRECEIVE_H
#define _PKTRECEIVE_H

#include <stdio.h>

// receive processflags
struct receive_packet_flags
{
	uint8_t block_rec : 1;  // block receive new packet, pervent override receive buffer
	uint8_t status : 1;   // final status of receive process true for completed and false for incompleted
	uint8_t free_mem : 1; // free allocated memory inside the receive process or not. to use buffer outside of the receive function
	uint8_t err_code : 4; // error code of receive process
};

extern struct receive_packet_flags rec_pkt_flags;


void init_receive_process_flags(bool FreeMemory);

#endif

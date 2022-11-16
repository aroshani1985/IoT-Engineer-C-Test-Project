#include "pktformat.h"

struct rec_packet_params rec_pkt_params;


// input packrt validation after decription
int8_t is_pkt_valid()
{
	if (rec_pkt_params.len > PACKET_MAX_LEN)
		return ERR_PKT_INV_LEN;
	
	if (rec_pkt_params.start != PACKET_START)
		return ERR_PKT_INV_START;		
		
	return ERR_NO_ERR;
}

void extract_packet_params(uint8_t* packet)
{
	rec_pkt_params.start = packet[0];
	rec_pkt_params.cmd = packet[1];
	rec_pkt_params.cmd <<= 8;
	rec_pkt_params.cmd |= packet[2];
	rec_pkt_params.len =  packet[3];
	rec_pkt_params.payloadp = packet + PACKET_HEADER_LEN;
}
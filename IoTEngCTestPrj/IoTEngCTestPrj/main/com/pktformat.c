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
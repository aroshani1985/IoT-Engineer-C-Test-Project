#include <stdint.h>
#include <stdbool.h>
#include "pktreceive.h"


struct receive_packet_flags rec_pkt_flags;

void init_receive_process_flags(bool FreeMemory)
{
	rec_pkt_flags.blok_rx = false;
	rec_pkt_flags.status = false;
	rec_pkt_flags.err_code = 0;
	rec_pkt_flags.free_mem = FreeMemory;
}


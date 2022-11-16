#include <stdint.h>
#include <stdbool.h>
#include "pktreceive.h"
#include "pktformat.h"


struct receive_packet_flags rec_pkt_flags;

// init receive flags before start receive. 
// to access allocated memoty after exit from function, set freememory to false;
void init_receive_process_flags(bool FreeMemory)
{
	rec_pkt_flags.block_rec = false;
	rec_pkt_flags.status = false;
	rec_pkt_flags.err_code = 0;
	rec_pkt_flags.free_mem = FreeMemory;
}
void free_receive_resources()
{
	if (rec_pkt_flags.err_code == 0 && rec_pkt_flags.free_mem != 0)
	{
		free(rec_pkt_params.payloadp - 4);
	}
}
void Communication_onDataReceived(uint8_t* packet, uint16_t lenght)
{
	//////////////////////////////////////// receive process starts from hear. pervent new receive or buffer override
	rec_pkt_flags.block_rec = true;
	///////////////////////////// decrypted packet length limit check
	if (lenght > FRAME_MAX_LEN) 
	{
		rec_pkt_flags.err_code = ERR_INV_FRAME;
		rec_pkt_flags.block_rec = false; // resume receive.
		return;
	}
	///////////////////////////////////// allocate memory from heap and verify allocation 
	uint8_t* _decrypt_buffer = malloc(lenght); 
	if (_decrypt_buffer == NULL) 
	{	
		rec_pkt_flags.err_code = ERR_OUT_OF_MEM;
		rec_pkt_flags.block_rec = false;   // resume receive.
		return;
	}
	///////////////////////////////////////

	///////////////////////////////////////
	rec_pkt_flags.status = true;   
	rec_pkt_flags.block_rec = false; // resume receive.
	/////////////////////////////////if you want to access this memory outside of this function, dont free here
	if (rec_pkt_flags.free_mem)
		free(_decrypt_buffer);
}
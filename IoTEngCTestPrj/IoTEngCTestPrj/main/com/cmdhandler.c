#include "cmdhandler.h"
#include "pktsend.h"
#include "pktformat.h"
#include "pktreceive.h"
#include "encdec.h"


// container for each command parameters
struct command_handle_params cmd_handle_params;

// array of functions, each functions related to one command
cmd_process *cmd_process_array[CMD_COUNT] = {
	cmd_000_process,
	cmd_001_process,
	cmd_002_process,
	cmd_003_process,
	cmd_004_process,
	cmd_005_process,
    cmd_006_process,
	cmd_007_process,
	cmd_008_process,
    cmd_009_process
};


void  CommandHandler_handle(uint16_t cmdid, uint8_t* payloadp)
{
	int i;
	uint16_t items_len_accumulator = 0;        //accumulate current items responce len 
	///////////////////////////////////////   //get the items of the current command
	cmd_process_array[cmdid](NULL, 0, NULL);
	if (cmd_handle_params.items_count == 0)   // if no item found, return, no need for reply
		return;
	////////////////////////////////////////////////////////
	Communication_openResponse();
	////////////////////////////////////////////////////
	uint8_t * _item_responce_buff = malloc(SEND_MAX_BUFF_LEN); 
	if (_item_responce_buff == NULL) 
	{	
		rec_pkt_flags.err_code = ERR_OUT_OF_MEM2;
		return;
	}
	///////////////////////////////////////////////////////////
	for (i = 1; i < cmd_handle_params.items_count; i++)
	{
		cmd_handle_params.curr_item = i;   
		cmd_process_array[cmdid](payloadp, i, _item_responce_buff + items_len_accumulator);
		items_len_accumulator += cmd_handle_params.curr_item_length;
		
		if ((items_len_accumulator + cmd_handle_params.next_item_length) >= SEND_MAX_BUFF_LEN)
		{
			uint8_t * _enc_buffer = malloc(items_len_accumulator); 
			if (_enc_buffer == NULL) 
			{
				rec_pkt_flags.err_code = ERR_OUT_OF_MEM3;
				return;
			}
			encrypt_decrypt_packet(_item_responce_buff, items_len_accumulator, _enc_buffer, false);
			Communication_sendData(_enc_buffer, items_len_accumulator);
			items_len_accumulator = 0;
			free(_enc_buffer);
		}
	}
	/////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////
	free(_item_responce_buff);	
	Communication_closeResponse();
}

// implementation of each command process function
void cmd_000_process(uint8_t* payloadp, uint16_t ItemIdx, uint8_t* responseDatap)
{
	if (ItemIdx > CMD_ID_000_ITEMS) 
	{
		// register error here
		cmd_handle_params.curr_item_length = 0;
		cmd_handle_params.next_item_length = 0;
		return;
	}
	switch (ItemIdx)
	{
	case 0:
		cmd_handle_params.items_count = (uint16_t) CMD_ID_000_ITEMS;
		cmd_handle_params.curr_item_length = 0;
		cmd_handle_params.next_item_length = 0;
		break;
		
	case CMD_ID_000_ITEMS:
		cmd_handle_params.curr_item_length = CMD_ITEM_FIX_LEN;
		cmd_handle_params.next_item_length = 0;
		break;
		
	default:
		cmd_handle_params.curr_item_length = CMD_ITEM_FIX_LEN;
		cmd_handle_params.next_item_length = CMD_ITEM_FIX_LEN;
		break;
	}
}
void cmd_001_process(uint8_t* payloadp, uint16_t ItemIdx, uint8_t* responseDatap)
{
	if (ItemIdx > CMD_ID_001_ITEMS) 
	{
		// register error here
		cmd_handle_params.curr_item_length = 0;
		cmd_handle_params.next_item_length = 0;
		return;
	}
	switch (ItemIdx)
	{
	case 0:
		cmd_handle_params.items_count = (uint16_t) CMD_ID_001_ITEMS;
		cmd_handle_params.curr_item_length = 0;
		cmd_handle_params.next_item_length = 0;
		break;
		
	case CMD_ID_001_ITEMS:
		cmd_handle_params.curr_item_length = CMD_ITEM_FIX_LEN;
		cmd_handle_params.next_item_length = 0;
		break;
		
	default:
		cmd_handle_params.curr_item_length = CMD_ITEM_FIX_LEN;
		cmd_handle_params.next_item_length = CMD_ITEM_FIX_LEN;
		break;
	}
}
void cmd_002_process(uint8_t* payloadp, uint16_t ItemIdx, uint8_t* responseDatap)
{
	if (ItemIdx > CMD_ID_002_ITEMS) 
	{
		// register error here
		cmd_handle_params.curr_item_length = 0;
		cmd_handle_params.next_item_length = 0;
		return;
	}
	switch (ItemIdx)
	{
	case 0:
		cmd_handle_params.items_count = (uint16_t) CMD_ID_002_ITEMS;
		cmd_handle_params.curr_item_length = 0;
		cmd_handle_params.next_item_length = 0;
		break;
		
	case CMD_ID_002_ITEMS:
		cmd_handle_params.curr_item_length = CMD_ITEM_FIX_LEN;
		cmd_handle_params.next_item_length = 0;
		break;
		
	default:
		cmd_handle_params.curr_item_length = CMD_ITEM_FIX_LEN;
		cmd_handle_params.next_item_length = CMD_ITEM_FIX_LEN;
		break;
	}
}
void cmd_003_process(uint8_t* payloadp, uint16_t ItemIdx, uint8_t* responseDatap)
{
	if (ItemIdx > CMD_ID_003_ITEMS) 
	{
		// register error here
		cmd_handle_params.curr_item_length = 0;
		cmd_handle_params.next_item_length = 0;
		return;
	}
	switch (ItemIdx)
	{
	case 0:
		cmd_handle_params.items_count = (uint16_t) CMD_ID_003_ITEMS;
		cmd_handle_params.curr_item_length = 0;
		cmd_handle_params.next_item_length = 0;
		break;
		
	case CMD_ID_003_ITEMS:
		cmd_handle_params.curr_item_length = CMD_ITEM_FIX_LEN;
		cmd_handle_params.next_item_length = 0;
		break;
		
	default:
		cmd_handle_params.curr_item_length = CMD_ITEM_FIX_LEN;
		cmd_handle_params.next_item_length = CMD_ITEM_FIX_LEN;
		break;
	}
}
void cmd_004_process(uint8_t* payloadp, uint16_t ItemIdx, uint8_t* responseDatap)
{
	if (ItemIdx > CMD_ID_004_ITEMS) 
	{
		// register error here
		cmd_handle_params.curr_item_length = 0;
		cmd_handle_params.next_item_length = 0;
		return;
	}
	switch (ItemIdx)
	{
	case 0:
		cmd_handle_params.items_count = (uint16_t) CMD_ID_004_ITEMS;
		cmd_handle_params.curr_item_length = 0;
		cmd_handle_params.next_item_length = 0;
		break;
		
	case CMD_ID_004_ITEMS:
		cmd_handle_params.curr_item_length = CMD_ITEM_FIX_LEN;
		cmd_handle_params.next_item_length = 0;
		break;
		
	default:
		cmd_handle_params.curr_item_length = CMD_ITEM_FIX_LEN;
		cmd_handle_params.next_item_length = CMD_ITEM_FIX_LEN;
		break;
	}
}
void cmd_005_process(uint8_t* payloadp, uint16_t ItemIdx, uint8_t* responseDatap)
{
	if (ItemIdx > CMD_ID_005_ITEMS) 
	{
		// register error here
		cmd_handle_params.curr_item_length = 0;
		cmd_handle_params.next_item_length = 0;
		return;
	}
	switch (ItemIdx)
	{
	case 0:
		cmd_handle_params.items_count = (uint16_t) CMD_ID_005_ITEMS;
		cmd_handle_params.curr_item_length = 0;
		cmd_handle_params.next_item_length = 0;
		break;
		
	case CMD_ID_005_ITEMS:
		cmd_handle_params.curr_item_length = CMD_ITEM_FIX_LEN;
		cmd_handle_params.next_item_length = 0;
		break;
		
	default:
		cmd_handle_params.curr_item_length = CMD_ITEM_FIX_LEN;
		cmd_handle_params.next_item_length = CMD_ITEM_FIX_LEN;
		break;
	}
}
void cmd_006_process(uint8_t* payloadp, uint16_t ItemIdx, uint8_t* responseDatap)
{
	if (ItemIdx > CMD_ID_006_ITEMS) 
	{
		// register error here
		cmd_handle_params.curr_item_length = 0;
		cmd_handle_params.next_item_length = 0;
		return;
	}
	switch (ItemIdx)
	{
	case 0:
		cmd_handle_params.items_count = (uint16_t) CMD_ID_006_ITEMS;
		cmd_handle_params.curr_item_length = 0;
		cmd_handle_params.next_item_length = 0;
		break;
		
	case CMD_ID_006_ITEMS:
		cmd_handle_params.curr_item_length = CMD_ITEM_FIX_LEN;
		cmd_handle_params.next_item_length = 0;
		break;
		
	default:
		cmd_handle_params.curr_item_length = CMD_ITEM_FIX_LEN;
		cmd_handle_params.next_item_length = CMD_ITEM_FIX_LEN;
		break;
	}
}
void cmd_007_process(uint8_t* payloadp, uint16_t ItemIdx, uint8_t* responseDatap)
{
	if (ItemIdx > CMD_ID_007_ITEMS) 
	{
		// register error here
		cmd_handle_params.curr_item_length = 0;
		cmd_handle_params.next_item_length = 0;
		return;
	}
	switch (ItemIdx)
	{
	case 0:
		cmd_handle_params.items_count = (uint16_t) CMD_ID_007_ITEMS;
		cmd_handle_params.curr_item_length = 0;
		cmd_handle_params.next_item_length = 0;
		break;
		
	case CMD_ID_007_ITEMS:
		cmd_handle_params.curr_item_length = CMD_ITEM_FIX_LEN;
		cmd_handle_params.next_item_length = 0;
		break;
		
	default:
		cmd_handle_params.curr_item_length = CMD_ITEM_FIX_LEN;
		cmd_handle_params.next_item_length = CMD_ITEM_FIX_LEN;
		break;
	}
}
void cmd_008_process(uint8_t* payloadp, uint16_t ItemIdx, uint8_t* responseDatap)
{
	if (ItemIdx > CMD_ID_008_ITEMS) 
	{
		// register error here
		cmd_handle_params.curr_item_length = 0;
		cmd_handle_params.next_item_length = 0;
		return;
	}
	switch (ItemIdx)
	{
	case 0:
		cmd_handle_params.items_count = (uint16_t) CMD_ID_008_ITEMS;
		cmd_handle_params.curr_item_length = 0;
		cmd_handle_params.next_item_length = 0;
		break;
		
	case CMD_ID_008_ITEMS:
		cmd_handle_params.curr_item_length = CMD_ITEM_FIX_LEN;
		cmd_handle_params.next_item_length = 0;
		break;
		
	default:
		cmd_handle_params.curr_item_length = CMD_ITEM_FIX_LEN;
		cmd_handle_params.next_item_length = CMD_ITEM_FIX_LEN;
		break;
	}
}
void cmd_009_process(uint8_t* payloadp, uint16_t ItemIdx, uint8_t* responseDatap)
{
	if (ItemIdx > CMD_ID_009_ITEMS) 
	{
		// register error here
		cmd_handle_params.curr_item_length = 0;
		cmd_handle_params.next_item_length = 0;
		return;
	}
	switch (ItemIdx)
	{
	case 0:
		cmd_handle_params.items_count = (uint16_t) CMD_ID_009_ITEMS;
		cmd_handle_params.curr_item_length = 0;
		cmd_handle_params.next_item_length = 0;
		break;
		
	case CMD_ID_009_ITEMS:
		cmd_handle_params.curr_item_length = CMD_ITEM_FIX_LEN;
		cmd_handle_params.next_item_length = 0;
		break;
		
	default:
		cmd_handle_params.curr_item_length = CMD_ITEM_FIX_LEN;
		cmd_handle_params.next_item_length = CMD_ITEM_FIX_LEN;
		break;
	}
}


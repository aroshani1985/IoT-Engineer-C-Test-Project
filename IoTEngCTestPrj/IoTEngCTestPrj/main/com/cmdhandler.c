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

// handle command with multiple items in response with limmted send buffer
void  CommandHandler_handle(uint16_t cmdid, uint8_t* payloadp)
{
	int i;
	uint16_t items_len_accumulator = 0;        //accumulate current items responce len 
	///////////////////////////////////////   //get the items of the current command
	cmd_process_array[cmdid](NULL, 0, NULL);
	if (cmd_handle_params.items_count == 0)   // if no item found, return, no need for reply
		return;
	////////////////////////////////////////////////////
	uint8_t * _item_responce_buff = malloc(SEND_MAX_BUFF_LEN); // allocate memory for response packet
	if (_item_responce_buff == NULL) 
	{	
		rec_pkt_flags.err_code = ERR_OUT_OF_MEM2;
		return;
	}
	////////////////////////////////////////////////////////
	Communication_openResponse();              //open communication responce, from communication layer
	Communication_send_Header_Packet(cmdid);   // send packet header
	/////////////////////////////////////////////////////////// accumulate items data untill limmited buffer size
	for (i = 1; i <= cmd_handle_params.items_count; i++)
	{
		cmd_handle_params.curr_item = i;   // just for test purposes
		cmd_process_array[cmdid](payloadp, i, _item_responce_buff + items_len_accumulator); //get each item parameters
		if (cmd_handle_params.curr_item_length != 0)   // if current item has any data, add data to responce buffer
		{
			Communication_appendResponse(_item_responce_buff + items_len_accumulator, cmd_handle_params.curr_item_length);
		}
		items_len_accumulator += cmd_handle_params.curr_item_length; // sum up data length in response buffer
		// check buffer before overflow
		if ((((items_len_accumulator + cmd_handle_params.next_item_length) >= SEND_MAX_BUFF_LEN) || (i == cmd_handle_params.items_count)) && (items_len_accumulator!= 0))
		{
			uint8_t * _enc_buffer = malloc(items_len_accumulator); // allocat temporary memory for encryption 
			if (_enc_buffer == NULL) 
			{
				rec_pkt_flags.err_code = ERR_OUT_OF_MEM3;
				return;
			}
			encrypt_decrypt_packet(_item_responce_buff, items_len_accumulator, _enc_buffer, false); // encrypt response buffer
			Communication_sendData(_enc_buffer, items_len_accumulator);  // send current section of responce 
			items_len_accumulator = 0;  // reset accumulator 
			free(_enc_buffer);          // free temporary memory allocated for encryption 
		}
	}
	/////////////////////////////////////////////
	Communication_send_EndOfPacket();   // send packet footer 
	///////////////////////////////////////////////////////////////
	free(_item_responce_buff);	        // free memory allocated for response buffer 
	Communication_closeResponse();      // close communication, from communication layer
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
	// if we need some process on payloadp and fill the responseDatap base on, we should call Communication_appendResponse here 
	// if not, better call it once inside CommandHandler_handle, this way is more optilal.
	//Communication_appendResponse(responseDatap, cmd_handle_params.curr_item_length);
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
	//Communication_appendResponse(responseDatap, cmd_handle_params.curr_item_length);
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
	//Communication_appendResponse(responseDatap, cmd_handle_params.curr_item_length);
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
	//Communication_appendResponse(responseDatap, cmd_handle_params.curr_item_length);
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
	//Communication_appendResponse(responseDatap, cmd_handle_params.curr_item_length);
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
	//Communication_appendResponse(responseDatap, cmd_handle_params.curr_item_length);
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
	//Communication_appendResponse(responseDatap, cmd_handle_params.curr_item_length);
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
	//Communication_appendResponse(responseDatap, cmd_handle_params.curr_item_length);
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
	//Communication_appendResponse(responseDatap, cmd_handle_params.curr_item_length);
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
	//Communication_appendResponse(responseDatap, cmd_handle_params.curr_item_length);
}


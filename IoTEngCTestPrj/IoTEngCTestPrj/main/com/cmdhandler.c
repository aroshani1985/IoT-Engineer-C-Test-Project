#include "cmdhandler.h"

struct command_handle_params cmd_handle_params;

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


void cmd_000_process(uint8_t* payloadp, uint16_t ItemIdx, uint8_t* responseDatap)
{
	if (ItemIdx == 0) {
		cmd_handle_params.items_count = (uint16_t) CMD_ID_001_ITEMS;
	}
	else
	{
		
	}
}
void cmd_001_process(uint8_t* payloadp, uint16_t ItemIdx, uint8_t* responseDatap)
{
	if (ItemIdx == 0) {
		cmd_handle_params.items_count = (uint16_t) CMD_ID_001_ITEMS;
	}
	else
	{
		
	}
}
void cmd_002_process(uint8_t* payloadp, uint16_t ItemIdx, uint8_t* responseDatap)
{
	if (ItemIdx == 0) {
		cmd_handle_params.items_count = (uint16_t) CMD_ID_001_ITEMS;
	}
	else
	{
		
	}
}
void cmd_003_process(uint8_t* payloadp, uint16_t ItemIdx, uint8_t* responseDatap)
{
	if (ItemIdx == 0) {
		cmd_handle_params.items_count = (uint16_t) CMD_ID_001_ITEMS;
	}
	else
	{
		
	}
}
void cmd_004_process(uint8_t* payloadp, uint16_t ItemIdx, uint8_t* responseDatap)
{
	if (ItemIdx == 0) {
		cmd_handle_params.items_count = (uint16_t) CMD_ID_001_ITEMS;
	}
	else
	{
		
	}
}
void cmd_005_process(uint8_t* payloadp, uint16_t ItemIdx, uint8_t* responseDatap)
{
	if (ItemIdx == 0) {
		cmd_handle_params.items_count = (uint16_t) CMD_ID_001_ITEMS;
	}
	else
	{
		
	}
}
void cmd_006_process(uint8_t* payloadp, uint16_t ItemIdx, uint8_t* responseDatap)
{
	if (ItemIdx == 0) {
		cmd_handle_params.items_count = (uint16_t) CMD_ID_001_ITEMS;
	}
	else
	{
		
	}
}
void cmd_007_process(uint8_t* payloadp, uint16_t ItemIdx, uint8_t* responseDatap)
{
	if (ItemIdx == 0) {
		cmd_handle_params.items_count = (uint16_t) CMD_ID_001_ITEMS;
	}
	else
	{
		
	}
}
void cmd_008_process(uint8_t* payloadp, uint16_t ItemIdx, uint8_t* responseDatap)
{
	if (ItemIdx == 0) {
		cmd_handle_params.items_count = (uint16_t) CMD_ID_001_ITEMS;
	}
	else
	{
		
	}
}
void cmd_009_process(uint8_t* payloadp, uint16_t ItemIdx, uint8_t* responseDatap)
{
	if (ItemIdx == 0) {
		cmd_handle_params.items_count = (uint16_t) CMD_ID_001_ITEMS;
	}
	else
	{
		
	}
}


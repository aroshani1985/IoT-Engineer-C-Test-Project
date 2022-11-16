#ifndef _CMDHANDLER_H
#define _CMDHANDLER_H

#include <stdio.h>

#define CMD_COUNT           10

#define CMD_ID_000          0
#define CMD_ID_001          1
#define CMD_ID_002          2
#define CMD_ID_003          3
#define CMD_ID_004          4
#define CMD_ID_005          5
#define CMD_ID_006          6
#define CMD_ID_007          7
#define CMD_ID_008          8
#define CMD_ID_009          9


#define CMD_ID_000_ITEMS          10
#define CMD_ID_001_ITEMS          1001
#define CMD_ID_002_ITEMS          1002
#define CMD_ID_003_ITEMS          1003
#define CMD_ID_004_ITEMS          1004
#define CMD_ID_005_ITEMS          1005
#define CMD_ID_006_ITEMS          1006
#define CMD_ID_007_ITEMS          1007
#define CMD_ID_008_ITEMS          1008
#define CMD_ID_009_ITEMS          1009
#define CMD_ID_010_ITEMS          1010

#define CMD_ITEM_FIX_LEN          3

// container for each command parameters
struct command_handle_params
{
	uint16_t items_count; // number of items of each command
};
extern struct command_handle_params cmd_handle_params;

// command process function template 
// payloadp: is a pointer to related payload data in the heap
// ItemIdx: item index is related to different items of one command, 
// ItemIdx =0, returns item count of each command
// responseDatap: pointer to the responce buffer 
typedef void cmd_process(uint8_t* payloadp, uint16_t ItemIdx, uint8_t* responseDatap);

// array of functions, each functions related to one command
extern cmd_process *cmd_process_array[];

// implementation of each command process function
void cmd_000_process(uint8_t* payloadp, uint16_t ItemIdx, uint8_t* responseDatap);
void cmd_001_process(uint8_t* payloadp, uint16_t ItemIdx, uint8_t* responseDatap);
void cmd_002_process(uint8_t* payloadp, uint16_t ItemIdx, uint8_t* responseDatap);
void cmd_003_process(uint8_t* payloadp, uint16_t ItemIdx, uint8_t* responseDatap);
void cmd_004_process(uint8_t* payloadp, uint16_t ItemIdx, uint8_t* responseDatap);
void cmd_005_process(uint8_t* payloadp, uint16_t ItemIdx, uint8_t* responseDatap);
void cmd_006_process(uint8_t* payloadp, uint16_t ItemIdx, uint8_t* responseDatapx);
void cmd_007_process(uint8_t* payloadp, uint16_t ItemIdx, uint8_t* responseDatap);
void cmd_008_process(uint8_t* payloadp, uint16_t ItemIdx, uint8_t* responseDatap);
void cmd_009_process(uint8_t* payloadp, uint16_t ItemIdx, uint8_t* responseDatap);

#endif

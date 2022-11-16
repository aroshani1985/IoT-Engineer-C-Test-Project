#include "pktsend.h"
#include "esp_log.h"
#include "cmdhandler.h"

//just simple implementation for test purposes
void Communication_openResponse()
{
	ESP_LOGI("Send fcn", "Communication_openResponse");
}

//just simple implementation for test purposes
void Communication_closeResponse()
{
	ESP_LOGI("Send fcn", "Communication_closeResponse");
}

//just simple implementation for test purposes
void Communication_sendData(uint8_t* data, uint16_t length)
{
	int i;
	int idx = 0;
	char buff[32];
	////////////////////////////////////
	for (i = 0; i < length; i++)
	{
		if (idx >= 32)
		{
			idx = 0;
			ESP_LOGI("Send fcn", "Send result: %s", buff);
		}
		idx += sprintf(buff + idx, "%hhu ", data[i]);
	}
	if(idx < 32 && idx!= 0)
	   ESP_LOGI("Send fcn", "Send result: %s", buff);
}


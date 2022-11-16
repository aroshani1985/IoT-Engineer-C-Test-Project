#ifndef _PKTSEND_H
#define _PKTSEND_H

#include <stdio.h>


#define SEND_MAX_BUFF_LEN      256

void Communication_openResponse();
void Communication_appendResponse(uint8_t* data, uint16_t  length);
void Communication_sendData(uint8_t* data, uint16_t length);
void Communication_closeResponse();



#endif // ! _PKTSEND_H

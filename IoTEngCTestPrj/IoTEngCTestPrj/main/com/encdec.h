#ifndef _ENCDEC_H
#define _ENCDEC_H

#include <stdio.h>
#include "stdbool.h"


#define ENC_DEC_BUFF_LIMIT     255  //encrypt decrypt functions buffer limit

void encrypt_decrypt_packet(uint8_t* input, uint16_t length, uint8_t* output, bool is_decrypt);
void encrypt(uint8_t* input, uint8_t length, uint8_t* output);
void decrypt(uint8_t* input, uint8_t length, uint8_t* output);

#endif

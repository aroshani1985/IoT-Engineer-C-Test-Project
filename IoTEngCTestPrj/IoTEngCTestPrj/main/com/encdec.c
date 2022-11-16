#include "encdec.h"
#include "string.h"

//wrapper for original ebcrypt and decrypt function to support any length
void encrypt_decrypt_packet(uint8_t* input, uint16_t length, uint8_t* output, bool is_decrypt)
{
	uint8_t i;
	uint8_t pkt_full_segments = length / ENC_DEC_BUFF_LIMIT;     //get full segments of 255 bytes
	uint8_t pkt_last_segment_len = length % ENC_DEC_BUFF_LIMIT;  // get remained bytes
	//////////////////////////////////////// handle full segments
	for (i = 0; i < pkt_full_segments; i++)
	{
		if (is_decrypt)
			decrypt(input + i*ENC_DEC_BUFF_LIMIT, ENC_DEC_BUFF_LIMIT, output + i*ENC_DEC_BUFF_LIMIT);
		else
			encrypt(input + i*ENC_DEC_BUFF_LIMIT, ENC_DEC_BUFF_LIMIT, output + i*ENC_DEC_BUFF_LIMIT);
	}
	//////////////////////////////////handle remaied segment if exist
	if (pkt_last_segment_len) 
	{
		if (is_decrypt)
			decrypt(input + pkt_full_segments*ENC_DEC_BUFF_LIMIT, pkt_last_segment_len, output + pkt_full_segments*ENC_DEC_BUFF_LIMIT);
		else
			encrypt(input + pkt_full_segments*ENC_DEC_BUFF_LIMIT, pkt_last_segment_len, output + pkt_full_segments*ENC_DEC_BUFF_LIMIT);
	}
}

void encrypt(uint8_t* input, uint8_t length, uint8_t* output)
{
	memcpy(output, input, length); // jus for test purposes 
}
void decrypt(uint8_t* input, uint8_t length, uint8_t* output)
{
	memcpy(output, input, length); // jus for test purposes 
}
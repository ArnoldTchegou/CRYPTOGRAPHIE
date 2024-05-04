#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

void broadcast_publickey(char* file_name, uint32_t public_key);

void create_shared_aes_key_and_encrypt_challenge(uint8_t aes_key[16],
                                                 uint32_t internal_secretkey, 
                                                 uint32_t external_publickey, 
                                                 uint32_t seed_table[1024],
                                                 uint8_t *text, size_t text_len);

void secure_channel_com(uint8_t *shared_key,
                        size_t shared_key_length,
                        uint8_t *buffer,
                        size_t length, 
                        uint8_t *IV);


#endif
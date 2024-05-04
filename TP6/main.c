#include "aes.h"
#include "rng.h"
#include "exponentiation.h"
#include "protocol.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {

    // // Init Field
    uint32_t g = ???; 

    // // Init PRNG
    seed = 0;
    uint32_t a = 16;
    uint32_t b = 10;
    uint32_t m = 25;

    // Alice Keys
    //uint32_t alice_secret_key = ???;
    //uint32_t alice_public_key = leaking_square_and_multiply(g, alice_secret_key);
    //broadcast_publickey("alice_pubkey.out", alice_public_key);

    
    // Bob Keys
    ///uint32_t bob_secret_key = ???;
    //uint32_t bob_public_key = leaking_square_and_multiply(g, bob_secret_key);
    //broadcast_publickey("bob_pubkey.out", bob_public_key);

    // init seed table
    uint32_t seed_table[1024];
    for (size_t i = 0; i < 1024; i++) {
        prng(a, b, m);
        seed_table[i] = seed;
        printf("%X\n", seed_table[i]);
    }

    // Alice initiate the protocol by creating a shared key and encrypting a challenge that she sends back to Bob in transcript.out
    //uint8_t shared_key[16];
    // uint8_t challenge[16] = {???};
    //size_t challenge_len = 16;
    //create_shared_aes_key_and_encrypt_challenge(shared_key, alice_secret_key, bob_public_key, seed_table, challenge, challenge_len);
    
    // Use the challenge as IV and encrypt a message using CBC 
    //char str_transaction[] = "Send 100$ to Bob";
    //u_int8_t transaction[16];
    //for (size_t i=0; i<16; i++) {
        //transaction[i] = str_transaction[i];
    //}
    //secure_channel_com(shared_key, 16, transaction, 16, challenge);

    return 0;
}

#ifndef FEISTEL_H
#define FEISTEL_H

#include <cstdint>

// Global key and secret flag variables.
// The secret flag is stored as an 8-byte (64-bit) value.
extern uint32_t KEY;
extern uint64_t SECRET_FLAG;

// Generate a random 32-bit key and an 8-byte secret flag.
// Also writes the values (in hex) to "secret.txt" for verification.
void generate_secrets();

// The round function for our simple Feistel cipher.
// It computes: ((R XOR key) + (R << 1)) mod 2^32.
uint32_t round_function(uint32_t R, uint32_t key);

// Feistel encryption of a 64-bit plaintext using a 4-round network.
// If debug is true, prints each round’s state.
uint64_t feistel_encrypt(uint64_t plaintext, uint32_t key, bool debug = false);

// Feistel decryption of a 64-bit ciphertext using a 4-round network.
uint64_t feistel_decrypt(uint64_t ciphertext, uint32_t key);

#endif

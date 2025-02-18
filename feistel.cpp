#include "feistel.h"
#include <fstream>
#include <random>
#include <iostream>
#include <iomanip>

// Global variables definition.
uint32_t KEY;
uint64_t SECRET_FLAG;
using namespace std;
void generate_secrets() {
    // Use random_device and mt19937 for randomness.
     random_device rd;
     mt19937 gen(rd());
     uniform_int_distribution<uint32_t> dist32(0, 0xFFFFFFFF);
    KEY = dist32(gen);

    // Generate an 8-byte secret flag as a random 64-bit number.
     uniform_int_distribution<uint64_t> dist64(0, 0xFFFFFFFFFFFFFFFF);
    SECRET_FLAG = dist64(gen);

    // Write the key and secret flag to secret.txt (for verification only).
     ofstream ofs("secret.txt");
    if (ofs) {
        ofs << "KEY = " <<  hex << KEY << "\n";
        ofs << "SECRET_FLAG = " <<  hex << SECRET_FLAG << "\n";
    }
}

uint32_t round_function(uint32_t R, uint32_t key) {
    // Since we are using 32-bit unsigned integers, overflow wraps modulo 2^32.
    return ((R ^ key) + (R << 1));
}

uint64_t feistel_encrypt(uint64_t plaintext, uint32_t key, bool debug) {
    // Split the 64-bit plaintext into two 32-bit halves.
    uint32_t L = static_cast<uint32_t>(plaintext >> 32);
    uint32_t R = static_cast<uint32_t>(plaintext & 0xFFFFFFFF);

    for (int i = 0; i < 4; i++) {
        if (debug) {
             cout << "[DEBUG] Round " << i << ": L = 0x"
                      <<  hex << L << ", R = 0x" << R << "\n";
        }
        uint32_t newL = R;
        uint32_t newR = L ^ round_function(R, key);
        L = newL;
        R = newR;
    }
    uint64_t ciphertext = (static_cast<uint64_t>(L) << 32) | R;
    if (debug) {
         cout << "[DEBUG] Final ciphertext: 0x" <<  hex << ciphertext << "\n";
    }
    return ciphertext;
}

uint64_t feistel_decrypt(uint64_t ciphertext, uint32_t key) {
    uint32_t L = static_cast<uint32_t>(ciphertext >> 32);
    uint32_t R = static_cast<uint32_t>(ciphertext & 0xFFFFFFFF);
    for (int i = 0; i < 4; i++) {
        uint32_t newL = R ^ round_function(L, key);
        uint32_t newR = L;
        L = newL;
        R = newR;
    }
    uint64_t plaintext = (static_cast<uint64_t>(L) << 32) | R;
    return plaintext;
}

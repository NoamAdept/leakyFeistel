#include "feistel.h"
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;
void print_header() {
    cout << "\n-----------------------------------------------------\n"
              << "             CTF Challenge: Feistel Cipher\n"
              << "-----------------------------------------------------\n"
              << "Welcome, challenger!\n\n"
              << "In this challenge, you are given access to an oracle that\n"
              << "encrypts data using a simple 4-round Feistel network.\n\n"
              << "Your mission:\n"
              << "  1. Submit chosen plaintexts to the oracle.\n"
              << "  2. Use the (leaked) debug output to eventually recover the key.\n"
              << "  3. Decrypt the hidden secret flag.\n\n"
              << "Hints:\n"
              << "  - A Feistel cipher splits data into two halves and uses\n"
              << "    a round function to mix them.\n"
              << "  - Reusing a key in a simple cipher can leak critical information.\n\n"
              << "IMPORTANT: NEVER reuse keys in real systems!\n"
              << "-----------------------------------------------------\n";
}

int main() {
    print_header();
     cout << "Welcome to the CTF Feistel Cipher Challenge!\n";
     cout << "1. Run Oracle\n";
     cout << "Select option (1 to run oracle): ";

     string choice;
     getline( cin, choice);

    if (choice == "1") {
        // Generate new secrets at startup.
        generate_secrets();

         cout << "=== Feistel Oracle ===\n";
         cout << "The oracle is encrypting the secret flag. Can you break it?\n";

        // Encrypt the secret flag.
        uint64_t ct = feistel_encrypt(SECRET_FLAG, KEY, false);
        // In a real challenge, this ciphertext would be hidden.
         cout << "[Oracle] Encrypted flag (hidden): 0x" <<  hex << ct << "\n";
         cout << "\nYou can now submit any 8-byte hex plaintext to see its encryption (with debug output).\n";
         cout << "Type 'exit' to quit.\n";

        while (true) {
             cout << "Enter 8-byte hex plaintext (or 'exit'): ";
             string input;
             getline( cin, input);
            if (input == "exit" || input == "EXIT")
                break;
            try {
                // Convert hex string to a 64-bit unsigned integer.
                uint64_t pt =  stoull(input, nullptr, 16);
                uint64_t ct_result = feistel_encrypt(pt, KEY, true);
                 cout << "[Oracle] Resulting ciphertext: 0x" <<  hex << ct_result << "\n";
            } catch (const  exception &e) {
                 cout << "[Oracle] Error: " << e.what() << "\n";
            }
        }
    } else {
         cout << "Invalid option. Exiting.\n";
    }
    return 0;
}

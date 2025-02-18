
# Feistel Cipher Key Recovery Exploit

This project demonstrates a vulnerability in a Feistel cipher implementation that uses a fixed key for all rounds (i.e., no key scheduling). By carefully choosing the plaintext input, an attacker can recover the key from leaked intermediate values and subsequently decrypt any ciphertext produced by the cipher.

![Exploit Diagram](https://github.com/user-attachments/assets/dd98abc9-39cc-450e-a1f2-a2199e39cecc)

## Overview

The vulnerability arises when the attacker sends a specially crafted plaintext block with the left half set to zero. In the first round of the Feistel cipher, the computation simplifies to:

$$
L_1 = R_0,\quad R_1 = L_0 \oplus F(R_0, k) = F(R_0, k)
$$

Since \(L_0 = 0\), the output of the round function, \(F_0 = F(R_0, k)\), is directly exposed (for example, via debug output). The round function is defined as:

$$
F(R_0, k) = (R_0 \oplus k) + (R_0 \ll 1)
$$

Rearranging the equation yields:

$$
R_0 \oplus k = F_0 - (R_0 \ll 1) \quad \Rightarrow \quad k = R_0 \oplus \bigl(F_0 - (R_0 \ll 1)\bigr)
$$

This relationship allows an attacker to recover the key and decrypt any ciphertext produced by the cipher.

## Components

- **Vulnerable Cipher Module:**  
  Contains the implementation of the Feistel cipher with a fixed key.

- **Challenge Oracle:**  
  Provides an interactive environment where users can input 8-byte hex plaintexts and view how they are encrypted (with debug output).

- **Attacker Exploit:**  
  Demonstrates how to recover the key using leaked information from the cipher, and then decrypts a secret message (flag).

- **Diagram:**  
  A visual representation of the attack is provided in the embedded diagram above.

## How to Build and Run

### Compile the Oracle (Challenge) Program

Open a terminal and run:

```bash
g++ -std=c++17 ctf_challenge.cpp feistel.cpp -o ctf_challenge
```

### Compile the Exploit Program

In the same terminal, run:

```bash
g++ -std=c++17 exploit.cpp feistel.cpp -o exploit
```

### Run the Oracle

Start the challenge oracle by executing:

```bash
./ctf_challenge
```

You will see the challenge header and be able to enter 8‑byte hex plaintexts (with debug output).

### Run the Exploit

In another terminal, execute:

```bash
./exploit
```

This will simulate the chosen‑plaintext attack, recover the key, and print the decrypted flag.


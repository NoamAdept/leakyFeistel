# Feistel Cipher Key Recovery Exploit

This project demonstrates a vulnerability in a Feistel cipher implementation that uses a fixed key for all rounds (i.e., no key scheduling). By carefully choosing the plaintext input, an attacker can recover the key from leaked intermediate values.

![image](https://github.com/user-attachments/assets/dd98abc9-39cc-450e-a1f2-a2199e39cecc)


## Overview

The vulnerability arises when the attacker sends a specially crafted plaintext block with the left half set to zero. In the first round of the Feistel cipher, the computation simplifies to:


$L_1 = R_0,\quad R_1 = L_0 \oplus F(R_0,k) = F(R_0,k)$


Since $L_0 = 0$, the output of the round function, $F_0 = F(R_0,k)$, is directly exposed (e.g., via debug output). The round function is defined as:


$F(R_0,k) = (R_0 \oplus k) + (R_0 \ll 1)$

Rearranging the equation yields:

$$
R_0 \oplus k = F_0 - (R_0 \ll 1)
\Rightarrow k = R_0 \oplus \bigl(F_0 - (R_0 \ll 1)\bigr)
$$


This relationship allows an attacker to recover the key and subsequently decrypt any ciphertext produced by the cipher.

## Components

- **Vulnerable Cipher Module:** Contains the implementation of the Feistel cipher with a fixed key.
- **Challenge Oracle:** Provides an interactive environment where users can input plaintexts to see how they are encrypted.
- **Attacker Exploit:** Demonstrates how to recover the key and decrypt a secret message (flag) using the leaked information.
- **Diagram:** A visual representation of the attack is provided in the embedded LaTeX diagram.

## Embedded Diagram

<img width="610" alt="Screenshot 2025-02-18 at 13 15 58" src="https://github.com/user-attachments/assets/68525f94-c995-45b0-8861-59733000f754" />



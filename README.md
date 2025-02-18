
# Feistel Cipher Key Recovery Exploit

This project demonstrates a vulnerability in a Feistel cipher implementation that uses a fixed key for all rounds (i.e., no key scheduling). By carefully choosing the plaintext input, an attacker can recover the key from leaked intermediate values and subsequently decrypt any ciphertext produced by the cipher.

## Overview

![Exploit Diagram](https://github.com/user-attachments/assets/dd98abc9-39cc-450e-a1f2-a2199e39cecc)


Source: Joy of Cryptography

Suppose that $k_1 =  k_2 =  ... k_r \in \mathbb{R}$

The vulnerability arises when the attacker sends a specially crafted plaintext block with the left half set to zero. In the first round of the Feistel cipher, the computation simplifies to:

$$
L_1 = R_0,\quad R_1 = L_0 \oplus F(R_0, k) = F(R_0, k)
$$

Since $L_0 = 0$, the output of the round function, $F_0 = F(R_0, k)$, is directly exposed (for example, via debug output). The round function is defined as:

$$
F(R_0, k) = (R_0 \oplus k) + (R_0 \ll 1)
$$

Rearranging the equation yields:

$$
R_0 \oplus k = F_0 - (R_0 \ll 1) \quad \Rightarrow \quad k = R_0 \oplus \bigl(F_0 - (R_0 \ll 1)\bigr)
$$

This relationship allows an attacker to recover the key and decrypt any ciphertext produced by the cipher.


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


## How might I exploit this Feistel?

<details>
<img width="496" alt="image" src="https://github.com/user-attachments/assets/ca983742-e0bd-495f-81bd-0bfa9bc2432e" />

</details>







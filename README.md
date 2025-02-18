# Feistel Cipher Key Recovery Exploit

This project demonstrates a vulnerability in a Feistel cipher implementation that uses a fixed key for all rounds (i.e., no key scheduling). By carefully choosing the plaintext input, an attacker can recover the key from leaked intermediate values.

## Overview

The vulnerability arises when the attacker sends a specially crafted plaintext block with the left half set to zero. In the first round of the Feistel cipher, the computation simplifies to:

\[
L_1 = R_0,\quad R_1 = L_0 \oplus F(R_0,k) = F(R_0,k)
\]

Since \(L_0 = 0\), the output of the round function, \(F_0 = F(R_0,k)\), is directly exposed (e.g., via debug output). The round function is defined as:

\[
F(R_0,k) = (R_0 \oplus k) + (R_0 \ll 1)
\]

Rearranging the equation yields:

\[
R_0 \oplus k = F_0 - (R_0 \ll 1)
\]
\[
\Rightarrow k = R_0 \oplus \bigl(F_0 - (R_0 \ll 1)\bigr)
\]

This relationship allows an attacker to recover the key and subsequently decrypt any ciphertext produced by the cipher.

## Components

- **Vulnerable Cipher Module:** Contains the implementation of the Feistel cipher with a fixed key.
- **Challenge Oracle:** Provides an interactive environment where users can input plaintexts to see how they are encrypted.
- **Attacker Exploit:** Demonstrates how to recover the key and decrypt a secret message (flag) using the leaked information.
- **Diagram:** A visual representation of the attack is provided in the embedded LaTeX diagram.

## Embedded Diagram

Below is the LaTeX/TikZ code for the diagram that explains the key recovery exploit:

```latex
\documentclass[tikz,border=10pt]{standalone}
\usetikzlibrary{positioning, arrows.meta, shapes}
\begin{document}

\begin{tikzpicture}[
    node distance=2.5cm and 2.5cm,
    auto,
    roundnode/.style={
        rectangle,
        draw=black,
        rounded corners,
        align=center,
        minimum width=3.5cm,
        minimum height=1.5cm,
        text width=3.5cm,
        font=\small
    },
    arrow/.style={-{Latex[length=3mm]}, thick},
    dashedarrow/.style={arrow, dashed}
  ]
  
  % Title
  \node[font=\Large\bfseries] (title) {Feistel Cipher Key Recovery Exploit};
  
  % Nodes
  \node[roundnode, below=of title, yshift=-0.5cm] (plaintext) 
    {Plaintext Block \\[0.3em] \(P = L_0 \,||\, R_0\) \\[0.3em] with \(L_0 = 0\)};
  
  \node[roundnode, right=of plaintext, xshift=1cm] (round0) 
    {Round 0 \\[0.3em] \(L_1 = R_0\) \\[0.3em] \(R_1 = L_0 \oplus F(R_0,k)\)};
    
  \node[roundnode, below=of round0] (roundfunc) 
    {Round Function \\[0.3em] \(F(R_0,k) = (R_0 \oplus k) + (R_0 \ll 1)\)};
    
  \node[roundnode, right=of round0, xshift=1cm] (ciphertext) 
    {Ciphertext \\[0.3em] \(C = L_1 \,||\, R_1\)};
  
  % Arrows between nodes
  \draw[arrow] (plaintext) -- (round0);
  \draw[arrow] (round0) -- (ciphertext);
  
  % Arrow from Round0 to Round Function
  \draw[arrow] (round0.south) -- (roundfunc.north) node[midway, right] {\(F_0\)};
  
  % Leak annotation
  \node[below=of roundfunc, text width=6cm, align=center, font=\small] (leak) 
    {Leak: \(F_0\) is observed via debug output};
  \draw[dashedarrow] (roundfunc.south) -- (leak.north);
  
  % Exploit annotation
  \node[below=of leak, text width=10cm, align=center, font=\small] (exploit) {
    \textbf{Exploit:} \\[0.3em]
    With \(L_0 = 0\), we have: \\[0.3em]
    \(R_1 = F(R_0,k) = (R_0 \oplus k) + (R_0 \ll 1)\) \\[0.3em]
    Rearranging gives: \\[0.3em]
    \(R_0 \oplus k = F_0 - (R_0 \ll 1)\) \\[0.3em]
    \(\Rightarrow k = R_0 \oplus \bigl(F_0 - (R_0 \ll 1)\bigr)\)
  };
  
  \draw[dashedarrow] (exploit.north) -- ++(0,2) -| (roundfunc.east);
  
\end{tikzpicture}

\end{document}


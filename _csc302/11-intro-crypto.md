---
layout: lecture
pretty_table: true
collection: csc302
course: CSC 302: Computer Security II
title: "Introduction to Cryptography - Secret-Key Encryption"
toc:
  - name: Introduction
  - name: Substitution Cipher
  - name: Encryption Standard
  - name: Encryption Modes
  - name: Modes for Authenticated Encryption
---
# Introduction to Cryptography - Secret-Key Encryption

## Introduction

- Encryption is the process of encoding a message in such a way that 
only authorized parties can read the content of the original message
- History of encryption dates back to 1900 BC
- Two types of encryption
  - Secret-key encryption : same key for encryption and decryption
  - Pubic-key encryption  : different keys for encryption and decryption
- We focus on secret-key encryption in this chapter

## Substitution Cipher

- Encryption is done by replacing `units` of plaintext with ciphertext, 
according to a fixed system.
- `Units` may be single letters, pairs of letters, triplets of letters, 
mixtures of the above, and so forth. 
- Decryption simply performs the inverse substitution.
- Two typical substitution ciphers:
  - Monoalphabetic - fixed substitution over the entire message
  - Polyalphabetic - a number of substitutions at different positions in the message

### 2.1. Monoalphabetic Substitution Cipher

- Encryption and decryption
- Setup environment

~~~bash
wget https://seedsecuritylabs.org/Labs_20.04/Files/Crypto_Encryption/Labsetup.zip
unzip Lapsetup
cd Lapsetup
docker-compose up -d
~~~

- Check the `tr` command

~~~bash
wget --no-check-certificate https://cs.wcupa.edu/lngo/data/enigma.txt
cat enigma.txt
tr [:upper:] [:lower:] < enigma.txt > lowercase.txt
cat lowercase.txt
~~~

- Encryption and decryption process

~~~bash
tr 'a-z' 'vgapnbrtmosicuxejhqyzflkdw' < enigma.txt > cipher.txt
cat cipher.txt
tr 'vgapnbrtmosicuxejhqyzflkdw' 'a-z' < cipher.txt > plaintext.txt
cat plaintext.txt
~~~

### 2.2. Breaking Monoalphabetic Substitution Cipher

- Frequency analysis is the study of the frequency of letters or 
groups of letters in a ciphertext. 
  - Common letters : `T`, `A`, `E`, `I`, `O`
  - Common 2-letter combinations (bigrams): `TH`, `HE`, `IN`, `ER`
  - Common 3-letter combinations (trigrams): `THE`, `AND`, and `ING`
- Perform frequency analysis on cipher text to guess frequency!

{% include figure.liquid path="assets/img/courses/csc302/cryptography/frequency.png" width="50%" zoomable=true alt="Frequency analysis" %}

- Create the following python script

~~~python
from collections import Counter
import re

TOP_K = 20
N_GRAM = 3

# generate all the n-grams for value n
def ngrams(n, text):
  for i in range(len(text) - n + 1):
    if not re.search(r'\s', text[i:i+n]):
      yield text[i:i+n]

with open('cipher.txt') as f:
  text = f.read()

for N in range(N_GRAM):
  print("-----------------------------------")
  print("{}-ngram (top {}):".format(N+1, TOP_K))
  counts = Counter(ngrams(N+1, text))
  sorted_counts = counts.most_common(TOP_K)
  for ngram, count in sorted_counts:
    print("{}: {}".format(ngram, count))
~~~

### 2.3. Frequency Analysis results

- [English frequencies](https://www3.nd.edu/~busiforc/handouts/cryptography/Letter%20Frequencies.html)

~~~bash
python3 freq.py
~~~

~~~bash
tr n E < cipher.txt
tr nt EH < cipher.txt
tr nty EHT < cipher.txt
~~~

- Continue guessing ...

### 2.4. Exercise

~~~bash
wget --no-check-certificate https://www.cs.wcupa.edu/lngo/data/cipher_speech.txt
mv cipher_speech.txt cipher.txt
~~~

- Try to decode this text!

## Encryption Standard

### 3.1. Data Encryption Standard (DES)

- DES is a block cipher - can only encrypt a block of data
- Block size for DES is 64 bits
- DES uses 56-bit keys although a 64-bit key is fed into the algorithm
- Theoretical attacks were identified. None was practical enough to 
cause major concerns.
- Triple DES can solve DES's key size problem

### 3.2. Advanced Encryption Standard (AES)
- AES is a block cipher
- 128-bit block size.
- Three different key sizes: 128, 192, and 256 bits

## Encryption Modes

- Encryption mode or mode of operation refers to the many ways to make the input of 
an encryption algorithm different.

- Examples include:
  - Electronic Codebook (ECB)
  - Cipher Block Chaining (CBC)
  - Propagating CBC (PCBC)
  - Cipher Feedback (CFB)
  - Output Feedback (OFB)
  - Counter (CTR)

### 4.1. Electronic Codebook (ECB) Mode

- Blocks are encrypted separatedly

{% include figure.liquid path="assets/img/courses/csc302/cryptography/ecb.png" width="50%" zoomable=true alt="ECB" %}

~~~bash
echo "Hello Golden Rams!" > plain.txt
openssl enc -aes-128-ecb -e -in plain.txt -out cipher.txt -K 00112233445566778899AABBCCDDEEFF
cat cipher.txt
openssl enc -aes-128-ecb -d -in cipher.txt -out plain2.txt -K 00112233445566778899AABBCCDDEEFF
cat plain2.txt
~~~

- We use the 128-bit (key size) AES algorithm
  - The -aes-128-ecb option specifies ECB mode 
  - The -e option indicates encryption
  - The -d option indicate decryption 
  - The -K option is used to specify the encryption/decryption key

- Naive and unsafe method

{% include figure.liquid path="assets/img/courses/csc302/cryptography/encryption_modes.png" width="50%" zoomable=true alt="Encryption modes" %}


### 4.2. Cipher Block Chaining (CBC) Mode

- The main purpose of `IV` is to ensure that even if two 
plaintexts are identical, their ciphertexts are still different, 
because different IVs will be used.
  - Decryption can be parallelized
  - Encryption cannot be parallelized

{% include figure.liquid path="assets/img/courses/csc302/cryptography/cbc.png" width="50%" zoomable=true alt="CBC" %}

~~~bash
openssl enc -aes-128-cbc -e -in plain.txt -out cipher1.txt -K 00112233445566778899AABBCCDDEEFF -iv 000102030405060708090a0b0c0d0e0f
openssl enc -aes-128-ecb -e -in plain.txt -out cipher2.txt -K 00112233445566778899AABBCCDDEEFF -iv 000102030405060708090a0b0c0d0e0e
cat cipher1.txt
cat cipher2.txt
~~~

- We use the 128-bit (key size) AES algorithm
  - The -aes-128-cbc option specifies CBC mode 
  - The -e option indicates encryption
  - The -K option is used to specify the encryption/decryption key
  - The -iv option is used to specify the initialization vector (IV)

### 4.3. Cipher Feedback (CFB) Mode

- A block cipher is turned into a stream cipher.
- Ideal for encrypting real-time data.
- Padding not required for the last block.
- Decryption using the CFB mode can be parallelized, while 
encryption can only be conducted sequentially

{% include figure.liquid path="assets/img/courses/csc302/cryptography/cfb.png" width="50%" zoomable=true alt="CFB" %}

~~~bash
openssl enc -aes-128-cbc -e -in plain.txt -out cipher1.txt -K 00112233445566778899AABBCCDDEEFF -iv 000102030405060708090a0b0c0d0e0f
openssl enc -aes-128-cfb -e -in plain.txt -out cipher2.txt -K 00112233445566778899AABBCCDDEEFF -iv 000102030405060708090a0b0c0d0e0f
cat cipher1.txt
cat cipher2.txt
ls -l plain.txt cipher1.txt cipher2.txt
~~~

### 4.4. Output Feedback (OFB) Mode

- Similar to CFB
  - Used as stream cipher
  - Does not need padding
  - Decryption can parallelized
- Encryption in the OFB mode can be parallelized

{% include figure.liquid path="assets/img/courses/csc302/cryptography/ofb.png" width="50%" zoomable=true alt="OFB" %}

### 4.5. Counter (CTR) Mode

- It basically uses a counter to generate the key streams
- No key stream can be reused, hence the counter value for 
each block is prepended with a randomly generated value called nonce
- This nonce serves the same role as the IV does to the other 
encryption modes.
- Both encryption and decryption can be parallelized the key stream 
in the CTR mode can be calculated in parallel during the encryption

{% include figure.liquid path="assets/img/courses/csc302/cryptography/ctr.png" width="50%" zoomable=true alt="CTR" %}

## Modes for Authenticated Encryption

- None of the Encryption modes discussed so far cannot be used to 
achieve message authentication
- A number of modes of operation have been designed to 
combine message authentication and encryption.
- Examples include
  - GCM (Galois/Counter Mode) 
  - CCM (Counter with CBC-MAC)
  - OCB mode (Offset Codebook Mode)

### 5.1. Padding

- Block cipher encryption modes divide plaintext into blocks 
and the size of each block should match the cipher’s block size.
- No guarantee that the size of the last block matches the cipher’s 
block size.
- Last block of the plaintext needs padding i.e. before encryption, 
extra data needs to be added to the last block of the plaintext, so 
its size equals to the cipher’s block size.
- Padding schemes need to clearly mark where the padding starts, so 
decryption can remove the padded data.
- Commonly used padding scheme is PKCS#5

### 5.2. Initial Vector and Common Mistakes

- Initial vectors have the following requirements:
  - IV is supposed to be stored or transmitted in plaintext
  - IV should not repeat (uniqueness).
  - IV should not be predictable.

### 5.3. Experiment

- Initial IV for Bob: `4ae71336e44bf9bf79d2752e234818a5`
- Let's encrypt Bob's vote

~~~bash
echo -n "John Smith......" > P1
openssl enc -aes-128-cbc -e -in P1 -out C1 -K 00112233445566778899AABBCCDDEEFF -iv 4ae71336e44bf9bf79d2752e234818a5
echo -n "4ae71336e44bf9bf79d2752e234818a5" | xxd -r -p > tmp_iv 
md5sum tmp_iv
~~~

- The next iv is `398d01fdf7934d1292c263d374778e1a`

- Since there is a limited number of candidates, let's assume Even guesses 
that Bob voted for Mr. Ram, she creates P1_guessed and XOR it with the first and second iv values, 
and finally constructs the name for a write-in candidate.

~~~bash
echo -n "John Smith......" > P1_guessed
~~~

- Create a python program called `xor.py` to do exclusive or

~~~python
#!/usr/bin/env python3
from sys import argv
script, first, second = argv
aa = bytearray.fromhex(first)
bb = bytearray.fromhex(second)
xord = bytearray(x^y for x, y in zip(aa, bb))
print(xord.hex())
~~~

- Convert the guessed text to hex
  - In my case, I have the result as `4a6f686e20536d6974682e2e2e2e2e2e`. 
  - The results might differ on individual machines. 

~~~bash
xxd -p P1_guessed
~~~

- XOR the hex outcome with the initial iv value

~~~bash
chmod +x xor.py
./xor.py 4a6f686e20536d6974682e2e2e2e2e2e 4ae71336e44bf9bf79d2752e234818a5
~~~

- Take the result and XOR again with the second iv value

~~~bash
./xor.py 00887b58c41894d60dba5b000d66368b 398d01fdf7934d1292c263d374778e1a 
~~~

- Conver the above result to binary and save to P2

~~~bash
echo -n "39057aa5338bd9c49f7838d37911b891" | xxd -r -p > P2
~~~

- Eve gives her write-in candidate’s name (stored in P2) to the voting machine, 
which encrypts the name using second IV. The result is stored in C2. 
If C1 (Bob’s encrypted vote) == C2, then Eve knows for sure that Bob has voted for Mr. Ram!

~~~bash
openssl enc -aes-128-cbc -e -in P2 -out C2 -K 00112233445566778899AABBCCDDEEFF -iv 398d01fdf7934d1292c263d374778e1a
xxd -p C1
xxd -p C2
~~~

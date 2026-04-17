---
layout: lecture
pretty_table: true
collection: csc302

title: "One-Way Hash Functions"
toc:
  - name: Overview of One-way Hash Functions
  - name: Common One-way Hash Functions
  - name: Applications of One-Way Hash Functions
---
# One-Way Hash Functions

## Overview of One-way Hash Functions

### Overview

- Essential building block in cryptography
- Need to satisfy some cryptographic properties:
  - One-way
  - Collision resistant 
- Usage example:
  - Password authentication
  - Integrity preservation
  - Blockchain
- Possible Attacks:
  - Length extension attack
  - Collision attack

### Properties of One-way Hash Function
- Difference from Hash Function
  - Hash function: maps arbitrary size data to data of fixed size
  - Example: `f(x) = x mod 1000`
- One-way Hash Properties:
  - One-way: hash(m) = h, difficult to find m
  - Collision resistant: Difficult to find `m1` and `m2` such that `hash(m1) = hash(m2)`
- Common One-way Hash Functions:
  - MD series
  - SHA series

## Common One-way Hash Functions

### MD: Message Digest
- Developed by Ron Rivest
- Includes MD2, MD4, MD5,and MD6
- Status of Algorithms:
  - MD2, MD4 - severely broken (obsolete)
  - MD5 - collision resistance property broken, one-way property not broken
  - MD6 - developed in response to proposal by NIST

### SHA: Secure Hash Algorithm 
- Published by NIST
- Includes SHA-0, SHA-1, SHA-2, and SHA-3
- Status of Algorithms:
  - SHA-0: withdrawn due to flaw
  - SHA-1: Designed by NSA; Collision attack found in 2017
  - SHA-2: Designed by NSA; Includes SHA-256 and SHA-512; Other truncated versions; 
  No significant attack found yet
  - SHA-3: Released in 2015; Has different construction structure (compared to SHA-1 and SHA-2)

### How One-Way Hash Algorithm Works
- Construction method called Merkle–Damgard
- Used by algorithms like MD5, SHA-1, and SHA-2
- Block of messages are chain-compresed with an IV to generate 
a final hashed value

{% include figure.liquid path="assets/img/courses/csc302/hash/merkle-damgard.png" width="50%" zoomable=true alt="Merkle-Damgard" %}

### One-Way Hash Commands
- Aavilable via Linux utility programs
- Example: `md5sum`, `sha224sum`, `sha256sum`, `sha384sum` and `sha512sum`

~~~bash
echo -n "Golden Rams" > file.txt
md5sum file.txt
sha256sum file.txt
openssl dgst -sha256 file.txt
openssl sha256 file.txt
openssl md5 file.txt
openssl dgst -md5 file.txt
~~~

### Computing One-Way Hash in Programs
- Different languages including C/C++, Python, SQL, PHP provide support
- Language specific:
  - MySQL - SHA2 function
  - Python - Use `hashlib` package
  - C - Use functions from openssl/sha.h header
- Python example:

~~~python
python3
>>> import hashlib
>>> m = hashlib.sha256()
>>> m.update(b"Golden Rams")
~~~

- C example: `calculate_sha256.c`

~~~c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

int main(int argc, char* argv) {
  SHA256_CTX ctx;
  u_int8_t results[SHA256_DIGEST_LENGTH];
  int i;
  char *msg_part1 = "Golden ";
  char *msg_part2 = "Rams";

  SHA256_Init(&ctx);
  SHA256_Update(&ctx, msg_part1, strlen(msg_part1));
  SHA256_Update(&ctx, msg_part2, strlen(msg_part2));
  SHA256_Final(results, &ctx);
  printf("%s%s\n", msg_part1, msg_part2);
  for (i = 0; i < SHA256_DIGEST_LENGTH; i++) {
    printf("%02x", results[i]);
  }
  printf("\n");
}
~~~

- Confirm that the hash matches

~~~bash
gcc -o calculate_sha256 calculate_sha256.c -lcrypto
./calculate_sha256 
~~~

## Applications of One-Way Hash Functions

### Integrity Verification
- Changing one bit of the original data changes hash value

~~~bash
echo -n "Golden Rams" | sha256sum
echo -n "G0lden Rams" | sha256sum
~~~

- Usage examples:
  - Detect change in system files
  - Detect if file downloaded from website is corrupted


### Committing a Secret Without Telling It
- One-way property
  - Disclosing the hash does not disclose the original message
  - Useful to commit secret without disclosing the secret itself
- Usage Example - Stock Market
  - Need to make prediction about the stock market about a certain day
  - Publish the hash of the secret on your website
  - On the particular day, release the secret
- Your audience can verify it against the hash

### Password Verification 
- To login into account, user needs to tell a secret (password)
- Cannot store the secrets in their plaintext
- Need for:
  - Password storage where nobody can know what the password is
  - If provided with a password, it verified against the stored password
- Solution: one-way hash function
- Example: Linux stores passwords in the /etc/shadow file

~~~
sudo cat /etc/shadow | grep root
~~~

- Case Study: Linux Shadow File
  - Password field has 3 parts, separated by the `$` sign: 
    - `$`ALGORITHM_USED`$`SALT`$`PASSWORD_HASH
  - Salt and password hash are encoded into printable characters
  - Multiple rounds of hash function (slow down brute-force attack)
- Purpose of Salt
  - Using salt, same input can result in different hashes
  - Password hash = one-way hash rounds (password || random string)
  - Random string is the salt


~~~bash
useradd -m -s /bin/bash seed
echo "seed:dees" | chpasswd
useradd -m -s /bin/bash seed2
echo "seed2:dees" | chpasswd
cat /etc/shadow | grep seed
cat /etc/shadow | grep seed
~~~

- In my case, the outcomes of the final two `cat` commands are:

~~~bash
seed:$6$6m4jvilqG3xbXlNa$xHCTxjkWN0Agbo5jBl8xl1EkEN7kyakIHr87Mw2oG1vwV2y2fllXiY5pspZfcu6orQuclyo530S/okBMk2oTy/:19480:0:99999:7:::
seed2:$6$CbEbHBQYnmoyZtw6$EgS8kC6qZXbgJ9tRsucryLKarHRg4NZcXZJ7zAkBoeZ8otrkwx4E3IjjRkrMJmQh9YrP0osbno9RyETkvwDye0:19480:0:99999:7:::
~~~

- Both accounts `seed` and `seed2` have the same password, but are salted differently in the hash

~~~python
python3
>>> import crypt
>>> print(crypt.crypt("dees","$6$6m4jvilqG3xbXlNa"))
>>> print(crypt.crypt("dees","$6$CbEbHBQYnmoyZtw6")) 
~~~

- Attacks Prevented by Salt
  - Dictionary Attack
    - Put candidate words in a dictionary
    - Try each against the targeted password hash to find a match
  - Rainbow Table Attack
    - Precomputed table for reversing cryptographic hash functions
  - Why Salt Prevents them ?
    - If target password is same as precomputed data, the hash will be the same
    - If this property does not hold, all the precomputed data are useless
  - Salt destroys that property

### Trusted Timestamping
- Need:  How to prove that a document existed prior to certain date ?
- Timestamping Approaches:
  - Approach # 1: Publish one-way hash (instead of document) in a newspaper or a magazine
  - Approach # 2: Time Stamping Authority (TSA) can sign the document hash using private key
  - Approach # 3: 
    - Use Blockchain i.e. a growing list of record (blocks)
    - Publish document hash in a block
    - Blockchain depends on one-way hash

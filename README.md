# __Rail fence ciphers__

This program contains :
1. Encryption of a message using the classical rail-fence cipher algorithm
2. Encryption of a message using the 2-level rail-fence cipher
3. Decryption of a message using the 2-level rail-fence cipher

Code includes the following functions:
```
void railFence(char *message, char *cipherText, int length, int A);
void railFence2(char *message, char *cipherText, int length, int A, int B,
int dir);
```
The function railFence2() accepts an argument dir which controls whether the function performs
encryption or decryption. When dir=0 the function should encrypt (ie: read from message[] and
write to cipherText[] and when dir=1 it should decrypt (ie: read from cipherText[] and write to
message[]

## 2-level rail fence cipher 

The encryption algorithm involves two broad steps:
1. Writing the message on a 2D grid where each row is called a "rail". The message "zig-zags" between
the top and bottom rails, one message character per column. The height (number of rows) is the "key".
2. The cipher text is created by reading the characters of the grid in a top-to-bottom-left-to-right
sequence.
Where the classical rail fence cipher has a \key" which is a single integer, A, your algorithm will use two
integers A, and B with A > B and B > 1; alternating between them when writing out the message on the
fence rails. This algorithm reduces down to the classical rail fence cipher if A = B.

__General Example__
If the message characters are denoted A, B, C, D, ... , etc and the cipher key is chosen as A = 4
and B = 2 then the message characters would be written on the rails as:
A-------I-------Q
-B-----H-J-----P-
--C-E-G---K-M-O--
---D-F-----L-N---
Observe the general pattern in the algorithm:
1. Down A rails (to D)
2. Up to a peak of B rails (up 1 to E)
3. Down B 􀀀 1 rails back to the bottom (down 1 to F)
4. Up to a peak of A rails (up 3 to I)
5. Repeat until whole message has been written to the grid
The ciphertext can then be read o left-to-right-top-to-bottom:
A, I, Q, B, H, J, P, C, E, G, K, M, O, D, F, L, N

## Message specification
1. The ~ character must not appear in the message
2. A single ~ character indicates the end of the message
3. A newline character in the message should read into the program and be encrypted just like any
other allowed character.

__HOW TO RUN__
This program works for three kinds of inputs. 
1) Default hardcoded tests. This tests all the functions as displays result
2) stdin input, where user has otpion to select which function to run 
3) file input. The txt input file is created as follows:
  1) first line - > contains an integer, tells which function to run 
  2) second line -> contains key,integer
  3) third line -> contain key,integer (only for 2-level rail fence)
  4) text message ending with "~"
 File can contain many test cases.

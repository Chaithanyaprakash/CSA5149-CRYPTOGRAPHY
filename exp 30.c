#include <stdio.h>
#include <string.h>
#define BLOCK_SIZE 16 
#define KEY_SIZE 16  
void encrypt(unsigned char *output, const unsigned char *input, const unsigned char *key) 
{
    for (int i = 0; i < BLOCK_SIZE; ++i) 
	{
        output[i] = input[i] ^ key[i];
    }
}
void printBlock(const unsigned char *block) 
{
    for (int i = 0; i < BLOCK_SIZE; ++i) 
	{
        printf("%02x", block[i]);
    }
    printf("\n");
}
void computeCBCMAC(unsigned char *T, const unsigned char *X, const unsigned char *K) 
{
    unsigned char IV[BLOCK_SIZE] = {0}; 
    unsigned char temp[BLOCK_SIZE];
    for (int i = 0; i < BLOCK_SIZE; ++i) 
	{
        temp[i] = IV[i] ^ X[i];
    }
    encrypt(T, temp, K);
}
int main() 
{
    unsigned char K[KEY_SIZE] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 
                                 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f}; 
    unsigned char X[BLOCK_SIZE] = "example message"; 
    unsigned char T[BLOCK_SIZE]; 
    unsigned char X2[BLOCK_SIZE]; 
    unsigned char twoBlockMAC[BLOCK_SIZE]; 
    computeCBCMAC(T, X, K);
    printf("MAC for one-block message X: ");
    printBlock(T);
    for (int i = 0; i < BLOCK_SIZE; ++i) 
	{
        X2[i] = X[i] ^ T[i];
    }
    unsigned char temp[BLOCK_SIZE];
    for (int i = 0; i < BLOCK_SIZE; ++i) 
	{
        temp[i] = X[i];
    }
    encrypt(temp, temp, K);
    for (int i = 0; i < BLOCK_SIZE; ++i) 
	{
        temp[i] = X2[i] ^ temp[i];
    }
    encrypt(twoBlockMAC, temp, K);
    printf("MAC for two-block message X || (X ? T): ");
    printBlock(twoBlockMAC);
    return 0;
}

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define R_64  0x1B
#define R_128 0x87
void print_block(uint8_t *block, size_t size) 
{
    for (size_t i = 0; i < size; i++) 
	{
        printf("%02X", block[i]);
    }
    printf("\n");
}
void left_shift(uint8_t *input, uint8_t *output, size_t size) 
{
    uint8_t carry = 0;
    for (int i = size - 1; i >= 0; i--) 
	{
        output[i] = (input[i] << 1) | carry;
        carry = (input[i] & 0x80) ? 1 : 0;
    }
}
void generate_subkeys(uint8_t *L, size_t size, uint8_t *K1, uint8_t *K2, uint8_t R) 
{
    left_shift(L, K1, size);
    if (L[0] & 0x80) 
	{
        K1[size - 1] ^= R;
    }
    
    left_shift(K1, K2, size);
    if (K1[0] & 0x80) 
	{
        K2[size - 1] ^= R;
    }
}
int main() 
{
    uint8_t L_64[8] = {0}; 
    uint8_t L_128[16] = {0}; 
    memset(L_64, 0xAB, 8); 
    memset(L_128, 0xCD, 16); 
    uint8_t K1_64[8], K2_64[8];
    uint8_t K1_128[16], K2_128[16];
    generate_subkeys(L_64, 8, K1_64, K2_64, R_64);
    printf("K1 (64-bit): ");
    print_block(K1_64, 8);
    printf("K2 (64-bit): ");
    print_block(K2_64, 8);
    generate_subkeys(L_128, 16, K1_128, K2_128, R_128);
    printf("K1 (128-bit): ");
    print_block(K1_128, 16);
    printf("K2 (128-bit): ");
    print_block(K2_128, 16);
    return 0;
}


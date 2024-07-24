#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
unsigned long mod_exp(unsigned long base, unsigned long exp, unsigned long mod) {
    unsigned long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}
unsigned long encrypt_char(char c, unsigned long e, unsigned long n) {
    unsigned long m = (unsigned long)(toupper(c) - 'A');
    return mod_exp(m, e, n);
}
char decrypt_char(unsigned long ciphertext, unsigned long e, unsigned long n) {
	unsigned long m;
    for (m = 0; m < 26; m++) {
        if (mod_exp(m, e, n) == ciphertext) {
            return (char)(m + 'A');
        }
    }
    return '?';  
}

int main() {
    unsigned long n, e;
    char message[100], encrypted_message[100];
    unsigned long ciphertexts[100];
    int i;
    n = 3233; 
    e = 17;   
    printf("Enter a message to encrypt (only alphabetic characters): ");
    scanf("%s", message);

    for (i = 0; message[i] != '\0'; i++) {
        ciphertexts[i] = encrypt_char(message[i], e, n);
        encrypted_message[i] = (char)ciphertexts[i];
    }
    encrypted_message[i] = '\0'    ;

    printf("Encrypted message: ");
    for (i = 0; encrypted_message[i] != '\0'; i++) {
        printf("%lu ", ciphertexts[i]);
    }
    printf("\n");
    printf("Decrypted message: ");
    for (i = 0; encrypted_message[i] != '\0'; i++) {
        printf("%c", decrypt_char(ciphertexts[i], e, n));
    }
    printf("\n");

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define MAX_TEXT_SIZE 1024
void generateKeyStream(int *keyStream, int length);
void encrypt(char *plaintext, char *ciphertext, int *keyStream);
void decrypt(char *ciphertext, char *plaintext, int *keyStream);

int main() {
    char plaintext[MAX_TEXT_SIZE], ciphertext[MAX_TEXT_SIZE];
    int keyStream[MAX_TEXT_SIZE];

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 
    int length = strlen(plaintext);
    generateKeyStream(keyStream, length);
    printf("Generated key stream: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", keyStream[i]);
    }
    printf("\n");
    encrypt(plaintext, ciphertext, keyStream);
    printf("Encrypted ciphertext: %s\n", ciphertext);
    decrypt(ciphertext, plaintext, keyStream);
    printf("Decrypted plaintext: %s\n", plaintext);

    return 0;
}
void generateKeyStream(int *keyStream, int length) {
    srand(time(0));  

    for (int i = 0; i < length; i++) {
        keyStream[i] = rand() % 26;
    }
}
void encrypt(char *plaintext, char *ciphertext, int *keyStream) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char offset = isupper(plaintext[i]) ? 'A' : 'a';
            ciphertext[i] = ((plaintext[i] - offset + keyStream[i]) % 26) + offset;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}
void decrypt(char *ciphertext, char *plaintext, int *keyStream) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char offset = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = ((ciphertext[i] - offset - keyStream[i] + 26) % 26) + offset;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}


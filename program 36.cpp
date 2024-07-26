#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int gcd(int a, int b);
int modInverse(int a, int m);
void affineEncrypt(char *plaintext, char *ciphertext, int a, int b);
void affineDecrypt(char *ciphertext, char *plaintext, int a, int b);

int main() {
    char plaintext[1024], ciphertext[1024];
    int a, b;

    printf("Enter the value of a (must be coprime with 26): ");
    scanf("%d", &a);
    printf("Enter the value of b: ");
    scanf("%d", &b);
    printf("Enter the plaintext: ");
    scanf("%s", plaintext);
    if (gcd(a, 26) != 1) {
        printf("Error: a and 26 are not coprime. Please choose a different a.\n");
        return 1;
    }

    affineEncrypt(plaintext, ciphertext, a, b);
    printf("Encrypted ciphertext: %s\n", ciphertext);

    affineDecrypt(ciphertext, plaintext, a, b);
    printf("Decrypted plaintext: %s\n", plaintext);

    return 0;
}
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}
void affineEncrypt(char *plaintext, char *ciphertext, int a, int b) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char offset = isupper(plaintext[i]) ? 'A' : 'a';
            ciphertext[i] = ((a * (plaintext[i] - offset) + b) % 26) + offset;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}
void affineDecrypt(char *ciphertext, char *plaintext, int a, int b) {
    int a_inv = modInverse(a, 26);
    if (a_inv == -1) {
        printf("Error: Inverse of a does not exist.\n");
        exit(1);
    }

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char offset = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = (a_inv * (ciphertext[i] - offset - b + 26) % 26) + offset;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}


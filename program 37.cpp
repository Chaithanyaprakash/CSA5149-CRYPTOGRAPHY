#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define ALPHABET_SIZE 26
#define MAX_TEXT_SIZE 1024
const float englishFrequencies[ALPHABET_SIZE] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153,
    0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056,
    2.758, 0.978, 2.360, 0.150, 1.974, 0.074
};
void analyzeFrequency(const char *text, float *frequencies);
void getTopNDecryption(char *ciphertext, int n);
int compareFrequencies(const void *a, const void *b);
void decrypt(char *ciphertext, char *plaintext, const int *mapping);
void sortFrequencies(float *frequencies, int *indices);

int main() {
    char ciphertext[MAX_TEXT_SIZE];
    int topN;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';

    printf("Enter the number of top possible plaintexts to display: ");
    scanf("%d", &topN);

    getTopNDecryption(ciphertext, topN);

    return 0;
}
void analyzeFrequency(const char *text, float *frequencies) {
    int counts[ALPHABET_SIZE] = {0};
    int total = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            counts[toupper(text[i]) - 'A']++;
            total++;
        }
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        frequencies[i] = (float)counts[i] / total * 100;
    }
}
int compareFrequencies(const void *a, const void *b) {
    float diff = *(float*)b - *(float*)a;
    return (diff > 0) - (diff < 0);
}
void decrypt(char *ciphertext, char *plaintext, const int *mapping) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char letter = toupper(ciphertext[i]) - 'A';
            plaintext[i] = mapping[letter] + 'A';
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}
void sortFrequencies(float *frequencies, int *indices) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        indices[i] = i;
    }

    qsort(frequencies, ALPHABET_SIZE, sizeof(float), compareFrequencies);
}
void getTopNDecryption(char *ciphertext, int n) {
    float frequencies[ALPHABET_SIZE];
    int sortedIndices[ALPHABET_SIZE];
    int mapping[ALPHABET_SIZE];
    char plaintext[MAX_TEXT_SIZE];
    analyzeFrequency(ciphertext, frequencies);
    sortFrequencies(frequencies, sortedIndices);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            mapping[sortedIndices[j]] = (j + i) % ALPHABET_SIZE;
        }

        decrypt(ciphertext, plaintext, mapping);
        printf("Possible plaintext #%d: %s\n", i + 1, plaintext);
    }
}


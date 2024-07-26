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
void decrypt(char *ciphertext, char *plaintext, int shift);
float scoreText(const char *text);
void getTopNDecryption(char *ciphertext, int n);

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
void decrypt(char *ciphertext, char *plaintext, int shift) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char offset = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = ((ciphertext[i] - offset - shift + ALPHABET_SIZE) % ALPHABET_SIZE) + offset;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}
float scoreText(const char *text) {
    int counts[ALPHABET_SIZE] = {0};
    int total = 0;
    float score = 0.0;

    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            counts[toupper(text[i]) - 'A']++;
            total++;
        }
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        float frequency = (float)counts[i] / total * 100;
        score += frequency * englishFrequencies[i];
    }

    return score;
}
void getTopNDecryption(char *ciphertext, int n) {
    char plaintext[MAX_TEXT_SIZE];
    float scores[ALPHABET_SIZE];
    int shifts[ALPHABET_SIZE];
    for (int shift = 0; shift < ALPHABET_SIZE; shift++) {
        decrypt(ciphertext, plaintext, shift);
        scores[shift] = scoreText(plaintext);
        shifts[shift] = shift;
    }
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (scores[i] < scores[j]) {
                float tempScore = scores[i];
                scores[i] = scores[j];
                scores[j] = tempScore;

                int tempShift = shifts[i];
                shifts[i] = shifts[j];
                shifts[j] = tempShift;
            }
        }
    }
    for (int i = 0; i < n && i < ALPHABET_SIZE; i++) {
        decrypt(ciphertext, plaintext, shifts[i]);
        printf("Possible plaintext #%d (shift %d): %s\n", i + 1, shifts[i], plaintext);
    }
}


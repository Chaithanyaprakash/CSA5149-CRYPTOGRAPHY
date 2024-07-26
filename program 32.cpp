#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
void dsa_sign(const char *message, char *signature) 
{
 
    srand(time(NULL));
    int k = rand();
    snprintf(signature, 64, "DSA_SIG_%s_%d", message, k);
}
void rsa_sign(const char *message, char *signature) 
{
    snprintf(signature, 64, "RSA_SIG_%s", message);
}

int main() 
{
    const char *message = "Hello, World!";
    char dsa_signature1[64];
    char dsa_signature2[64];
    char rsa_signature1[64];
    char rsa_signature2[64];
    dsa_sign(message, dsa_signature1);
    dsa_sign(message, dsa_signature2);
    rsa_sign(message, rsa_signature1);
    rsa_sign(message, rsa_signature2);
    printf("DSA Signature 1: %s\n", dsa_signature1);
    printf("DSA Signature 2: %s\n", dsa_signature2);
    printf("RSA Signature 1: %s\n", rsa_signature1);
    printf("RSA Signature 2: %s\n", rsa_signature2);
    return 0;
}


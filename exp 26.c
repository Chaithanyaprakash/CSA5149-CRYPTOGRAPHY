#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int mod_exp(int base, int exponent, int modulus) {
    int result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exponent /= 2;
    }
    return result;
}

int mod_inverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        
        q = a / m;
        t = m;

        m = a % m, a = t;
        t = x0;

        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0)
        x1 += m0;

    return x1;
}

void generate_keys(int *n, int *e, int *d, int p, int q) {
    *n = p * q;
    int phi = (p - 1) * (q - 1);
    *e = 3;
    while (gcd(*e, phi) != 1) {
        (*e)++;
    }

    *d = mod_inverse(*e, phi);
}
int encrypt(int msg, int e, int n) {
    return mod_exp(msg, e, n);
}
int decrypt(int cipher, int d, int n) {
    return mod_exp(cipher, d, n);
}

int main() {
    
    int p = 61, q = 53;
    int n, e, d;
    generate_keys(&n, &e, &d, p, q);

    printf("Public Key: (n = %d, e = %d)\n", n, e);
    printf("Private Key: (n = %d, d = %d)\n", n, d);

    int msg = 42;
    printf("Original Message: %d\n", msg);

    int cipher = encrypt(msg, e, n);
    printf("Encrypted Message: %d\n", cipher);

    int decrypted_msg = decrypt(cipher, d, n);
    printf("Decrypted Message: %d\n", decrypted_msg);

    return 0;
}

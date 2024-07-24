#include <stdio.h>
#include <stdlib.h>
unsigned long gcd(unsigned long a, unsigned long b) {
    while (b != 0) {
        unsigned long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

unsigned long mod_inverse(unsigned long e, unsigned long phi) {
    long t = 0, newt = 1;
    long r = phi, newr = e;
    while (newr != 0) {
        long quotient = r / newr;
        long temp = t;
        t = newt;
        newt = temp - quotient * newt;
        temp = r;
        r = newr;
        newr = temp - quotient * newr;
    }
    if (r > 1) return -1;  
    if (t < 0) t += phi;
    return t;
}

int main() {
    unsigned long n, e, known_plaintext, p, q, phi, d;

    printf("Enter value of n (product of two primes p and q): ");
    scanf("%lu", &n);
    printf("Enter value of e (public exponent): ");
    scanf("%lu", &e);
    printf("Enter known plaintext block that has a common factor with n: ");
    scanf("%lu", &known_plaintext);
    
    unsigned long gcd_result = gcd(known_plaintext, n);
    if (gcd_result == 1) {
        printf("No common factor found with n.\n");
        return 1;
    }

    p = gcd_result;
    q = n / p;
    printf("Found prime factors p: %lu and q: %lu\n", p, q);

    phi = (p - 1) * (q - 1);

    
    d = mod_inverse(e, phi);
    if (d == (unsigned long)-1) {
        printf("Error computing modular inverse. e may not be invertible.\n");
        return 1;
    }

    printf("The private key d is: %lu\n", d);
    return 0;
}

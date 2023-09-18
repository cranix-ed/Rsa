#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to check if a number is prime
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;

    if (n % 2 == 0 || n % 3 == 0) return false;

    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }

    return true;
}

// Function to generate a random prime number
int generatePrime() {
    int prime;
    do {
        prime = rand() % 100 + 50; // Generate a random number between 50 and 149
    } while (!isPrime(prime));
    return prime;
}

// Function to calculate the greatest common divisor (GCD) of two numbers
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    // Seed the random number generator
    srand(time(0));

    // Generate two random prime numbers
    int p = generatePrime();
    int q = generatePrime();

    // Calculate n and phi(n)
    int n = p * q;
    int phi = (p - 1) * (q - 1);

    // Choose an encryption key e (1 < e < phi) such that e and phi are coprime
    int e;
    do {
        e = rand() % phi;
    } while (gcd(e, phi) != 1);

    // Calculate the decryption key d (d * e ≡ 1 (mod phi))
    int d;
    for (d = 2; d < phi; d++) {
        if ((d * e) % phi == 1) break;
    }

    // Public key: (n, e), Private key: (n, d)
    cout << "Public Key (n, e): (" << n << ", " << e << ")" << endl;
    cout << "Private Key (n, d): (" << n << ", " << d << ")" << endl;

    // Encryption and decryption
    int plaintext;
    cout << "Enter a message (integer): ";
    cin >> plaintext;

    int ciphertext = (int)pow(plaintext, e) % n;
    cout << "Ciphertext: " << ciphertext << endl;

    int decryptedtext = (int)pow(ciphertext, d) % n;
    cout << "Decrypted Text: " << decryptedtext << endl;

    return 0;
}

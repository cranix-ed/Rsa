#include <iostream>

using namespace std;

int gcd(int a, int b);
int inverse(int e, int phi);
void getMessage(int &p, int &q, int &m);
bool isPrime(int n);
void generateKeyPair(int p, int q, int &n, int &e, int &d);
int encrypt(int m, int e, int n);
int decrypt(int c, int d, int n);

int main() {
    int p, q, m, c;
    int n, e, d;

    getMessage(p, q, m);

    if (!isPrime(p) || !isPrime(q) || p == q) {
        cout << "p and q must be distinct prime numbers.\n";
        return 1;
    }

    generateKeyPair(p, q, n, e, d);

    c = encrypt(m, e, n);

    cout << "Encrypt c: " << c << endl;
    cout << "Decrypt m: " << decrypt(c, d, n) << endl;

    return 0;
}

int gcd(int a, int b) {
    while (b != 0) {
        int temp = a;
        a = b;
        b = temp % b;
    }
    return a;
}

void getMessage(int &p, int &q, int &m) {
    cout << "Enter two prime numbers: ";
    cin >> p >> q;
    cout << "Enter the message to be encrypted: ";
    cin >> m;
}

bool isPrime(int n) {
    if (n <= 1)
        return false;

    if (n == 2)
        return true;

    if (n % 2 == 0)
        return false;

    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0)
            return false;
    }

    return true;
}

int inverse(int e, int phi) {
    int d = 0;
    int x1 = 0;
    int x2 = 1;
    int tempPhi = phi;

    while (e > 0) {
        int temp1 = phi / e;
        int temp2 = tempPhi - temp1 * e;
        tempPhi = e;
        e = temp2;
        int x = x1 - x2 * temp2;
        x1 = x2;
        x2 = x;
    }

    if (tempPhi == 1)
        return x2;

    return 0;
}

void generateKeyPair(int p, int q, int &n, int &e, int &d) {
    n = p * q;
    int phi = (p - 1) * (q - 1);

    for (int i = 2; i < phi; i++) {
        if (gcd(i, phi) == 1) {
            e = i;
            break;
        }
    }

    d = inverse(e, phi);

    cout << "Public key: (" << e << ", " << n << ")\n";
    cout << "Private key: (" << d << ", " << n << ")\n";
}

int encrypt(int m, int e, int n) {
    int c = 1;
    for (int i = 0; i < e; i++) {
        c = (c * m) % n;
    }
    return c;
}

int decrypt(int c, int d, int n) {
    int m = 1;
    for (int i = 0; i < d; i++) {
        m = (m * c) % n;
    }
    return m;
}

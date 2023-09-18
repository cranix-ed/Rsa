#include <iostream>

using namespace std;

int gcd(int a, int b);
void getMessage(int &p, int &q, int &m);
bool primeNumber(int n);
int inverse(int e, int phi);
void generateKeyPair(int p, int q, int &n, int &e, int &d);
int encrypt( int m, int e, int n);
int decrypt(int c, int d, int n);

int main() {
    int p, q, m, c;
    int n, e, d;
    
    getMessage(p, q, m);

    if(!primeNumber(p) || !primeNumber(q) || p == q) {
        cout << "p and q must be distinct prime number.";
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
    cout << "Enter two prime number: ";
    cin >> p >> q;   
    cout << "Enter string you want cryptography: ";
    cin >> m;
}

bool primeNumber(int n) {
    if(n <= 1) {
        return false;
    }

    if(n == 2) {
        return true;
    }

    for(int i = 3; i < (n / 2); i++) {
        if(n % i == 0) {
            return false;
        }
    }
    return true;
}

int inverse(int e, int phi) {
    e = e % phi;
    for(int i = 1; i < phi; i++) {
        if((e * i) % phi == 1) {
            return i;
        }
    }
    return -1;
}



void generateKeyPair(int p, int q, int &n, int &e, int &d) {
    n = p * q;
    int phi = (p - 1) * (q -1);

    for(int i = 2; i < phi; i++) {
        if(gcd(i, phi) == 1) {
            e = i;
            break;
        }
    }

    d = inverse(e, phi);

    cout << "Public key: (" << e << ", " << n << ")" << endl;
    
    if(d != -1) {
        cout << "Private key: (" << d << ", " << n << ")" << endl;
    } else {
        cout << "Error.";
    }
}

int encrypt(int m, int e, int n) {
    long long c = 1;
    for(int i = 0; i < e; i++) {
        c = (c * m) % n;
    }
    return c;
}

int decrypt(int c, int d, int n) {
    long long m = 1;
    for(int i = 0; i < d; i++) {
        m = (m * c) % n;
    }
    return m;
}
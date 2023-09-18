#include <iostream>
#include <string>

using namespace std;

// Affine cipher encryption function 
string encrypt(string text, int a, int b) {
  string result = "";
  
  for(int i=0; i<text.length(); i++) {
    if (isupper(text[i])) {
      result += char(int(a * (text[i] - 'A') + b) % 26 + 'A'); 
    }
    else {
      result += char(int(a * (text[i] - 'a') + b) % 26 + 'a');
    }
  }

  return result;
}

// Affine cipher decryption function
string decrypt(string cipher, int a, int b) {
  string plain = "";
  
  // Find modular inverse of a
  int a_inv = 0;
  for(int i=0; i<26; i++) {
    if ((a*i) % 26 == 1) {
      a_inv = i;
      break;
    } 
  }
  
  for(int i=0; i<cipher.length(); i++) {
    if (isupper(cipher[i])) {
      plain += char(int(a_inv * (cipher[i] - 'A' - b)) % 26 + 'A');
    }
    else {
      plain += char(int(a_inv * (cipher[i] - 'a' - b)) % 26 + 'a'); 
    }
  }

  return plain;
}

int main() {
  string text = "SECRET MESSAGE";
  
  int a = 3; 
  int b = 5;

  string cipher = encrypt(text, a, b);

  cout << "Encrypted: " << cipher << endl;

  string plain = decrypt(cipher, a, b);

  cout << "Decrypted: " << plain << endl;
  
  return 0;
}
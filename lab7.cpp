#include <iostream>
#include <string>
using namespace std;

string caesarCipher(string text, int shift) {
    string result = "";
    for (char& c : text) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            c = (c - base + shift) % 26 + base;
        }
        result += c;
    }
    return result;
}

string rleEncode(const string& str) {
    string encoded = "";
    int count = 1;
    for (size_t i = 0; i < str.length(); i++) {
        if (i + 1 < str.length() && str[i] == str[i + 1]) {
            count++;
        } else {
            encoded += str[i];
            encoded += to_string(count);
            count = 1;
        }
    }
    return encoded;
}

string rleDecode(const string& str) {
    string decoded = "";
    for (size_t i = 0; i < str.length(); i++) {
        char ch = str[i];
        int count = 0;
        while (i + 1 < str.length() && isdigit(str[i + 1])) {
            count = count * 10 + (str[++i] - '0');
        }
        decoded += string(count, ch);
    }
    return decoded;
}

string encrypt(const string& text, int shift) {
    string caesarEncrypted = caesarCipher(text, shift);
    return rleEncode(caesarEncrypted);
}

string decrypt(const string& text, int shift) {
    string rleDecoded = rleDecode(text);
    return caesarCipher(rleDecoded, 26 - shift);
}

int main() {
    string text;
    int shift;
    cout << "Enter the text: ";
    getline(cin, text);
    cout << "Enter the Caesar shift value: ";
    cin >> shift;

    string encryptedText = encrypt(text, shift);
    cout << "Encrypted text: " << encryptedText << endl;

    string decryptedText = decrypt(encryptedText, shift);
    cout << "Decrypted text: " << decryptedText << endl;

    return 0;
}

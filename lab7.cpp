#include <iostream>
#include <string>
#include <cctype>
using namespace std;
class CaesarCipher {
public:
    CaesarCipher(int shift) : shiftValue(shift) {}
    string encrypt(const string &text) {
        string encryptedText = "";
        for (char ch : text) {
            if (isalpha(ch)) {
                char base = islower(ch) ? 'a' : 'A';
                encryptedText += (ch - base + shiftValue) % 26 + base;
            } else {
                encryptedText += ch;
            }
        }
        return encryptedText;
    }
    string decrypt(const string &text) {
        string decryptedText = "";
        for (char ch : text) {
            if (isalpha(ch)) {
                char base = islower(ch) ? 'a' : 'A';
                decryptedText += (ch - base - shiftValue + 26) % 26 + base;
            } else {
                decryptedText += ch;
            }
        }
        return decryptedText;
    }

private:
    int shiftValue;
};

string encRLE(const string& source) {
    string encoded = "";
    int count = 1;

    for (int i = 1; i < source.length(); i++) {
        if (source[i] == source[i - 1]) {
            count++;
        } else {
            while (count > 255) {
                encoded += source[i - 1];
                encoded += "255";
                count -= 255;
            }
            encoded += source[i - 1];
            encoded += to_string(count);
            count = 1;
        }
    }

    while (count > 255) {
        encoded += source[source.length() - 1];
        encoded += "255";
        count -= 255;
    }
    encoded += source[source.length() - 1];
    encoded += to_string(count);

    return encoded;
}
string decRLE(const string& encoded) {
    string decoded = "";
    int i = 0;

    while (i < encoded.length()) {
        char character = encoded[i++];
        int count = 0;

        while (i < encoded.length() && isdigit(encoded[i])) {
            count = count * 10 + (encoded[i] - '0');
            i++;
        }
        for (int j = 0; j < count; j++) {
            decoded += character;
        }
    }
    return decoded;
}

int main() {
    string text = "Hello, World!";
    int shiftValue = 3;

    CaesarCipher cipher(shiftValue);
    cout << "Plaintext: " << text << endl;

    string caesarEncrypted = cipher.encrypt(text);
    cout << "Caesar Encrypted: " << caesarEncrypted << endl;

    string caesarDecrypted = cipher.decrypt(caesarEncrypted);
    cout << "Caesar Decrypted: " << caesarDecrypted << endl;

    string rleEncoded = encRLE(caesarEncrypted);
    cout << "RLE Encoded: " << rleEncoded << endl;

    string rleDecoded = decRLE(rleEncoded);
    cout << "RLE Decoded: " << rleDecoded << endl;

    return 0;
}

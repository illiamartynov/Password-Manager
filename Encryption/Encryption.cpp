#include "Encryption.h"
using namespace std;

std::string Encryption::encryptToBinary(const string& text) {
    string binaryText;
    for (char c : text) {
        for (int i = 7; i >= 0; --i) {
            char bit = ((c >> i) & 1) + '0';
            binaryText += bit;
        }
    }
    return binaryText;
}



std::string Encryption::decryptFromBinary(const std::string& binaryText, const std::string& password, const std::string& masterPassword) {
    int q = 0;
    std::string text;
    if(password == masterPassword){
        q = 8;
    } else{
        if (password.length() == masterPassword.length()) {
            q = password[0] + password[1] - password[2] + password[3] - password[4] - password[5] + password[6];
        } else if (password.length() > masterPassword.length()) {
            q = password[0] + password[1] - password[2] + password[3] - password[4] - password[5] + password[6];
            for (size_t i = 7; i < password.length(); ++i) {
                if (i % 2 == 0) {
                    q += password[i];
                } else {
                    q -= password[i];
                }
            }
        }else if (password.length() < masterPassword.length()) {
            q = password[0] + password[1] - password[2] + password[3] - password[4] - password[5];
            for (size_t i = 6; i < 7 - password.length(); ++i) {
                q += i;
            }
        }

        if (q <= 1) {
            int passwordSum = 0;
            for (char ch : password) {
                passwordSum += ch;
            }

            while (q <= 1) {
                q += passwordSum;
                q /= 2;
            }
        }

    }

    for (size_t i = 0; i < binaryText.length(); i += 8) {
        char c = 0;
        for (int j = 0; j < q; ++j) {
            c = (c << 1) | (binaryText[i + j] - '0');
        }
        text += c;
    }
    return text;
}


std::string Encryption::encryptTimestamp() {
    time_t now = time(nullptr);
    string timestamp = ctime(&now);
    string encryptedTimestamp = Encryption::encryptToBinary("Timestamp: " + timestamp);
    return  encryptedTimestamp;
}

std::string Encryption::decryptTimestamp(const string& encryptedTimestamp, const string& password, const string& masterPassword ) {
    return Encryption::decryptFromBinary(encryptedTimestamp, password, masterPassword);
}

std::string Encryption::decryptTimestamp(const string& encryptedTimestamp) {
    string text;
    for (size_t i = 0; i < encryptedTimestamp.length(); i += 8) {
        char c = 0;
        for (int j = 0; j < 8; ++j) {
            c = (c << 1) | (encryptedTimestamp[i + j] - '0');
        }
        text += c;
    }
    return text;
}
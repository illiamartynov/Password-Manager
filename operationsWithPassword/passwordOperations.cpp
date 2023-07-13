
#include <fstream>
#include <iostream>
#include <random>
#include "passwordOperations.h"

int passwordOperations::isPasswordSafe(const std::string &password) {
    int score = 0;

    if (password.length() >= 8) {
        score++;
    }

    bool hasUppercase = false;
    for (char c: password) {
        if (isupper(c)) {
            hasUppercase = true;
            break;
        }
    }
    if (hasUppercase) {
        score++;
    }

    bool hasLowercase = false;
    for (char c: password) {
        if (islower(c)) {
            hasLowercase = true;
            break;
        }
    }
    if (hasLowercase) {
        score++;
    }

    bool hasDigit = false;
    int digitCount = 0;
    for (char c: password) {
        if (isdigit(c)) {
            hasDigit = true;
            digitCount++;
        }
    }
    if (hasDigit) {
        score++;
    }

    bool hasSpecialChar = false;
    for (char c: password) {
        if (!isalnum(c)) {
            hasSpecialChar = true;
            break;
        }
    }
    if (hasSpecialChar) {
        score++;
    }

    return score;
}

std::string passwordOperations::generatePassword(int length, bool includeUppercase, bool includeSpecialChars) {
    using namespace std;
    string password;
    string lowercaseLetters = "abcdefghijklmnopqrstuvwxyz";
    string uppercaseLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string specialChars = "!@#$%^&*";

    string characters = lowercaseLetters;
    if (includeUppercase)
        characters += uppercaseLetters;
    if (includeSpecialChars)
        characters += specialChars;

    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(0, characters.length() - 1);

    bool passwordSafe = false;
    while (!passwordSafe) {
        password = "";
        for (int i = 0; i < length; i++) {
            int randomIndex = distribution(generator);
            password += characters[randomIndex];
        }

        int score = isPasswordSafe(password);

        if (score < 4) {
            cout << "Generated password is not strong enough." << endl;
            cout << "Reason: Score " << score;
            if (!includeUppercase)
                cout << ", no uppercase letters";
            if (!includeSpecialChars)
                cout << ", no special characters";
            cout << endl;

            char choice;
            cout << "Do you want to continue with this password? (Y/N): ";
            cin.ignore();
            cin >> choice;

            if (choice == 'Y' || choice == 'y') {
                passwordSafe = true;
            } else if (choice == 'N' || choice == 'n') {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please enter a new password: ";
                cin >> password;
                passwordSafe = true;
            } else {
                cout << "Invalid choice. Please try again." << endl;
            }
        } else {
            passwordSafe = true;
        }
    }

    return password;
}

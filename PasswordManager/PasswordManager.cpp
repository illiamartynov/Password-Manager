#include "PasswordManager.h"
#include "../Encryption/Encryption.h"
#include "../dataOperations//dataOperations.h"
#include "../operationsWithPassword///passwordOperations.h"
#include "../additionalMethods/aditionalMethods.h"
#include "../password/Password.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <limits>

using namespace std;
void PasswordManager::searchPasswords(const string& password, const string& siteTerm, const string& loginTerm, const string& categoryTerm, const string& masterPassword, const string& filename) {


    ifstream file(("../txtFiles/" + filename + ".txt"));
    if (!file) {
        cout << "Error opening file." << endl;
        return;
    }

    string line;
    cout << left << setw(20) << "Site" << setw(20) << "Login" << setw(20) << "Category" << setw(25) << "Decrypted text" << endl;

    while (getline(file, line)) {
        size_t comma1 = line.find(",");
        size_t comma2 = line.find(",", comma1 + 1);
        size_t comma3 = line.find(",", comma2 + 1);

        string encryptedSite = line.substr(0, comma1);
        string encryptedLogin = line.substr(comma1 + 1, comma2 - comma1 - 1);
        string encryptedCategory = line.substr(comma2 + 1, comma3 - comma2 - 1);
        const string& encryptedText = line.substr(comma3 + 1);

        string site = Encryption::decryptFromBinary(encryptedSite, password, masterPassword);
        string login = Encryption::decryptFromBinary(encryptedLogin, password, masterPassword);
        string category = Encryption::decryptFromBinary(encryptedCategory, password, masterPassword);
        string decryptedText = Encryption::decryptFromBinary(encryptedText, password, masterPassword);

        bool match = true;
        if (!siteTerm.empty() && site.find(siteTerm) == string::npos) {
            match = false;
        }
        if (!loginTerm.empty() && login.find(loginTerm) == string::npos) {
            match = false;
        }
        if (!categoryTerm.empty() && category.find(categoryTerm) == string::npos) {
            match = false;
        }

        if (match) {
            cout << left << setw(20) << site << setw(20) << login << setw(20) << category << setw(25) << decryptedText << endl;
        }
    }

    file.close();

}



void PasswordManager::sortPasswords(const string& password, const string& sortBy1, const string& sortBy2, const string& masterPassword, const string& filename) {
    vector<Password> passwords;

    ifstream file("../txtFiles/" + filename + ".txt");
    if (!file) {
        cout << "Error opening file." << endl;
        return;
    }
    if(password != masterPassword){
        cout << "The password is wrong, so it is impossible to sort passwords" << endl;
        return;
    }
    string line;
    getline(file, line);
    while (getline(file, line)) {
        size_t comma1 = line.find(",");
        size_t comma2 = line.find(",", comma1 + 1);
        size_t comma3 = line.find(",", comma2 + 1);

        string encryptedSite = line.substr(0, comma1);
        string encryptedLogin = line.substr(comma1 + 1, comma2 - comma1 - 1);
        string encryptedCategory = line.substr(comma2 + 1, comma3 - comma2 - 1);
        const string& encryptedText = line.substr(comma3 + 1);

        string site = Encryption::decryptFromBinary(encryptedSite, password, masterPassword);
        string login = Encryption::decryptFromBinary(encryptedLogin, password, masterPassword);
        string category = Encryption::decryptFromBinary(encryptedCategory, password, masterPassword);
        string decryptedText = Encryption::decryptFromBinary(encryptedText, password, masterPassword);

        passwords.push_back(Password(site, login, category, decryptedText));
    }

    file.close();

    if (sortBy1 == "site") {
        sort(passwords.begin(), passwords.end(), [](const Password& a, const Password& b) {
            return a.site < b.site;
        });
    } else if (sortBy1 == "login") {
        sort(passwords.begin(), passwords.end(), [](const Password& a, const Password& b) {
            return a.login < b.login;
        });
    } else if (sortBy1 == "category") {
        sort(passwords.begin(), passwords.end(), [](const Password& a, const Password& b) {
            return a.category < b.category;
        });
    }

    if (!sortBy2.empty()) {
        if (sortBy2 == "site") {
            sort(passwords.begin(), passwords.end(), [](const Password& a, const Password& b) {
                return a.site < b.site;
            });
        } else if (sortBy2 == "login") {
            sort(passwords.begin(), passwords.end(), [](const Password& a, const Password& b) {
                return a.login < b.login;
            });
        } else if (sortBy2 == "category") {
            sort(passwords.begin(), passwords.end(), [](const Password& a, const Password& b) {
                return a.category < b.category;
            });
        }
    }

    cout << left << setw(20) << "Site" << setw(20) << "Login" << setw(20) << "Category" << setw(25) << "Decrypted text" << endl;
    for (const auto& password : passwords) {
        cout << left << setw(20) << password.site << setw(20) << password.login << setw(20) << password.category << setw(25) << password.decryptedText << endl;
    }
}


void PasswordManager::addPassword(const string& filename) {
    int passwordOption;
    string site, login, category, passwordForUser;
    getline(cin, site);

    while (site.empty()) {
        cout <<"Please enter a non-empty site: ";
        getline(cin, site);
    }
    cout << "Enter login: ";
    getline(cin, login);
    int categoryOption;
    cout << "Do you want to enter your own category or choose from existing ones?" << endl;
    cout << "1. Enter my own category" << endl;
    cout << "2. Choose from existing categories.txt" << endl;
    cout << "Enter option (1 or 2): ";

    while (!(cin >> categoryOption) || (categoryOption != 1 && categoryOption != 2)) {
        cout << "Invalid option. Please enter either 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cin.ignore();

    if (categoryOption == 1) {
        getline(cin, category);
        while (category.empty()) {
            cout <<"Please enter a non-empty category: ";
            getline(cin, category);
        }
    } else if (categoryOption == 2) {
        cout << "Available categories:" << endl;
        dataOperations::displayCategories("../categories/categories.txt");
        cout << "Enter category number: ";
        int categoryNumber;
        cin >> categoryNumber;
        cin.ignore();

        if (categoryNumber < 1 || categoryNumber > dataOperations::getCategoryCount("../categories/categories.txt")) {
            cout << "Invalid category number. Aborting." << endl;
           return;
        }

        category = dataOperations::getCategoryName(categoryNumber, "../categories/categories.txt");
    } else if(categoryOption == 0) {
        cout << "Invalid option. Aborting." << endl;
       return;
    }else{
        cout << "Invalid option. Aborting." << endl;
        return;
    }


    cout << "Do you want to enter your own password or generate one?" << endl;
    cout << "1. Enter my own password" << endl;
    cout << "2. Generate a password" << endl;
    cout << "Enter option (1 or 2): ";
    while (!(cin >> passwordOption) || (passwordOption != 1 && passwordOption != 2)) {
        cout << "Invalid option. Please enter either 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    if (passwordOption == 1) {
        cout << "Enter password: ";
        cin.ignore();
        getline(cin, passwordForUser);

        int passwordScore = passwordOperations::isPasswordSafe(passwordForUser);
        cout << "Password safety score: " << passwordScore << endl;

        if (passwordScore < 4) {
            char choice;
            cout << "The entered password is not strong enough. Do you want to continue with this password? (Y/N):";
            cin >> choice;

            if (choice == 'N' || choice == 'n') {
                cout << "Please enter new password." << endl;
                bool enterNewPassword = true;
                while (enterNewPassword) {
                    cin.ignore();
                    getline(cin, passwordForUser);

                    passwordScore = passwordOperations::isPasswordSafe(passwordForUser);
                    cout << "New password safety score: " << passwordScore << endl;

                    if (passwordScore >= 4) {
                        enterNewPassword = false;
                    } else {
                        cout << "The entered password is not strong enough. Please enter a new password." << endl;
                    }
                }
            }
        }
    }
    else if (passwordOption == 2) {
        int length;
        bool includeUppercase, includeSpecialChars;
        cout << "Enter password length: (maximum - 60)";
        do {
            cin >> length;

            if (length > 60) {
                cout << "Password is too long. Please enter a shorter password." << endl;
            }
        } while (length > 60);
        cout << "Include uppercase letters? (0 - No, 1 - Yes): ";
        cin >> includeUppercase;
        cout << "Include special characters? (0 - No, 1 - Yes): ";
        cin >> includeSpecialChars;

        passwordForUser = passwordOperations::generatePassword(length, includeUppercase, includeSpecialChars);
        cout << "Generated password: " << passwordForUser << endl;
    } else {
        cout << "Invalid option. Please try again." << endl;
        return;
    }

    string encryptedSite = Encryption::encryptToBinary(site);
    string encryptedLogin = Encryption::encryptToBinary(login);
    string encryptedCategory = Encryption::encryptToBinary(category);

    string encryptedText = Encryption::encryptToBinary(passwordForUser);
    string newEncryptedTimestamp = Encryption::encryptTimestamp();

    ofstream file("../txtFiles/" + filename + ".txt", ios::app);
    if (file.is_open()) {

        std::ifstream file1("../txtFiles/" + filename + ".txt");
        if (file1.is_open()) {
            std::string firstLine;
            std::getline(file1, firstLine);
            if (firstLine.substr(0, 10) == Encryption::encryptToBinary("Timestamp:").substr(0,10)) {
                aditionalMethods::deleteFirstLine("../txtFiles/" + filename + ".txt");
                aditionalMethods::writeNewTimeToFirstLine("../txtFiles/" + filename + ".txt", newEncryptedTimestamp);
                file << encryptedSite << "," << encryptedLogin << "," << encryptedCategory << "," << encryptedText << endl;
            } else {
                file << newEncryptedTimestamp << endl;
                file << encryptedSite << "," << encryptedLogin << "," << encryptedCategory << "," << encryptedText << endl;
            }
        } else {
            std::cout << "Unable to open the file." << std::endl;
        }

        file.close();
        cout << "Text successfully encrypted and appended to file." << endl;
    } else {
        cout << "Error opening file for writing." << endl;
    }
}

void PasswordManager::editPassword(const string &password, const string &masterPassword, const string &filename) {
    if(password != masterPassword){
        cout << "The password is wrong, so it is impossible to edit passwords" << endl;
        return;
    }
    ifstream file(filename);
    if (!file) {
        cout << "Error opening file." << endl;
        return;
    }

    vector<string> lines;
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    cout << "Available passwords:" << endl;
    cout << left << setw(20) << "Site" << setw(20) << "Login" << setw(20) << "Category" << setw(25)
         << "Decrypted text" << endl;
    for (size_t i = 1; i < lines.size(); i++) {
        string encryptedPassword = lines[i];

        stringstream ss(encryptedPassword);
        string word;

        bool isFirstWord = true;

        while (getline(ss, word, ',')) {
            string decryptedWord = Encryption::decryptFromBinary(word, password, masterPassword);

            if (isFirstWord) {
                cout << i << ". "<< setw(20) << decryptedWord ;
                isFirstWord = false;
            } else {
                cout << setw(20) << decryptedWord;
            }
        }

        cout << endl;
    }
    cout << "Enter the number of the password you want to edit: ";
    int passwordNumber;
    cin >> passwordNumber;
    cin.ignore();

    if (passwordNumber < 1 || passwordNumber >= static_cast<int>(lines.size())) {
        cout << "Invalid password number. Aborting." << endl;
        return;
    }

    string selectedPassword = lines[passwordNumber];

    size_t comma1 = selectedPassword.find(",");
    size_t comma2 = selectedPassword.find(",", comma1 + 1);
    size_t comma3 = selectedPassword.find(",", comma2 + 1);
    size_t comma4 = selectedPassword.find(",", comma3 + 1);

    string encryptedSite = selectedPassword.substr(0, comma1);
    string encryptedLogin = selectedPassword.substr(comma1 + 1, comma2 - comma1 - 1);
    string encryptedCategory = selectedPassword.substr(comma2 + 1, comma3 - comma2 - 1);
    string encryptedPassword = selectedPassword.substr(comma3 + 1, comma4 - comma3 - 1);

    string site = Encryption::decryptFromBinary(encryptedSite, password, masterPassword);
    string login = Encryption::decryptFromBinary(encryptedLogin, password, masterPassword);
    string category = Encryption::decryptFromBinary(encryptedCategory, password, masterPassword);
    string decryptedPassword = Encryption::decryptFromBinary(encryptedPassword, password, masterPassword);

    cout << "Current password data:" << endl;
    cout << "Site: " << site << endl;
    cout << "Login: " << login << endl;
    cout << "Category: " << category << endl;
    cout << "Password: " << decryptedPassword << endl;

    cout << "Enter new password data:" << endl;
    cout << "Password: ";
    string newPassword;
    getline(cin, newPassword);

    string newEncryptedPassword = Encryption::encryptToBinary(newPassword);

    string newLine = encryptedSite + "," + encryptedLogin + "," + encryptedCategory + "," + newEncryptedPassword;

    lines[passwordNumber] = newLine;

    ofstream outFile(filename);
    if (!outFile) {
        cout << "Error opening file." << endl;
        return;
    }

    for (const string& line : lines) {
        outFile << line << endl;
    }

    outFile.close();

    cout << "Password updated successfully." << endl;
}

void PasswordManager::deletePasswords(const string &password, const string &masterPassword, const string &filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Error opening file." << endl;
        return;
    }
    if(password != masterPassword){
        cout << "The password is wrong, so it is impossible to delete passwords" << endl;
        return;
    }

    vector<string> lines;
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    cout << "Available passwords:" << endl;
    for (size_t i = 1; i < lines.size(); i++) {
        string encryptedPassword = lines[i];

        stringstream ss(encryptedPassword);
        string word;

        bool isFirstWord = true;

        while (getline(ss, word, ',')) {

            string decryptedWord = Encryption::decryptFromBinary(word, password, masterPassword);

            if (isFirstWord) {
                cout << i + 1 << ". " << decryptedWord;
                isFirstWord = false;
            } else {
                cout << " " << decryptedWord;
            }
        }

        cout << endl;
    }

    cout << "Enter the number(s) of the password(s) you want to delete (comma-separated): ";
    string input;
    getline(cin, input);

    stringstream inputSS(input);
    vector<int> passwordIndices;
    int index;
    while (inputSS >> index) {
        passwordIndices.push_back(index);
        if (inputSS.peek() == ',') {
            inputSS.ignore();
        }
    }

    cout << "Are you sure you want to delete the selected password(s)? (y/n): ";
    char confirmation;
    cin >> confirmation;

    if (confirmation == 'y' || confirmation == 'Y') {
        ofstream outFile(filename);
        if (!outFile) {
            cout << "Error opening file." << endl;
            return;
        }

        bool deleted = false;
        for (size_t i = 0; i < lines.size(); i++) {
            if (find(passwordIndices.begin(), passwordIndices.end(), i + 1) == passwordIndices.end()) {
                outFile << lines[i] << endl;
            } else {
                deleted = true;
            }
        }

        outFile.close();

        if (deleted) {
            cout << "Password(s) deleted successfully." << endl;
        } else {
            cout << "No passwords were deleted." << endl;
        }
    } else {
        cout << "Deletion canceled." << endl;
    }
}

void PasswordManager::addCategory(const string &filename) {
    ofstream file(filename, ios::app);
    if (!file) {
        cout << "Error opening file." << endl;
        return;
    }

    string category;
    cout << "Enter category name: ";
    getline(cin, category);

    file << category << endl;
    file.close();

    cout << "Category added successfully." << endl;
}

void PasswordManager::deleteCategory(const string &categoryName, const string &password, const string &masterPassword,
                                     const string &filename) {
    if(password != masterPassword){
        cout << "The password is wrong, so it is impossible to delete category" << endl;
        return;
    }
    ifstream file(filename);
    if (!file) {
        cout << "Error opening file." << endl;
        return;
    }

    vector<string> lines;
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    bool categoryFound = false;
    for (const string& encryptedPassword : lines) {
        stringstream ss(encryptedPassword);
        string site, login, category, encryptedWord;

        getline(ss, site, ',');
        getline(ss, login, ',');
        getline(ss, category, ',');

        string decryptedCategory = Encryption::decryptFromBinary(category, password, masterPassword);

        if (decryptedCategory == categoryName) {
            categoryFound = true;
            break;
        }
    }


    if (!categoryFound) {
        cout << "No passwords found for the specified category." << endl;
        return;
    }

    vector<string> updatedLines;
    for (const string &encryptedPassword: lines) {
        stringstream ss(encryptedPassword);
        string site, login, category, encryptedWord;

        getline(ss, site, ',');
        getline(ss, login, ',');
        getline(ss, category, ',');

        string decryptedCategory = Encryption::decryptFromBinary(category, password, masterPassword);

        if (decryptedCategory != categoryName) {
            updatedLines.push_back(encryptedPassword);
        }
    }

    ofstream outputFile(filename);
    if (!outputFile) {
        cout << "Error opening file for writing." << endl;
        return;
    }

    for (const string &updatedPassword: updatedLines) {
        outputFile << updatedPassword << endl;
    }

    outputFile.close();

    cout << "Passwords with the specified category have been deleted." << endl;

}


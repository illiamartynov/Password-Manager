
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "runProgramme.h"
#include "../PasswordManager/PasswordManager.h"
#include "../Encryption/Encryption.h"


auto runProgramme::run() -> int {
    using namespace std;
    std::string masterPassword;
    std::string filename;

    int option = -1;
    string password;
    int searchOption;

    int choice1;
    std::vector<std::string> existingFiles;
    std::cout << "Menu:\n";
    std::cout << "1. Create a new file\n";
    std::cout << "2. Choose an existing file\n";
    std::cout << "Enter your choice (1 or 2): ";
    std::cin >> choice1;


    if (choice1 == 1) {
        while (true) {
            std::cout << "Enter filename: ";
            std::cin >> filename;

            if (filename.find(".txt") != std::string::npos) {
                std::cout << "Please enter a filename without the \".txt\" extension.\n";
                continue;
            }

            std::ifstream existingFile("../txtFiles/" + filename + ".txt");
            if (!existingFile.is_open()) {
                existingFile.close();
                break;
            }

            std::cout << "A file with the same name already exists. Please enter a different filename.\n";
        }

        std::ofstream newFile("../txtFiles/" + filename + ".txt");
        if (!newFile.is_open()) {
            std::cout << "Error creating the file.\n";
            return 1;
        }

        newFile.close();
        std::cout << "File created successfully.\n";
    }

    else if (choice1 == 2) {
        std::cout << "Existing files:\n";

        for (const auto& entry : std::filesystem::directory_iterator("../txtFiles")) {
            std::cout << entry.path().filename() << std::endl;
            existingFiles.push_back(entry.path().filename().string());
        }

        if (existingFiles.empty()) {
            std::cout << "No files found in the directory.\n";
            return 1;
        }

        std::cout << "Enter filename: (please enter without \".txt\")";
        std::cin >> filename;

        if (std::find(existingFiles.begin(), existingFiles.end(), (filename + ".txt")) == existingFiles.end()) {
            std::cout << "File does not exist.\n";
            return 1;
        }
    } else {
        std::cout << "Invalid choice.\n";
        return 0;
    }

    std::cout << "Enter password for the file:";
    std::cin >> masterPassword;

    while (option != 0) {
        cout << "Menu:" << endl;
        cout << "1. Add Password" << endl;
        cout << "2. Decrypt" << endl;
        cout << "3. Search Password" << endl;
        cout << "4. Sort passwords" << endl;
        cout << "5. Edit Password" << endl;
        cout << "6. Delete password(s)" << endl;
        cout << "7. Create category" << endl;
        cout << "8. Delete category" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter option :";
        cin >> option;

        if (option == 1) {
            PasswordManager::addPassword(filename);
        } else if (option == 2) {
            cout << "Enter password: ";
            cin.ignore();
            getline(cin, password);

            ifstream file("../txtFiles/" + filename + ".txt");
            if (!file) {
                cout << "Error opening file." << endl;
                return 1;
            }



            string line;
            cout << left << setw(20) << "Site" << setw(20) << "Login" << setw(20) << "Category" << setw(25)
                 << "Decrypted text" << endl;
            if (file.is_open()) {
                std::string firstLine;
                if (std::getline(file, firstLine)) {
                    cout << Encryption::decryptTimestamp(firstLine) << endl;
                } else {
                    std::cout << "File is empty." << std::endl;
                }

            } else {
                std::cout << "Failed to open the file." << std::endl;
            }
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


                    cout << left << setw(20) << site << setw(20) << login << setw(20) << category << setw(25) << decryptedText << endl;
                
            }


            file.close();
        } else if (option == 3) {
            cout << "Enter password: ";
            cin.ignore();
            getline(cin, password);

            cout << "Choose search option:" << endl;
            cout << "1. Search by site" << endl;
            cout << "2. Search by login" << endl;
            cout << "3. Search by category" << endl;
            cout << "Enter option (1, 2, or 3): ";
            cin >> searchOption;
                if (searchOption == 1) {
                    string siteTerm;
                    cout << "Enter site keyword: ";
                    cin.ignore();
                    getline(cin, siteTerm);
                    PasswordManager::searchPasswords(password, siteTerm, "", "", masterPassword, filename);
                } else if (searchOption == 2) {
                    string loginTerm;
                    cout << "Enter login keyword: ";
                    cin.ignore();
                    getline(cin, loginTerm);
                    PasswordManager::searchPasswords(password, "", loginTerm, "", masterPassword, filename);
                } else if (searchOption == 3) {
                    string categoryTerm;
                    cout << "Enter category keyword: ";
                    cin.ignore();
                    getline(cin, categoryTerm);
                    PasswordManager::searchPasswords(password, "", "", categoryTerm, masterPassword, filename);
                } else if(searchOption == 0) {
                    cout << "Invalid option. You entered string. Please try again." << endl;
                    break;
                }else{
                    cout << "Invalid option. Please try again." << endl;
                }

        } else if (option == 4) {
            cout << "Enter password: ";
            cin.ignore();
            getline(cin, password);
            cout << "Choose sorting options:" << endl;
            cout << "1. Sort by site" << endl;
            cout << "2. Sort by login" << endl;
            cout << "3. Sort by category" << endl;
            cout << "Enter first sort option (1, 2, or 3): ";
            int sortOption1;
            cin >> sortOption1;

            string sortBy1;
            if (sortOption1 == 1) {
                sortBy1 = "site";
            } else if (sortOption1 == 2) {
                sortBy1 = "login";
            } else if (sortOption1 == 3) {
                sortBy1 = "category";
            } else if(sortOption1 == 0) {
                cout << "Invalid option. You entered string. Please try again." << endl;
                break;
            }else{
                cout << "Invalid option. Please try again." << endl;
            }

            cout << "Enter second sort option (leave blank for single sorting): ";
            string sortBy2;
            cin.ignore();
            getline(cin, sortBy2);

            PasswordManager::sortPasswords(password, sortBy1, sortBy2, masterPassword, filename);
        } else if (option == 5) {
            cin.ignore();
            cout << "Enter master password: ";
            getline(cin, password);
            PasswordManager::editPassword(password, masterPassword, "../txtFiles/" + filename + ".txt");
        } else if (option == 6) {
            cin.ignore();
            cout << "Enter master password: ";
            getline(cin, password);
            PasswordManager::deletePasswords(password, masterPassword, "../txtFiles/" + filename + ".txt");
        } else if (option == 7) {
            cin.ignore();
            PasswordManager::addCategory("../categories/categories.txt");
        } else if (option == 8) {
            cin.ignore();
            cout << "Enter password: ";
            getline(cin, password);
            cout << "Enter the category name you want to delete: ";
            string categoryName;
            getline(cin, categoryName);

            PasswordManager::deleteCategory(categoryName, password, masterPassword, "../txtFiles/" + filename + ".txt"); // Вызов метода для удаления категории

            cout << "Category deleted successfully." << endl;
        } else if (option == 9) {
            cout << "Exiting program." << endl;
        } else if (option == 0) {
            cout << "Invalid option. Please try again." << endl;
        } else {
            cout << "Unknown option. Please try again." << endl;
        }
    }
    return 0;
}

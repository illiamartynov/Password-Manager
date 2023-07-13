
#include <fstream>
#include <iostream>
#include "dataOperations.h"
using namespace std;

void dataOperations::displayCategories(const std::string& filename) {
    ifstream file(filename);
    if (!file) {
        std::cout << "Error opening file." << endl;
        return;
    }

    string category;
    int categoryNumber = 1;
    while (getline(file, category)) {
        cout << categoryNumber << ". " << category << endl;
        categoryNumber++;
    }

    file.close();
}

int dataOperations::getCategoryCount(const std::string &filename) {
    std::ifstream file(filename);
    if (!file) {
        cout << "Error opening file." << endl;
        return 0;
    }

    int count = 0;
    string line;
    while (getline(file, line)) {
        count++;
    }

    file.close();
    return count;
}

std::string dataOperations::getCategoryName(int categoryNumber, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Error opening file." << endl;
        return "";
    }

    string category;
    int currentCategoryNumber = 1;
    while (getline(file, category)) {
        if (currentCategoryNumber == categoryNumber) {
            file.close();
            return category;
        }
        currentCategoryNumber++;
    }

    file.close();
    return "";
}


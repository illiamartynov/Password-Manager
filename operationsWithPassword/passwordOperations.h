#ifndef PASSWORDMANAGER_PASSWORDOPERATIONS_H
#define PASSWORDMANAGER_PASSWORDOPERATIONS_H

#include <string>

/**
 * @file passwordOperations.h
 * @brief Declaration of the passwordOperations class and its member functions.
 */

/**
 * @class passwordOperations
 * @brief A class that provides password operations.
 */
class passwordOperations {
public:
    /**
     * @brief Check if a password is safe.
     * @param password The password to be checked.
     * @return 1 if the password is safe, 0 otherwise.
     */
    static int isPasswordSafe(const std::string& password);

    /**
     * @brief Generate a password.
     * @param length The length of the generated password.
     * @param includeUppercase Whether to include uppercase letters in the password.
     * @param includeSpecialChars Whether to include special characters in the password.
     * @return The generated password as a string.
     */
    static std::string generatePassword(int length, bool includeUppercase, bool includeSpecialChars);
};

#endif // PASSWORDMANAGER_PASSWORDOPERATIONS_H
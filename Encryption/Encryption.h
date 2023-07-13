#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>

/**
 * @file Encryption.h
 * @brief Declaration of the Encryption class and its member functions.
 */

/**
 * @class Encryption
 * @brief A class that provides encryption and decryption operations.
 */
class Encryption {
public:
    /**
     * @brief Encrypts a text to binary representation.
     * @param text The text to be encrypted.
     * @return The encrypted text in binary format.
     */
    static std::string encryptToBinary(const std::string& text);

    /**
     * @brief Decrypts a binary text using the provided password and master password.
     * @param binaryText The binary text to be decrypted.
     * @param password The password for decryption.
     * @param masterPassword The master password for decryption.
     * @return The decrypted text.
     */
    static std::string decryptFromBinary(const std::string& binaryText, const std::string& password, const std::string& masterPassword);

    /**
     * @brief Encrypts the current timestamp.
     * @return The encrypted timestamp.
     */
    static std::string encryptTimestamp();

    /**
     * @brief Decrypts an encrypted timestamp using the provided password and master password.
     * @param encryptedTimestamp The encrypted timestamp to be decrypted.
     * @param password The password for decryption.
     * @param masterPassword The master password for decryption.
     * @return The decrypted timestamp.
     */
    static std::string decryptTimestamp(const std::string& encryptedTimestamp, const std::string& password, const std::string& masterPassword);

    /**
     * @brief Decrypts an encrypted timestamp.
     * @param encryptedTimestamp The encrypted timestamp to be decrypted.
     * @return The decrypted timestamp.
     */
    static std::string decryptTimestamp(const std::string& encryptedTimestamp);
};

#endif // ENCRYPTION_H

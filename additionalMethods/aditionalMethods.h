#ifndef PASSWORDMANAGER_ADITIONALMETHODS_H
#define PASSWORDMANAGER_ADITIONALMETHODS_H

#include <string>

/**
 * @file aditionalMethods.h
 * @brief Declaration of the aditionalMethods class and its member functions.
 */

/**
 * @class aditionalMethods
 * @brief A class that provides additional methods for file manipulation.
 */
class aditionalMethods {
public:
    /**
     * @brief Delete the first line of the specified file.
     * @param filename The name of the file.
     */
    static void deleteFirstLine(const std::string& filename);

    /**
     * @brief Write a new time value to the first line of the specified file.
     * @param filename The name of the file.
     * @param newTime The new time value to be written.
     */
    static void writeNewTimeToFirstLine(const std::string& filename, const std::string& newTime);
};

#endif // PASSWORDMANAGER_ADITIONALMETHODS_H

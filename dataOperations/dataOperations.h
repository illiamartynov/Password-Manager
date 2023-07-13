#ifndef PASSWORDMANAGER_DATAOPERATIONS_H
#define PASSWORDMANAGER_DATAOPERATIONS_H

#include <string>

/**
 * @file dataOperations.h
 * @brief Declaration of the dataOperations class and its member functions.
 */

/**
 * @class dataOperations
 * @brief A class that provides operations related to data retrieval and manipulation.
 */
class dataOperations {
public:
    /**
     * @brief Display the categories present in the specified filename.
     * @param filename The name of the password manager file.
     */
    static void displayCategories(const std::string& filename);

    /**
     * @brief Get the count of categories in the specified filename.
     * @param filename The name of the password manager file.
     * @return The count of categories.
     */
    static int getCategoryCount(const std::string& filename);

    /**
     * @brief Get the name of the category at the specified category number in the filename.
     * @param categoryNumber The number of the category.
     * @param filename The name of the password manager file.
     * @return The name of the category as a string.
     */
    static std::string getCategoryName(int categoryNumber, const std::string& filename);
};

#endif // PASSWORDMANAGER_DATAOPERATIONS_H

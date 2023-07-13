#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H

#include <string>
#include <vector>
#include <tuple>

/**
 * @brief The PasswordManager class manages passwords and provides various operations on them.
 */
class PasswordManager {
public:
    /**
     * @brief searchPasswords searches for passwords based on search criteria.
     * @param password The master password for accessing the password manager.
     * @param siteTerm The search term for filtering passwords by site.
     * @param loginTerm The search term for filtering passwords by login.
     * @param categoryTerm The search term for filtering passwords by category.
     * @param masterPassword The master password for accessing the password manager file.
     * @param filename The filename of the password manager file.
     */
    static void searchPasswords(const std::string& password, const std::string& siteTerm, const std::string& loginTerm, const std::string& categoryTerm, const std::string& masterPassword, const std::string& filename);

    /**
     * @brief sortPasswords sorts passwords based on specified sorting criteria.
     * @param password The master password for accessing the password manager.
     * @param sortBy1 The first sorting criterion.
     * @param sortBy2 The second sorting criterion.
     * @param masterPassword The master password for accessing the password manager file.
     * @param filename The filename of the password manager file.
     */
    static void sortPasswords(const std::string& password, const std::string& sortBy1, const std::string& sortBy2, const std::string& masterPassword, const std::string& filename);

    /**
     * @brief addPassword adds a new password to the password manager.
     * @param filename The filename of the password manager file.
     */
    static void addPassword(const std::string& filename);

    /**
     * @brief editPassword edits an existing password in the password manager.
     * @param password The master password for accessing the password manager.
     * @param masterPassword The master password for accessing the password manager file.
     * @param filename The filename of the password manager file.
     */
    static void editPassword(const std::string& password, const std::string& masterPassword, const std::string& filename);

    /**
     * @brief deletePasswords deletes passwords based on specified criteria.
     * @param password The master password for accessing the password manager.
     * @param masterPassword The master password for accessing the password manager file.
     * @param filename The filename of the password manager file.
     */
    static void deletePasswords(const std::string& password, const std::string& masterPassword, const std::string& filename);

    /**
     * @brief addCategory adds a new category to the password manager.
     * @param filename The filename of the password manager file.
     */
    static void addCategory(const std::string& filename);

    /**
     * @brief deleteCategory deletes a category and its associated passwords.
     * @param categoryName The name of the category to be deleted.
     * @param password The master password for accessing the password manager.
     * @param masterPassword The master password for accessing the password manager file.
     * @param filename The filename of the password manager file.
     */
    static void deleteCategory(const std::string& categoryName, const std::string& password, const std::string& masterPassword, const std::string& filename);
};

#endif // PASSWORDMANAGER_H

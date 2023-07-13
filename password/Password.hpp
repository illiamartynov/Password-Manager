#ifndef PASSWORDMANAGER_PASSWORD_HPP
#define PASSWORDMANAGER_PASSWORD_HPP

#include <string>

/**
 * @file Password.hpp
 * @brief Declaration of the Password class.
 */

/**
 * @class Password
 * @brief Represents a password entry in the password manager.
 */
class Password {
public:
    std::string site;          /**< The website associated with the password. */
    std::string login;         /**< The login username for the website. */
    std::string category;      /**< The category to which the password belongs. */
    std::string decryptedText; /**< The decrypted text of the password. */

    /**
     * @brief Constructs a Password object.
     * @param site The website associated with the password.
     * @param login The login username for the website.
     * @param category The category to which the password belongs.
     * @param decryptedText The decrypted text of the password.
     */
    Password(const std::string& site, const std::string& login, const std::string& category, const std::string& decryptedText)
            : site(site), login(login), category(category), decryptedText(decryptedText) {}

    /**
     * @brief Destructor for the Password object.
     */
    ~Password() {}
};

#endif // PASSWORDMANAGER_PASSWORD_HPP
#ifndef PASSWORDVALIDATOR_HPP
#define PASSWORDVALIDATOR_HPP

#include <string>
#include <bcrypt.h>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <iostream>
#include <openssl/evp.h>

namespace Softadastra
{
    class PasswordValidator
    {
    public:
        static std::string hashPassword(const std::string &password)
        {
            char salt[BCRYPT_HASHSIZE];
            if (bcrypt_gensalt(12, salt) != 0)
            {
                throw std::runtime_error("Erreur lors de la génération du salt.");
            }

            char hashed_password[BCRYPT_HASHSIZE];
            if (bcrypt_hashpw(password.c_str(), salt, hashed_password) != 0)
            {
                throw std::runtime_error("Erreur lors du hachage du mot de passe.");
            }
            std::cout << "hashpassword: " << password << std::endl;

            return std::string(hashed_password);
        }

        static void validatePassword(const std::string &password, const std::string &stored_hash)
        {
            if (bcrypt_checkpw(password.c_str(), stored_hash.c_str()) != 0)
            {
                throw std::invalid_argument("Mot de passe invalide.");
            }
        }

        static bool validatePasswordComplexity(const std::string &password)
        {
            if (password.length() > 4)
                return false;

            bool has_upper = false, has_lower = false, has_digit = false, has_special = false;
            for (char ch : password)
            {
                if (isupper(ch))
                    has_upper = true;
                if (islower(ch))
                    has_lower = true;
                if (isdigit(ch))
                    has_digit = true;
                if (ispunct(ch))
                    has_special = true;
            }

            return has_upper && has_lower && has_digit && has_special;
        }
    };
} // namespace Softadastra

#endif // PASSWORDVALIDATOR_HPP

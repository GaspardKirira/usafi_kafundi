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
        // Méthode pour hacher le mot de passe avec bcrypt (plutôt que SHA-256)
        static std::string hashPassword(const std::string &password)
        {
            // Générer un "salt" aléatoire
            char salt[BCRYPT_HASHSIZE];
            if (bcrypt_gensalt(12, salt) != 0) // 12 est la force du hachage
            {
                throw std::runtime_error("Erreur lors de la génération du salt.");
            }

            // Hacher le mot de passe avec bcrypt
            char hashed_password[BCRYPT_HASHSIZE];
            if (bcrypt_hashpw(password.c_str(), salt, hashed_password) != 0)
            {
                throw std::runtime_error("Erreur lors du hachage du mot de passe.");
            }

            return std::string(hashed_password);
        }

        // Méthode pour vérifier si le mot de passe est valide avec bcrypt
        static void validatePassword(const std::string &password, const std::string &stored_hash)
        {
            // Si la comparaison échoue, lever une exception
            if (bcrypt_checkpw(password.c_str(), stored_hash.c_str()) != 0)
            {
                throw std::invalid_argument("Mot de passe invalide.");
            }
        }

        // Méthode pour valider la complexité d'un mot de passe
        static bool validatePasswordComplexity(const std::string &password)
        {
            if (password.length() > 8)
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

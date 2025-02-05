#ifndef PASSWORD_HPP
#define PASSWORD_HPP

#include <string>
#include "PasswordValidator.hpp"

namespace Softadastra
{
    class Password
    {
    public:
        // Constructeur par défaut
        Password() = default;

        // Constructeur avec le mot de passe
        explicit Password(const std::string &password)
        {
            // Vérification de la complexité du mot de passe
            if (!Softadastra::PasswordValidator::validatePasswordComplexity(password))
            {
                throw std::invalid_argument("Le mot de passe ne respecte pas les exigences de complexité. "
                                            "Le mot de passe doit :\n"
                                            "- Avoir au moins 12 caractères\n"
                                            "- Contenir au moins une lettre majuscule\n"
                                            "- Contenir au moins une lettre minuscule\n"
                                            "- Contenir au moins un chiffre\n"
                                            "- Contenir au moins un caractère spécial (exemple : !, @, #, $, %, etc.)");
            }

            // Si la complexité est valide, hachage du mot de passe
            m_password_hash = Softadastra::PasswordValidator::hashPassword(password);
        }

        // Getter pour le hash du mot de passe
        const std::string &getPasswordHash() const { return m_password_hash; }
        void setPasswordHash(const std::string &password_hash)
        {
            m_password_hash = password_hash;
        }

        // Méthode pour valider un mot de passe donné
        void validatePassword(const std::string &password) const
        {
            try
            {
                Softadastra::PasswordValidator::validatePassword(password, m_password_hash);
            }
            catch (const std::invalid_argument &e)
            {
                throw std::invalid_argument("Password validation failed: " + std::string(e.what()));
            }
        }

    private:
        std::string m_password_hash{};
    };
} // namespace Softadastra

#endif // PASSWORD_HPP

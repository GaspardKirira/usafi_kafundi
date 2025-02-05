#ifndef EMAIL_HPP
#define EMAIL_HPP

#include <string>
#include <regex>
#include <stdexcept>
#include "EmailValidator.hpp"

namespace Softadastra
{
    class Email
    {
    public:
        explicit Email(const std::string &email) : m_email(email)
        {
            Softadastra::EmailValidator::validateEmail(email);
        }

        const std::string &getEmail() const { return m_email; }
        void setEmail(const std::string &email) { m_email = email; }

    private:
        std::string m_email{};
    };
} // namespace Softadastra

#endif // EMAIL_HPP

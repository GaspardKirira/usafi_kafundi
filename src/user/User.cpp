#include "User.hpp"

namespace Softadastra
{
    User::User()
        : m_email(),
          m_password(),
          m_created_at(std::time(nullptr)),
          m_update_at(std::time(nullptr)) {}

    User::User(const std::string &firstname,
               const std::string &lastname,
               const std::string &username,
               const std::shared_ptr<Email> &email,
               const std::shared_ptr<Password> &password)
        : m_firstname(firstname), m_lastname(lastname), m_username(username),
          m_email(email), m_password(password), m_created_at(std::time(nullptr)), m_update_at(std::time(nullptr)) {}

    User::User(const User &other)
        : m_id(other.m_id), m_firstname(other.m_firstname), m_lastname(other.m_lastname),
          m_username(other.m_username), m_email(other.m_email), m_password(other.m_password),
          m_is_active(other.m_is_active), m_otp(other.m_otp), m_created_at(other.m_created_at),
          m_update_at(other.m_update_at) {}

    User &User::operator=(const User &other)
    {
        if (this != &other)
        {
            m_id = other.m_id;
            m_firstname = other.m_firstname;
            m_lastname = other.m_lastname;
            m_username = other.m_username;
            m_email = other.m_email;
            m_password = other.m_password;
            m_is_active = other.m_is_active;
            m_otp = other.m_otp;
            m_created_at = other.m_created_at;
            m_update_at = other.m_update_at;
        }
        return *this;
    }

    User::User(User &&other) noexcept
        : m_id(other.m_id), m_firstname(std::move(other.m_firstname)), m_lastname(std::move(other.m_lastname)),
          m_username(std::move(other.m_username)), m_email(std::move(other.m_email)),
          m_password(std::move(other.m_password)), m_is_active(other.m_is_active), m_otp(other.m_otp),
          m_created_at(other.m_created_at), m_update_at(other.m_update_at)
    {
        other.m_id = 0;
        other.m_is_active = false;
        other.m_otp = 0;
        other.m_created_at = 0;
        other.m_update_at = 0;
    }

    User &User::operator=(User &&other) noexcept
    {
        if (this != &other)
        {
            m_id = other.m_id;
            m_firstname = std::move(other.m_firstname);
            m_lastname = std::move(other.m_lastname);
            m_username = std::move(other.m_username);
            m_email = std::move(other.m_email);
            m_password = std::move(other.m_password);
            m_is_active = other.m_is_active;
            m_otp = other.m_otp;
            m_created_at = other.m_created_at;
            m_update_at = other.m_update_at;

            other.m_id = 0;
            other.m_is_active = false;
            other.m_otp = 0;
            other.m_created_at = 0;
            other.m_update_at = 0;
        }
        return *this;
    }

    void User::displayInfo() const
    {
        std::cout << "ID: " << m_id << "\n"
                  << "Name: " << m_firstname << " " << m_lastname << "\n"
                  << "Username: " << m_username << "\n"
                  << "Email: " << m_email->getEmail() << "\n"
                  << "Password: " << m_password->getPasswordHash() << "\n"
                  << "Active: " << (m_is_active ? "Yes" : "No") << "\n"
                  << "OTP: " << m_otp << std::endl;
    }

    json User::to_json() const
    {
        return json{
            {"firstname", m_firstname},
            {"lastname", m_lastname},
            {"username", m_username},
            {"email", m_email->getEmail()},
            {"password_hash", m_password->getPasswordHash()},
            {"create_at", std::ctime(&m_created_at)}};
    }

    void User::displayCreatedAt() const
    {
        std::cout << "Account created at: " << std::ctime(&m_created_at);
    }

    void User::warning(const std::string &message) const
    {
        std::cout << "Warning: " << message << std::endl;
    }
}

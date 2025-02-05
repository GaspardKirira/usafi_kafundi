#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <memory>
#include <iostream>
#include <chrono>
#include <ctime>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace Softadastra
{
    class User
    {
    public:
        User();

        User(const std::string &firstname,
             const std::string &lastname,
             const std::string &username,
             const std::string &email,
             const std::string &password);

        ~User() = default;
        User(const User &other);
        User &operator=(const User &other);
        User(User &&other) noexcept;
        User &operator=(User &&other) noexcept;

        int getId() const { return m_id; }
        const std::string &getFirstName() const { return m_firstname; }
        const std::string &getLastName() const { return m_lastname; }
        const std::string &getUserName() const { return m_username; }
        const std::string &getEmail() const { return m_email; }
        const std::string &getPassword() const { return m_password; }
        std::time_t getCreatedAt() const { return m_created_at; }

        void warning(const std::string &message) const;
        void displayInfo() const;

        void setId(int id) { m_id = id; }
        void setFirstName(const std::string &firstname) { m_firstname = firstname; }
        void setLastName(const std::string &lastname) { m_lastname = lastname; }
        void setUserName(const std::string &username) { m_username = username; }
        void setEmail(const std::string &email) { m_email = email; }
        void setPassword(const std::string &password) { m_password = password; }
        void setIsActive(bool value) { m_is_active = value; }
        void setOpt(int otp) { m_otp = otp; }

        void displayCreatedAt() const;
        json to_json() const;

    private:
        int m_id{};
        std::string m_firstname{};
        std::string m_lastname{};
        std::string m_username{};
        std::string m_email{};
        std::string m_password{};
        std::string reset_password_token{};
        std::string registration_token{};
        bool m_is_active{};
        int m_otp{};
        std::time_t m_created_at;
        std::time_t m_update_at;
    };
}

#endif // USER_HPP

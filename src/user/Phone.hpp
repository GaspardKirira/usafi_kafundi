#ifndef PHONE_HPP
#define PHONE_HPP

#include <string>
#include <stdexcept>
#include "PhoneValidator.hpp"

namespace Softadastra
{
    class Phone
    {
    public:
        explicit Phone(const std::string &phone) : m_phone(phone)
        {
            PhoneValidator::validatePhoneNumber(phone);
        }

        const std::string &getPhone() const { return m_phone; }

    private:
        std::string m_phone{};
    };

} // namespace Softadastra

#endif // PHONE_HPP

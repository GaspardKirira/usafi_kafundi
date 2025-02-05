#ifndef PHONEVALIDATOR_HPP
#define PHONEVALIDATOR_HPP

#include <stdexcept>
#include <string>

namespace Softadastra
{
    class PhoneValidator
    {
    public:
        static void validatePhoneNumber(const std::string &phone)
        {
            // Le numéro de téléphone doit être entre 10 et 15 caractères (inclus)
            if (phone.size() < 10 || phone.size() > 15)
            {
                throw std::invalid_argument("Invalid phone number format: must be between 10 and 15 characters");
            }

            for (char c : phone)
            {
                if (!isdigit(c))
                {
                    throw std::invalid_argument("Invalid phone number format: must contain only digits");
                }
            }
        }
    };
} // namespace Softadastra

#endif
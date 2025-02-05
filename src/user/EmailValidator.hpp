#ifndef EMAILVALIDATOR_HPP
#define EMAILVALIDATOR_HPP

#include <string>
#include <regex>

namespace Softadastra
{
    class EmailValidator
    {
    public:
        static void validateEmail(const std::string &email)
        {
            std::regex email_regex(R"((\w+)(\.[\w]+)*@(\w+)(\.[a-zA-Z]{2,3})+)");

            if (!std::regex_match(email, email_regex))
            {
                throw std::invalid_argument("Invalid email format");
            }
        }
    };
} // namespace Softadastra

#endif
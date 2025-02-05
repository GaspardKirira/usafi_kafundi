#ifndef COMPANY_HPP
#define COMPANY_HPP

#include <string>
#include <stdexcept>
#include "CompanyValidator.hpp"

namespace Softadastra
{
    class Company
    {
    public:
        explicit Company(const std::string &company_name = "No Company")
            : m_company_name(company_name)
        {
            Softadastra::CompanyValidator::validateName(company_name);
        }

        const std::string &getCompanyName() const { return m_company_name; }

    private:
        std::string m_company_name;
    };
} // namespace Softadastra

#endif // COMPANY_HPP
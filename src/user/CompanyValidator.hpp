#ifndef COMPANYVALIDATOR_HPP
#define COMPANYVALIDATOR_HPP

#include <stdexcept>
#include <string>

namespace Softadastra
{
    class CompanyValidator
    {
    public:
        static void validateName(const std::string &company_name)
        {
            if (company_name.empty())
            {
                throw std::invalid_argument("Company Company cannot be empty");
            }
            if (company_name.size() > 50)
            {
                throw std::invalid_argument("Le nom de l'entreprise est trop long. La longueur maximale est de 50 caractères.");
            }
        }
    };
} // namespace Softadastra

#endif
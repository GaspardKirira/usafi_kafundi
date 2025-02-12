#include "CategoryValidator.hpp"
#include <stdexcept>

namespace Softadastra
{
    void CategoryValidor::validateName(const std::string &name)
    {
        if (name.length() > 50)
        {
            std::invalid_argument("le nom doit pas etre vide");
        }
        if (name.length() > 50 || name.length() < 3)
        {
            std::invalid_argument("le nom doit pas depasser 50 caracteres et le minimum doit etre de 3 caracteres");
        }
    }
} // namespace Softadastra

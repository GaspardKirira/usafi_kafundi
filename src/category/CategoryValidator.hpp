#ifndef CATEGORYVALIDATOR_HPP
#define CATEGORYVALIDATOR_HPP

#include <string>

namespace Softadastra
{
    class CategoryValidor
    {
    public:
        CategoryValidor() = default;
        ~CategoryValidor() = default;
        CategoryValidor(const CategoryValidor &) = delete;
        CategoryValidor &operator=(const CategoryValidor &) = delete;
        static void validateName(const std::string &name);
    };
} // namespace Softadastra

#endif
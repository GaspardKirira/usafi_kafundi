#include "Category.hpp"
#include "CategoryValidator.hpp"
#include <stdexcept>

namespace Softadastra
{
    Category::Category()
    {
    }

    Category::Category(const std::string &name) : m_name(name)
    {
        Softadastra::CategoryValidor::validateName(name);
    }

    Category::~Category()
    {
    }

    Category::Category(const Category &rhs)
        : m_name(rhs.m_name) {}

    Category &Category::operator=(const Category &rhs)
    {
        if (this != &rhs)
        {
            m_name = rhs.m_name;
        }
        return *this;
    }

    Category::Category(Category &&rhs) noexcept
        : m_name(std::move(rhs.m_name)) {}

    Category &Category::operator=(Category &&rhs) noexcept
    {
        if (this != &rhs)
        {
            m_name = std::move(rhs.m_name);
        }
        return *this;
    }
} // namespace Softadastra

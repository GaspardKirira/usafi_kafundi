#ifndef CATEGORY_HPP
#define CATEGORY_HPP

#include <string>

namespace Softadastra
{
    class Category
    {
    public:
        Category();
        Category(const std::string &name);
        ~Category();
        Category(const Category &rhs);
        Category &operator=(const Category &rhs);

        Category(Category &&rhs) noexcept;
        Category &operator=(Category &&rhs) noexcept;

        const std::string &getName() const { return m_name; }
        void set(const std::string &name) { m_name = name; }

    private:
        std::string m_name{};
    };
} // namespace Softadastra

#endif
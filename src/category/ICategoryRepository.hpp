#ifndef ICATEGORYREPOSITORY_HPP
#define ICATEGORYREPOSITORY_HPP

#include "Category.hpp"

namespace Softadastra
{
    class ICategoryRepository
    {
    public:
        ICategoryRepository() = default;
        virtual ~ICategoryRepository() = default;
        ICategoryRepository(const ICategoryRepository &) = delete;
        void operator=(const ICategoryRepository &) = delete;

        virtual void save(const Category &) = 0;
    };
} // namespace Softadastra

#endif // ICATEGORYREPOSITORY_HPP
#ifndef CATEGORYREPOSITORY_HPP
#define CATEGORYREPOSITORY_HPP

#include "ICategoryRepository.hpp"
#include "../config/Config.hpp"

namespace Softadastra
{
    class CategoryRepository : public ICategoryRepository
    {
    public:
        CategoryRepository() = default;
        ~CategoryRepository() = default;
        CategoryRepository(const CategoryRepository &) = delete;
        void operator=(const CategoryRepository &) = delete;

        std::shared_ptr<sql::Connection> getDbConnection() const;
        void save(const Category &category) override;
    };
} // namespace Softadastra

#endif // CATEGORYREPOSITORY_HPP
#ifndef USERREPOSITORY_HPP
#define USERREPOSITORY_HPP

#include <spdlog/spdlog.h>
#include "IUserRepository.hpp"
#include "../config/Config.hpp"

namespace Softadastra
{
    class UserRepository : public IUserRepository
    {
    public:
        UserRepository(Config &config);
        void saveUser(const User &user) override;
        std::vector<User> findAll();
        std::shared_ptr<User> find(int userId);
        void update(int userId, const User &user);
        std::unique_ptr<sql::Connection> getDbConnection();
        void deleteUser(int userId);
        ~UserRepository();

    private:
        Config &m_config;
    };
} // namespace Softadastra

#endif // USERREPOSITORY_HPP
#ifndef IUSERREPOSITORY_HPP
#define IUSERREPOSITORY_HPP

#include <vector>
#include <memory>
#include "User.hpp"

namespace Softadastra
{
    class IUserRepository
    {
    public:
        IUserRepository() = default;
        virtual ~IUserRepository() = default;
        IUserRepository(const IUserRepository &) = delete;
        void operator=(const IUserRepository &) = delete;

        virtual void saveUser(const User &user) = 0;
    };

} // namespace Softadastra

#endif // IUSERREPOSITORY_HPP
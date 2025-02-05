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
        virtual void saveUser(const User &user) = 0;
        virtual ~IUserRepository() = default;
    };

} // namespace Softadastra

#endif // IUSERREPOSITORY_HPP
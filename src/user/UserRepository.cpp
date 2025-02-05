#include "UserRepository.hpp"
#include <memory>
#include <vector>
#include <stdexcept>

namespace Softadastra
{
    UserRepository::UserRepository(Config &config) : m_config(config) {}

    std::unique_ptr<sql::Connection> UserRepository::getDbConnection()
    {
        try
        {
            Config &config = Config::getInstance();
            config.loadConfig();
            return config.getDbConnection();
        }
        catch (const std::exception &e)
        {
            std::cerr << "Erreur lors de la connexion à la base de données : " << e.what() << std::endl;
            throw std::runtime_error("Erreur de connexion à la base de données.");
        }
    }

    void UserRepository::saveUser(const User &user)
    {
        std::unique_ptr<sql::Connection> con = getDbConnection();
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(
            "INSERT INTO users(firstname, lastname, username, email, password_hash, opt) "
            "VALUES(?,?,?,?,?,?)"));

        pstmt->setString(1, user.getFirstName());
        pstmt->setString(2, user.getLastName());
        pstmt->setString(3, user.getUserName());
        pstmt->setString(4, user.getEmail());
        pstmt->setString(5, user.getPassword());
        pstmt->setString(6, "012323");
        pstmt->executeUpdate();
    }

    std::vector<User> UserRepository::findAll()
    {
        std::vector<User> users;
        std::unique_ptr<sql::Connection> con = getDbConnection();
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT * FROM users"));
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        while (res->next())
        {
            User user(res->getString("firstname"), res->getString("lastname"), res->getString("username"), res->getString("email"), res->getString("password_hash"));
            users.push_back(user);
        }

        return users;
    }

    std::shared_ptr<User> UserRepository::find(int userId)
    {
        try
        {
            std::unique_ptr<sql::Connection> con = getDbConnection();
            std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT * FROM users WHERE id = ?"));
            pstmt->setInt(1, userId);

            std::cerr << "Executing query: SELECT * FROM users WHERE id = " << userId << std::endl;

            std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

            if (res->next())
            {
                auto user = std::make_shared<User>();
                user->setId(res->getInt("id"));
                user->setFirstName(res->getString("firstname"));
                user->setLastName(res->getString("lastname"));
                user->setUserName(res->getString("username"));
                user->setEmail(res->getString("email"));
                user->setPassword(res->getString("password_hash"));
                return user;
            }
            else
            {
                std::cerr << "No user found with ID: " << userId << std::endl;
                throw std::runtime_error("User not found");
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error in find method: " << e.what() << std::endl;
            throw;
        }
    }

    void UserRepository::update(int userId, const User &user)
    {
        try
        {
            std::unique_ptr<sql::Connection> con = getDbConnection();
            std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(
                "UPDATE users SET firstname = ?, lastname = ?, username = ?, email = ?, password_hash = ? WHERE id = ?"));

            pstmt->setString(1, user.getFirstName());
            pstmt->setString(2, user.getLastName());
            pstmt->setString(3, user.getUserName());
            pstmt->setString(4, user.getEmail());
            pstmt->setString(5, user.getPassword());
            pstmt->setInt(6, userId);

            pstmt->executeUpdate();
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error updating user: " << e.what() << std::endl;
            throw;
        }
    }

    void UserRepository::deleteUser(int userId)
    {
        try
        {
            // Vérifier d'abord si l'utilisateur existe
            std::unique_ptr<sql::Connection> con = getDbConnection();
            std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT COUNT(*) FROM users WHERE id = ?"));
            pstmt->setInt(1, userId);
            std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

            if (res->next() && res->getInt(1) > 0)
            {
                // Si l'utilisateur existe, on procède à la suppression
                pstmt.reset(con->prepareStatement("DELETE FROM users WHERE id = ?"));
                pstmt->setInt(1, userId);
                pstmt->executeUpdate();
                std::cout << "User with ID " << userId << " has been deleted." << std::endl;
            }
            else
            {
                std::cerr << "User with ID " << userId << " does not exist." << std::endl;
                throw std::runtime_error("User not found");
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error deleting user: " << e.what() << std::endl;
            throw;
        }
    }

    UserRepository::~UserRepository()
    {
        spdlog::warn("UserRepository Destroyed bien!");
    }

} // namespace Softadastra

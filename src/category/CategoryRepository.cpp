#include "CategoryRepository.hpp"

namespace Softadastra
{
    std::shared_ptr<sql::Connection> CategoryRepository::getDbConnection() const
    {
        try
        {
            Config &config = Config::getInstance();
            config.loadConfig();
            return config.getDbConnection();
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error("error lors de la connexion a la base de donnees");
        }
    }

    void CategoryRepository::save(const Category &category)
    {
        try
        {
            std::shared_ptr<sql::Connection> con = getDbConnection();
            std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO category(name) VALUES(?)"));
            pstmt->setString(1, category.getName());
            pstmt->executeUpdate();
        }
        catch (const sql::SQLException &e)
        {
            throw std::runtime_error("error lors de l'insertion de la categorie");
        }
    }
}
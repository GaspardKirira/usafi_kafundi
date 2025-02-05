#ifndef USERROUTES_HPP
#define USERROUTES_HPP

#include <unordered_map>
#include <string>
#include <memory>
#include <stdexcept>
#include "Controller.hpp"
#include "../user/UserRepository.hpp"
#include "../user/User.hpp"

namespace Softadastra
{

    // Fonction pour convertir unordered_map en une chaîne lisible
    std::string unordered_map_to_string(const std::unordered_map<std::string, std::string> &map)
    {
        std::stringstream ss;
        ss << "{";
        for (auto it = map.begin(); it != map.end(); ++it)
        {
            if (it != map.begin())
            {
                ss << ", "; // Ajouter une virgule pour séparer les éléments
            }
            ss << it->first << ": " << it->second;
        }
        ss << "}";
        return ss.str();
    }
    class UserController : public Controller
    {
    public:
        UserController(const UserRepository &user_repository)
            : m_user_repository(user_repository) {}

        void configure(Router &router) override
        {
            router.add_route(http::verb::get, "/find/{id}",
                             std::static_pointer_cast<IRequestHandler>(
                                 std::make_shared<DynamicRequestHandler>(
                                     [this](const std::unordered_map<std::string, std::string> &params,
                                            http::response<http::string_body> &res)
                                     {
                                         try
                                         {
                                             std::string user_id = params.at("id");
                                             std::cerr << "ID param: " << user_id << std::endl; // Log l'ID reçu pour débogage
                                             int id = std::stoi(user_id);                       // Conversion en int

                                             std::shared_ptr<User> user = m_user_repository.find(id);

                                             // Si l'utilisateur est trouvé, renvoyer les informations
                                             res.result(http::status::ok);
                                             res.set(http::field::content_type, "application/json");
                                             res.body() = json{
                                                 {"id", user->getId()},
                                                 {"full_name", user->getFirstName() + " " + user->getLastName()},
                                                 {"email", user->getEmail()},
                                                 {"username", user->getUserName()}}
                                                              .dump();
                                         }
                                         catch (const std::exception &e)
                                         {
                                             std::cerr << "Error: " << e.what() << std::endl; // Log de l'erreur pour débogage
                                             res.result(http::status::not_found);
                                             res.set(http::field::content_type, "application/json");
                                             res.body() = json{{"message", "User not found"}}.dump();
                                         }
                                     })));

            // Route GET pour récupérer tous les utilisateurs
            router.add_route(http::verb::get, "/users",
                             std::static_pointer_cast<IRequestHandler>(
                                 std::make_shared<DynamicRequestHandler>(
                                     [this](const std::unordered_map<std::string, std::string> &,
                                            http::response<http::string_body> &res)
                                     {
                                         try
                                         {
                                             std::vector<User> users = m_user_repository.findAll();

                                             res.result(http::status::ok);
                                             res.set(http::field::content_type, "application/json");
                                             nlohmann::json json_users = nlohmann::json::array();
                                             for (const auto &user : users)
                                             {
                                                 json_users.push_back({{"id", user.getId()}, {"full_name", user.getFirstName()}});
                                             }
                                             res.body() = json_users.dump();
                                         }
                                         catch (const std::exception &e)
                                         {
                                             res.result(http::status::internal_server_error);
                                             res.set(http::field::content_type, "application/json");
                                             res.body() = json{{"message", "Error fetching users"}}.dump();
                                         }
                                     })));

            router.add_route(http::verb::post, "/create",
                             std::static_pointer_cast<IRequestHandler>(
                                 std::make_shared<DynamicRequestHandler>(
                                     [this](const std::unordered_map<std::string, std::string> &params,
                                            http::response<http::string_body> &res)
                                     {
                                         json request_json;
                                         try
                                         {
                                             // Extraire et parser le JSON depuis les paramètres
                                             request_json = json::parse(params.at("body"));
                                         }
                                         catch (const std::exception &e)
                                         {
                                             res.result(http::status::bad_request);
                                             res.set(http::field::content_type, "application/json");
                                             res.body() = json{{"message", "Invalid JSON body."}}.dump();
                                             return;
                                         }

                                         // Vérification des champs dans le JSON
                                         if (request_json.find("firstname") == request_json.end())
                                         {
                                             res.result(http::status::bad_request);
                                             res.set(http::field::content_type, "application/json");
                                             res.body() = json{{"message", "Le champ 'firstname' est manquant."}}.dump();
                                             return;
                                         }
                                         if (request_json.find("lastname") == request_json.end())
                                         {
                                             res.result(http::status::bad_request);
                                             res.set(http::field::content_type, "application/json");
                                             res.body() = json{{"message", "Le champ 'lastname' est manquant."}}.dump();
                                             return;
                                         }
                                         if (request_json.find("username") == request_json.end())
                                         {
                                             res.result(http::status::bad_request);
                                             res.set(http::field::content_type, "application/json");
                                             res.body() = json{{"message", "Le champ 'username' est manquant."}}.dump();
                                             return;
                                         }
                                         if (request_json.find("email") == request_json.end())
                                         {
                                             res.result(http::status::bad_request);
                                             res.set(http::field::content_type, "application/json");
                                             res.body() = json{{"message", "Le champ 'email' est manquant."}}.dump();
                                             return;
                                         }
                                         if (request_json.find("password") == request_json.end())
                                         {
                                             res.result(http::status::bad_request);
                                             res.set(http::field::content_type, "application/json");
                                             res.body() = json{{"message", "Le champ 'password' est manquant."}}.dump();
                                             return;
                                         }

                                         // Créer un nouvel utilisateur
                                         User new_user(request_json["firstname"], request_json["lastname"],
                                                       request_json["username"], request_json["email"], request_json["password"]);

                                         // Sauvegarder l'utilisateur dans la base de données
                                         m_user_repository.saveUser(new_user);

                                         // Répondre avec succès
                                         res.result(http::status::created);
                                         res.set(http::field::content_type, "application/json");
                                         res.body() = json{{"message", "User created successfully"}}.dump();
                                     })));

            router.add_route(http::verb::put, "/user/{id}",
                             std::static_pointer_cast<IRequestHandler>(
                                 std::make_shared<DynamicRequestHandler>(
                                     [this](const std::unordered_map<std::string, std::string> &params,
                                            http::response<http::string_body> &res)
                                     {
                                         try
                                         {
                                             std::string user_id = params.at("id");
                                             int id = std::stoi(user_id);

                                             // Ici, vous récupérez les données de la requête et les utilisez pour mettre à jour l'utilisateur
                                             // Exemple simplifié d'une mise à jour de "full_name"
                                             std::string updated_full_name = "Updated User Name";

                                             std::shared_ptr<User> updated_user = m_user_repository.find(id);
                                             updated_user->setFirstName(updated_full_name);

                                             // Mettre à jour l'utilisateur dans la base de données
                                             m_user_repository.update(id, *updated_user);

                                             res.result(http::status::ok);
                                             res.set(http::field::content_type, "application/json");
                                             res.body() = json{{"message", "User updated successfully"}}.dump();
                                         }
                                         catch (const std::exception &e)
                                         {
                                             res.result(http::status::not_found);
                                             res.set(http::field::content_type, "application/json");
                                             res.body() = json{{"message", "User not found"}}.dump();
                                         }
                                     })));

            // Route DELETE pour supprimer un utilisateur
            router.add_route(http::verb::get, "/delete/{id}",
                             std::static_pointer_cast<IRequestHandler>(
                                 std::make_shared<DynamicRequestHandler>(
                                     [this](const std::unordered_map<std::string, std::string> &params,
                                            http::response<http::string_body> &res)
                                     {
                                         try
                                         {
                                             std::string user_id = params.at("id");
                                             int id = std::stoi(user_id);

                                             // Supprimer l'utilisateur de la base de données
                                             m_user_repository.deleteUser(id);

                                             res.result(http::status::ok);
                                             res.set(http::field::content_type, "application/json");
                                             res.body() = json{{"message", "User deleted successfully"}}.dump();
                                         }
                                         catch (const std::exception &e)
                                         {
                                             res.result(http::status::not_found);
                                             res.set(http::field::content_type, "application/json");
                                             res.body() = json{{"message", "User not found"}}.dump();
                                         }
                                     })));
        }

    private:
        UserRepository m_user_repository; // Assurez-vous d'instancier votre repository ici
    };
}

#endif // USERROUTES_HPP

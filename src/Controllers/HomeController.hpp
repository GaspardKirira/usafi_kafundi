#ifndef HOMEROUTES_HPP
#define HOMEROUTES_HPP

#include <unordered_map>
#include <string>
#include <memory>
#include <stdexcept>
#include <nlohmann/json.hpp>
#include <ctime>
#include "Controller.hpp"

#include "../user/User.hpp"
#include "../user/UserService.hpp"
#include "../user/UserRepository.hpp"
#include "../config/Config.hpp"

using json = nlohmann::json;

namespace Softadastra
{
    class HomeController : public Controller
    {
    public:
        void configure(Router &routes) override
        {
            routes.add_route(
                http::verb::get, "/",
                std::static_pointer_cast<IRequestHandler>(
                    std::make_shared<SimpleRequestHandler>(
                        [](const http::request<http::string_body> &req,
                           http::response<http::string_body> &res)
                        {
                            // Définir la version de HTTP de la réponse
                            res.version(req.version());

                            // Définir le statut de la réponse à 200 OK
                            res.result(http::status::ok);

                            // Définir l'en-tête Content-Type en application/json
                            res.set(http::field::content_type, "application/json");

                            // Ajouter l'en-tête Server
                            res.set(http::field::server, "Softadastra/master");

                            // Générer la date actuelle au format HTTP (RFC 1123)
                            auto now = std::chrono::system_clock::now();
                            std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
                            std::tm tm = *std::gmtime(&now_time_t);

                            std::ostringstream oss;
                            oss << std::put_time(&tm, "%a, %d %b %Y %H:%M:%S GMT");
                            std::string date = oss.str();

                            // Ajouter l'en-tête Date avec la date dynamique
                            res.set(http::field::date, date);

                            // Remplir le corps de la réponse avec un message JSON
                            res.body() = json{{"message", "Welcome to the Softadastra HTTP Server"}}.dump();
                        })));

            // Gestion de la méthode OPTIONS avant la méthode POST
            routes.add_route(http::verb::options, "/create",
                             std::static_pointer_cast<IRequestHandler>(std::make_shared<SimpleRequestHandler>(
                                 [](const http::request<http::string_body> &, http::response<http::string_body> &res)
                                 {
                                     // Réponse vide avec les en-têtes CORS
                                     res.result(http::status::no_content);
                                     res.set(http::field::access_control_allow_origin, "*");              // Permet toutes les origines (ajuste si nécessaire)
                                     res.set(http::field::access_control_allow_methods, "POST, OPTIONS"); // Autorise les méthodes POST et OPTIONS
                                     res.set(http::field::access_control_allow_headers, "Content-Type");  // Autorise l'en-tête Content-Type
                                 })));
        }
    };
} // namespace Softadastra

#endif // HOMEROUTES_HPP

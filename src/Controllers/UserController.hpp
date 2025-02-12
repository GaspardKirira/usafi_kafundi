#ifndef USERCONTROLLER_HPP
#define USERCONTROLLER_HPP

#include "Controller.hpp"
#include "Validator.hpp"
#include "../user/User.hpp"
#include "../user/UserRepository.hpp"
#include "../kernel/Response.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace Softadastra
{
    class UserController : public Controller
    {
    public:
        using Controller::Controller;

        void configure(Router &router) override
        {
            router.add_route(http::verb::post, "/create_user",
                             std::static_pointer_cast<IRequestHandler>(
                                 std::make_shared<RequestHandler>(
                                     [this](
                                         const http::request<http::string_body> &req,
                                         http::response<http::string_body> &res)
                                     {
                                         json request_json;
                                         try
                                         {
                                             request_json = json::parse(req.body());
                                         }
                                         catch (const std::exception &e)
                                         {
                                             Response::error_response(res, http::status::bad_request, "Invalid JSON data");
                                             return;
                                         }

                                         std::string firstname, lastname, username, email, password;
                                         bool is_valid = true;

                                         is_valid &= Validator::validate_field(request_json, "firstname", firstname, res, "Missing or invalid 'firstname'");
                                         is_valid &= Validator::validate_field(request_json, "lastname", lastname, res, "Missing or invalid 'lastname'");
                                         is_valid &= Validator::validate_field(request_json, "username", username, res, "Missing or invalid 'username'");
                                         is_valid &= Validator::validate_field(request_json, "email", email, res, "Missing or invalid 'email'");
                                         is_valid &= Validator::validate_field(request_json, "password", password, res, "Missing or invalid 'password'");

                                         if (!is_valid)
                                         {
                                             return;
                                         }
                                         try
                                         {
                                             auto c_email = std::make_shared<Email>(email);
                                             auto c_password = std::make_shared<Password>(password);

                                             std::unique_ptr<User> user = std::make_unique<User>(firstname, lastname, username, c_email, c_password);

                                             Config &config = Config::getInstance();
                                             config.loadConfig();

                                             std::unique_ptr<UserRepository> repo = std::make_unique<UserRepository>(config);
                                             repo->saveUser(*user);

                                             json json_data;
                                             json_data["firstname"] = user->getFirstName();
                                             json_data["lastname"] = user->getLastName();
                                             json_data["username"] = user->getUserName();
                                             json_data["email"] = user->getEmail();
                                             json_data["password"] = user->getPassword();

                                             Response::json_response(res, json_data);
                                         }
                                         catch (const std::exception &e)
                                         {
                                             Response::error_response(res, http::status::bad_request, e.what());
                                         }

                                         return;
                                     })));
        }
    };
}

#endif // USERCONTROLLER_HPP

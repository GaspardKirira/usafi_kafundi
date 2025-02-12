#ifndef CATEGORYCONTROLLER_HPP
#define CATEGORYCONTROLLER_HPP

#include "Controller.hpp"
#include "../category/Category.hpp"
#include "../category/CategoryRepository.hpp"
#include <nlohmann/json.hpp>
#include "Validator.hpp"

using json = nlohmann::json;

namespace Softadastra
{

    class CategoryController : public Controller
    {
    public:
        using Controller::Controller;

        void configure(Router &router) override
        {
            router.add_route(http::verb::post, "/create_category",
                             std::static_pointer_cast<IRequestHandler>(
                                 std::make_shared<RequestHandler>(
                                     [](const http::request<http::string_body> &req, http::response<http::string_body> &res)
                                     {
                                         json request_data;
                                         try
                                         {
                                             request_data = json::parse(req.body());
                                         }
                                         catch (const std::exception &e)
                                         {
                                             Response::error_response(res, http::status::bad_request, "Invalid JSON data");
                                         }
                                         
                                         std::string name{};
                                         bool is_valid = true;
                                         is_valid &= Validator::validate_field(request_data, "name", name, res, "Missing or invalid name");

                                         if (!is_valid)
                                         {
                                             return;
                                         }

                                         try
                                         {
                                             std::unique_ptr<CategoryRepository> repo = std::make_unique<CategoryRepository>();
                                             std::unique_ptr<Category> category = std::make_unique<Category>(name);
                                             repo->save(*category);
                                             Response::success_response(res, "Category created successfull");
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
#endif // CATEGORYCONTROLLER_HPP
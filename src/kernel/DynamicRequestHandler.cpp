#include "DynamicRequestHandler.hpp"
#include <spdlog/spdlog.h>
#include <regex>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace Softadastra
{

    DynamicRequestHandler::DynamicRequestHandler(
        std::function<void(const std::unordered_map<std::string, std::string> &,
                           http::response<http::string_body> &)>
            handler)
        : params_(), handler_(std::move(handler))
    {
        spdlog::info("DynamicRequestHandler initialized.");
    }

    void DynamicRequestHandler::handle_request(const http::request<http::string_body> &req,
                                               http::response<http::string_body> &res)
    {
        spdlog::info("Handling request with body...");

        // Extraire le corps de la requête
        const std::string &body = req.body();

        json request_json;
        try
        {
            // Parser le corps JSON
            request_json = json::parse(body);
        }
        catch (const std::exception &e)
        {
            spdlog::error("Failed to parse JSON body: {}", e.what());
            res.result(http::status::bad_request);
            res.set(http::field::content_type, "application/json");
            res.body() = json{{"message", "Invalid JSON body."}}.dump();
            return;
        }

        // Appeler le handler avec les paramètres extraits
        handler_({{"body", body}}, res);
    }

    void DynamicRequestHandler::set_params(const std::unordered_map<std::string, std::string> &params)
    {
        spdlog::info("Setting parameters in DynamicRequestHandler...");

        for (const auto &param : params)
        {
            const std::string &key = param.first;
            const std::string &value = param.second;

            // Validation générique (par exemple pour ID ou slug)
            if (key == "id" && !std::regex_match(value, std::regex("^[0-9]+$")))
            {
                spdlog::warn("Invalid 'id' parameter: {}", value);
                throw std::invalid_argument("Invalid parameter value for 'id'. Must be a positive integer.");
            }
            else if (key == "slug" && !std::regex_match(value, std::regex("^[a-zA-Z0-9_-]+$")))
            {
                spdlog::warn("Invalid 'slug' parameter: {}", value);
                throw std::invalid_argument("Invalid parameter value for 'slug'. Must be alphanumeric.");
            }
        }

        params_ = params; // Mise à jour des paramètres
        spdlog::info("Parameters set successfully.");
    }

}

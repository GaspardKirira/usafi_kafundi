#ifndef VALIDATOR_HPP
#define VALIDATOR_HPP

#include <nlohmann/json.hpp>
#include <string>
#include "../kernel/Response.hpp"
#include <type_traits>
#include <boost/beast/http.hpp>

using json = nlohmann::json;
namespace http = boost::beast::http;

namespace Softadastra
{
    class Validator
    {
    public:
        template <typename T>
        static bool validate_field(const json &request_json, const std::string &field, T &value, http::response<http::string_body> &res, const std::string &error_message)
        {
            if (!request_json.contains(field))
            {
                Response::error_response(res, http::status::bad_request, "Missing '" + field + "'");
                return false;
            }

            if constexpr (std::is_same<T, std::string>::value)
            {
                if (!request_json[field].is_string())
                {
                    Response::error_response(res, http::status::bad_request, error_message);
                    return false;
                }
                value = request_json[field].get<std::string>();
            }
            else if constexpr (std::is_same<T, int>::value)
            {
                if (!request_json[field].is_number_integer())
                {
                    Response::error_response(res, http::status::bad_request, error_message);
                    return false;
                }
                value = request_json[field].get<int>();
            }
            else if constexpr (std::is_same<T, bool>::value)
            {
                if (!request_json[field].is_boolean())
                {
                    Response::error_response(res, http::status::bad_request, error_message);
                    return false;
                }
                value = request_json[field].get<bool>();
            }
            else
            {
                Response::error_response(res, http::status::bad_request, "Unsupported field type for '" + field + "'");
                return false;
            }

            return true;
        }
    };
}

#endif // VALIDATOR_HPP

#include "RouteConfigurator.hpp"
#include "../Controllers/ProductController.hpp"
#include "../Controllers/UserController.hpp"
#include "../Controllers/HomeController.hpp"
#include "../user/UserRepository.hpp"

namespace Softadastra
{
    RouteConfigurator::RouteConfigurator(Router &router)
        : router_(router)
    {
    }

    void RouteConfigurator::configure_routes()
    {
        Config &config = Config::getInstance();
        config.loadConfig();

        HomeController homeController;
        homeController.configure(router_);

        ProductController productController;
        productController.configure(router_);

        UserRepository userRepository(config);
        UserController userController(userRepository);
        userController.configure(router_);
    }
}

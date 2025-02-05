
#ifndef LOCATIONVALIDATOR_HPP
#define LOCATIONVALIDATOR_HPP

#include <stdexcept>

namespace Softadastra
{
    class LocationValidator
    {
    public:
        static void validateLocation(int country_id, int currency_id, int language_id)
        {
            if (country_id < 0 || currency_id < 0 || language_id < 0)
            {
                throw std::invalid_argument("Country, currency, or language ID cannot be negative");
            }

            if (country_id > 999 || currency_id > 999 || language_id > 999)
            {
                throw std::invalid_argument("Country, currency, or language ID is too large");
            }
        }
    };
} // namespace Softadastra

#endif
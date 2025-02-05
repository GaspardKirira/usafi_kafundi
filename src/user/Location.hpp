#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <stdexcept>
#include "LocationValidator.hpp"

namespace Softadastra
{
    class Location
    {
    public:
        Location(int country_id = 0, int currency_id = 0, int language_id = 0)
            : m_country_id(country_id), m_currency_id(currency_id), m_language_id(language_id)
        {
            Softadastra::LocationValidator::validateLocation(country_id, currency_id, language_id);
        }

        int getCountryId() const { return m_country_id; }
        int getCurrencyId() const { return m_currency_id; }
        int getLanguageId() const { return m_language_id; }

    private:
        int m_country_id;
        int m_currency_id;
        int m_language_id;
    };
} // namespace Softadastra

#endif // LOCATION_HPP

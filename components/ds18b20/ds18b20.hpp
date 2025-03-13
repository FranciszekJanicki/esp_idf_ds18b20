#ifndef DS18B20_HPP
#define DS18B20_HPP

#include "ds18b20_config.hpp"

namespace DS18B20 {

    struct DS18B20 {
    public:
        static inline OWDevice ow_device{};

        std::int16_t get_temperature_raw() noexcept;
        float get_temperature_scaled() noexcept;

        DevAddress address{};
    };

}; // namespace DS18B20

#endif // DS18B20_HPP

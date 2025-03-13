#include "ds18b20.hpp"
#include <utility>

namespace DS18B20 {

    std::int16_t DS18B20::get_temperature_raw() noexcept
    {
        this->ow_device.reset();
        this->ow_device.write16(static_cast<std::uint16_t>(CMD::SKIP_ROM));
        this->ow_device.write16(static_cast<std::uint16_t>(CMD::CONVERT_T));

        while (this->ow_device.read8() == 0) {
            ;
        }

        this->ow_device.reset();
        this->ow_device.write16(static_cast<std::uint16_t>(CMD::MATCH_ROM));
        this->ow_device.write64(static_cast<std::uint64_t>(this->address));
        this->ow_device.write16(static_cast<std::uint16_t>(CMD::READ_SCRATCHPAD));

        return static_cast<std::int16_t>(this->ow_device.read8()) |
               static_cast<std::int16_t>(this->ow_device.read8() << 8);
    }

    float DS18B20::get_temperature_scaled() noexcept
    {
        return static_cast<float>(this->get_temperature_raw()) / 16.0F;
    }

}; // namespace DS18B20
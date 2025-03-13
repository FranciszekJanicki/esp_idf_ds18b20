#include "ds18b20_task.hpp"
#include "ds18b20.hpp"
#include "ds18b20_config.hpp"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <array>

namespace DS18B20 {

    namespace {

        auto constexpr TASK_TAG = "DS18B20";
        auto constexpr TASK_STACK_SIZE = 4096UL;
        auto task_stack = std::array<StackType_t, 4096UL>{};
        auto static_task = StaticTask_t{};

        auto constexpr OW_GPIO_PIN = gpio_num_t::GPIO_NUM_0;
        auto ow_queue_storage = std::array<StackType_t, sizeof(rmt_rx_done_event_data_t)>{};
        auto ow_static_queue = StaticQueue_t{};

        void task(void* parameter) noexcept
        {
            auto ds18b20 = DS18B20{.address = DevAddress::ADDRESS1};

            while (true) {
                ESP_LOGI(TASK_TAG, "temperature: %f", ds18b20.get_temperature_scaled());
                vTaskDelay(pdMS_TO_TICKS(10));
            }
        }

    }; // namespace

    void start_task() noexcept
    {
        xTaskCreateStaticPinnedToCore(&task,
                                      TASK_TAG,
                                      task_stack.size(),
                                      nullptr,
                                      1,
                                      task_stack.data(),
                                      &static_task,
                                      1);
    }

}; // namespace DS18B20
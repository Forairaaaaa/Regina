/**
 * @file app_input_daemon.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-05-14
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <cstdint>
#include <mooncake.h>
#include "../../hal/types.h"

namespace MOONCAKE
{
    namespace APPS
    {
        /**
         * @brief AppInputDaemon
         *
         */
        class AppInputDaemon : public APP_BASE
        {
        private:
            struct Data_t
            {
                uint32_t update_input_time_count = 0;
                uint32_t update_input_interval = 50;

                uint8_t last_dial_a_value = 0;
                uint8_t last_dial_b_value = 0;
                uint8_t last_dial_a_count = 0;
                uint8_t last_dial_b_count = 0;

                BLE_KB::InputFrame_t new_input_frame;
            };
            Data_t _data;
            void _update_input();
            void _update_button();
            void _update_dial();

        public:
            void onCreate() override;
            void onResume() override;
            void onRunning() override;
            void onDestroy() override;
        };

        class AppInputDaemon_Packer : public APP_PACKER_BASE
        {
            const char* getAppName() override;
            void* newApp() override { return new AppInputDaemon; }
            void deleteApp(void* app) override { delete (AppInputDaemon*)app; }
        };
    } // namespace APPS
} // namespace MOONCAKE

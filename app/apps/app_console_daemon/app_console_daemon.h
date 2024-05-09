/**
 * @file app_console_daemon.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-05-09
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <cstdint>
#include <mooncake.h>

namespace MOONCAKE
{
    namespace APPS
    {
        /**
         * @brief AppConsoleDaemon
         *
         */
        class AppConsoleDaemon : public APP_BASE
        {
        private:
            struct Data_t
            {
                uint32_t update_btn_time_count = 0;
                uint32_t update_btn_interval = 20;
            };
            Data_t _data;
            void _update_buttons();

        public:
            void onResume() override;
            void onRunning() override;
            void onDestroy() override;
        };

        class AppConsoleDaemon_Packer : public APP_PACKER_BASE
        {
            const char* getAppName() override;
            void* newApp() override { return new AppConsoleDaemon; }
            void deleteApp(void* app) override { delete (AppConsoleDaemon*)app; }
        };
    } // namespace APPS
} // namespace MOONCAKE
/**
 * @file app_sleep_daemon.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-05-08
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
        class AppSleepDaemon : public APP_BASE
        {
        private:
            struct Data_t
            {
                uint32_t check_pwr_btn_time_count = 0;
                uint32_t check_pwr_btn_interval = 100;
                uint32_t audio_fft_timeout_count = 0;
            };
            Data_t _data;

        public:
            void onResume() override;
            void onRunning() override;
            void onDestroy() override;
        };

        class AppSleepDaemon_Packer : public APP_PACKER_BASE
        {
            const char* getAppName() override;
            void* newApp() override { return new AppSleepDaemon; }
            void deleteApp(void* app) override { delete (AppSleepDaemon*)app; }
        };
    } // namespace APPS
} // namespace MOONCAKE

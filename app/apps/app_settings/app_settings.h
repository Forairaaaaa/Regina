/**
 * @file app_settings.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-05-11
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
         * @brief AppSettings
         *
         */
        class AppSettings : public APP_BASE
        {
        private:
            struct Data_t
            {
                std::uint32_t time_count = 0;
            };
            Data_t _data;

        public:
            void onResume() override;
            void onRunning() override;
            void onDestroy() override;
        };

        class AppSettings_Packer : public APP_PACKER_BASE
        {
            const char* getAppName() override;
            void* getAppIcon() override;
            void* newApp() override { return new AppSettings; }
            void deleteApp(void* app) override { delete (AppSettings*)app; }
        };
    } // namespace APPS
} // namespace MOONCAKE
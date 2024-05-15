/**
 * @file app_notification.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-05-15
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
         * @brief AppNotification
         *
         */
        class AppNotification : public APP_BASE
        {
        private:
            struct Data_t
            {
            };
            Data_t _data;

        public:
            void onResume() override;
            void onRunning() override;
            void onDestroy() override;
        };

        class AppNotification_Packer : public APP_PACKER_BASE
        {
            const char* getAppName() override;
            void* newApp() override { return new AppNotification; }
            void deleteApp(void* app) override { delete (AppNotification*)app; }
        };
    } // namespace APPS
} // namespace MOONCAKE
/**
 * @file app_desktop.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-05-01
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <cstdint>
#include <mooncake.h>
#include "view/desktop.h"

namespace MOONCAKE
{
    namespace APPS
    {
        /**
         * @brief Template
         *
         */
        class AppDesktop : public APP_BASE
        {
        private:
            struct Data_t
            {
                WidgetDesktop widget_desktop;
            };
            Data_t _data;

        public:
            void onCreate() override;
            void onResume() override;
            void onRunning() override;
            void onDestroy() override;
        };

        class AppDesktop_Packer : public APP_PACKER_BASE
        {
            const char* getAppName() override;
            void* getAppIcon() override;
            void* newApp() override { return new AppDesktop; }
            void deleteApp(void* app) override { delete (AppDesktop*)app; }
        };

    } // namespace APPS
} // namespace MOONCAKE
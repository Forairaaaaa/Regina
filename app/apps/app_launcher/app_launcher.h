/**
 * @file app_launcher.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-04-25
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
        class AppLauncher : public APP_BASE
        {
        private:
        public:
            void onCreate() override;
            void onResume() override;
            void onRunning() override;
            void onDestroy() override;
        };

        class AppLauncher_Packer : public APP_PACKER_BASE
        {
            const char* getAppName() override;
            void* getAppIcon() override;
            void* newApp() override { return new AppLauncher; }
            void deleteApp(void* app) override { delete (AppLauncher*)app; }
        };
    } // namespace APPS
} // namespace MOONCAKE
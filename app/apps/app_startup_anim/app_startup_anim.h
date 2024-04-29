/**
 * @file app_startup_anim.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-04-29
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
         * @brief Template
         *
         */
        class AppStartupAnim : public APP_BASE
        {
        private:
        public:
            void onResume() override;
            void onDestroy() override;
        };

        class AppStartupAnim_Packer : public APP_PACKER_BASE
        {
            const char* getAppName() override;
            void* newApp() override { return new AppStartupAnim; }
            void deleteApp(void* app) override { delete (AppStartupAnim*)app; }
        };
    } // namespace APPS
} // namespace MOONCAKE
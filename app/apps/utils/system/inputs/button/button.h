/**
 * @file button.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-03-05
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "../../../../../hal/hal.h"
#include "m5unified/Button_Class.hpp"

namespace SYSTEM
{
    namespace INPUTS
    {
        // Special shit
        class ButtonPwr
        {
        public:
            bool wasClicked(void);
        };

        /**
         * @brief Button class with richer apis
         *
         */
        class Button : public m5::Button_Class
        {
        private:
            GAMEPAD::GamePadButton_t _button;

        public:
            Button(GAMEPAD::GamePadButton_t button) : _button(button) {}
            void update();

        public:
            /**
             * @brief Button instances
             *
             * @return Button*
             */
            static Button* A();
            static Button* B();
            static Button* C();
            static Button* D();
            static ButtonPwr* Power();

            /**
             * @brief Helper method to update all button instances
             *
             */
            static void Update();
        };

    } // namespace INPUTS
} // namespace SYSTEM

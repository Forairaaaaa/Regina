/**
 * @file hal_rtc.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2023-11-07
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "../hal_regina.h"
#include "../hal_config.h"
#include <mooncake.h>
#include <utility/RTC8563_Class.hpp>

static m5::RTC8563_Class* _rtc = nullptr;

void HAL_Regina::_rtc_init()
{
    spdlog::info("rtc init");

    _rtc = new m5::RTC8563_Class(0x51, 400000, &m5::In_I2C);
    if (!_rtc->begin())
    {
        spdlog::error("init failed!");
        delete _rtc;
    }

    _adjust_sys_time();

    // /* -------------------------------------------------------------------------- */
    // /*                                    Test                                    */
    // /* -------------------------------------------------------------------------- */
    // tm set_time;
    // set_time.tm_year = 2077;
    // set_time.tm_mon = 2;
    // set_time.tm_mday = 7;
    // set_time.tm_wday = 5;
    // set_time.tm_hour = 6;
    // set_time.tm_min = 6;
    // set_time.tm_sec = 6;
    // setSystemTime(set_time);

    // m5::rtc_time_t rtc_time;
    // m5::rtc_date_t rtc_date;
    // while (1)
    // {
    //     _rtc->getTime(&rtc_time);
    //     _rtc->getDate(&rtc_date);
    //     printf("%02d:%02d:%02d %04d,%02d,%02d,%02d\n",
    //            rtc_time.hours,
    //            rtc_time.minutes,
    //            rtc_time.seconds,
    //            rtc_date.year,
    //            rtc_date.month,
    //            rtc_date.date,
    //            rtc_date.weekDay);

    //     delay(1000);
    // }
}

void HAL_Regina::setSystemTime(tm dateTime)
{
    _rtc->setDateTime(dateTime);
    _adjust_sys_time();
}

void HAL_Regina::_adjust_sys_time()
{
    spdlog::info("adjust system time");

    auto time = _rtc->getDateTime().get_tm();
    time_t tv_sec = mktime(&time);

    struct timeval now;
    now.tv_sec = tv_sec;

    settimeofday(&now, NULL);
}

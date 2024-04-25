file(GLOB_RECURSE APP_LAYER_SRCS
    ../../../app/*.c
    ../../../app/*.cpp
)

set(APP_LAYER_INCS
    ../../../app
)

file(GLOB_RECURSE HAL_ESP32S3_SRCS
    ./hal_esp32s3/*.c
    ./hal_esp32s3/*.cpp
)

idf_component_register(SRCS "app_main.cpp" ${APP_LAYER_SRCS} ${HAL_ESP32S3_SRCS}
                    INCLUDE_DIRS "." ${APP_LAYER_INCS})

file(GLOB_RECURSE APP_LAYER_SRCS
    ../../../app/*.c
    ../../../app/*.cpp
)

set(APP_LAYER_INCS
    ../../../app
)

file(GLOB_RECURSE HAL_REGINA_SRCS
    ./hal_regina/*.c
    ./hal_regina/*.cpp
)

idf_component_register(SRCS "regina.cpp" ${APP_LAYER_SRCS} ${HAL_REGINA_SRCS}
                    INCLUDE_DIRS "." ${APP_LAYER_INCS})

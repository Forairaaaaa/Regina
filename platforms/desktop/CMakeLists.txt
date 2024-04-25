# See how to install sdl2: https://wiki.libsdl.org/SDL2/Installation
cmake_minimum_required (VERSION 3.8)
project(DesktopBuild)

# LovyanGFX
add_definitions(-DLGFX_SDL)

# ビルド対象にするファイルを指定する;
# LovyanGFXのあるパスと位置関係を変えた場合は相対パス記述を環境に合わせて調整すること;
file(GLOB Target_Files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} CONFIGURE_DEPENDS 
    dependencies/LovyanGFX/src/lgfx/Fonts/efont/*.c
    dependencies/LovyanGFX/src/lgfx/Fonts/IPA/*.c
    dependencies/LovyanGFX/src/lgfx/utility/*.c
    dependencies/LovyanGFX/src/lgfx/v1/*.cpp
    dependencies/LovyanGFX/src/lgfx/v1/misc/*.cpp
    dependencies/LovyanGFX/src/lgfx/v1/panel/Panel_Device.cpp
    dependencies/LovyanGFX/src/lgfx/v1/panel/Panel_FrameBufferBase.cpp
    dependencies/LovyanGFX/src/lgfx/v1/platforms/sdl/*.cpp
    )
# add_executable (LGFX_SDL ${Target_Files})
add_library(lovyangfx ${Target_Files})

# includeするファイルのパスを指定する;
# LovyanGFXのあるパスと位置関係を変えた場合は相対パス記述を環境に合わせて調整すること;
target_include_directories(lovyangfx PUBLIC dependencies/LovyanGFX/src/)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")

# Linux環境の場合;
# SDL2_INCLUDE_DIRS と SDL2_LIBRARIES を事前に設定しておく;
    find_package(SDL2 REQUIRED SDL2)
    include_directories(${SDL2_INCLUDE_DIRS})
    target_link_libraries(lovyangfx -lpthread ${SDL2_LIBRARIES})

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")

# Windows環境の場合;
# SDL2を配置したパス内のincludeのパスを指定する;
    target_include_directories(lovyangfx PUBLIC "C:/SDL2/include")

# SDL2を配置したパス内の.libファイルのパスを指定する;
    target_link_libraries(lovyangfx PUBLIC "C:/SDL2/lib/x64/SDL2.lib")


    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/Zc:__cplusplus>")

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")

# MacOS(Darwin)環境の場合;
    find_package(SDL2 REQUIRED COMPONENTS SDL2)
    target_link_libraries(lovyangfx PRIVATE SDL2::SDL2)

ENDIF ()

target_compile_features(lovyangfx PUBLIC cxx_std_17)

# Mooncake 
add_subdirectory(dependencies/mooncake)

# Smooth ui toolkit 
add_subdirectory(dependencies/smooth_ui_toolkit)

# App layer
file(GLOB_RECURSE APP_LAYER_SRCS
    app/*.c
    app/*.cpp
)
set(APP_LAYER_INCS
    app/
)
add_library(app_layer ${APP_LAYER_SRCS})
target_include_directories(app_layer PUBLIC ${APP_LAYER_INCS})
target_link_libraries(app_layer PUBLIC mooncake smooth_ui_toolkit lovyangfx)

set(EXTRA_INCS 
    dependencies/LovyanGFX/src/
)

# Desktop build
file(GLOB_RECURSE APP_DESKTOP_BUILD_SRCS
    platforms/desktop/*.cpp
)
add_executable(app_desktop_build ${APP_DESKTOP_BUILD_SRCS})
target_link_libraries(app_desktop_build PUBLIC app_layer)

# 设置构建路径
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build/desktop)

# 确保构建路径存在
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR})

# 设置生成的可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# # 设置生成的库文件输出路径
# set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

cmake_minimum_required(VERSION 3.8)
project(MC_APP_BOILERPLATE VERSION 0.1.0 LANGUAGES C CXX)

# Platform
option(PLATFORM_BUILD_DESKTOP "Build for platform desktop" ON)

if(PLATFORM_BUILD_DESKTOP)
    add_definitions(-DPLATFORM_BUILD_DESKTOP)
    include(platforms/desktop/CMakeLists.txt)
endif()

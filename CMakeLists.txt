cmake_minimum_required(VERSION 3.20)
project(nyabi-f LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (APPLE)
    list(PREPEND CMAKE_PREFIX_PATH "/opt/homebrew")
endif ()

find_package(PkgConfig REQUIRED)
find_package(Threads REQUIRED)

pkg_check_modules(LIBRAW REQUIRED IMPORTED_TARGET libraw)
pkg_check_modules(EXIV2 REQUIRED IMPORTED_TARGET exiv2)

find_package(OpenCV CONFIG REQUIRED core imgproc imgcodecs highgui dnn)
find_package(onnxruntime CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

include(FetchContent)
FetchContent_Declare(
        SQLiteCpp
        GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp.git
        GIT_TAG 3.3.1
)
set(SQLITECPP_RUN_CPPCHECK OFF CACHE BOOL "" FORCE)
set(SQLITECPP_RUN_CPPLINT OFF CACHE BOOL "" FORCE)
set(SQLITECPP_INTERNAL_SQLITE ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(SQLiteCpp)

add_executable(nyabi-f
        src/main.cpp
        include/types.hpp
        include/raw_decoder.hpp
        src/raw_decoder.cpp)

target_include_directories(nyabi-f PRIVATE include)

target_compile_options(nyabi-f PRIVATE -Wall -Wextra -Wpedantic)

target_link_libraries(nyabi-f PRIVATE
        opencv_core opencv_imgproc opencv_imgcodecs opencv_highgui opencv_dnn
        onnxruntime::onnxruntime
        spdlog::spdlog
        SQLiteCpp
        Threads::Threads
        PkgConfig::LIBRAW
        PkgConfig::EXIV2
)
cmake_minimum_required(VERSION 3.20)
project(nyabi-f LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(APPLE)
    list(PREPEND CMAKE_PREFIX_PATH "/opt/homebrew")
endif()

find_package(OpenCV CONFIG REQUIRED)
find_package(onnxruntime CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_executable(nyabi-f
        src/main.cpp
)

target_include_directories(nyabi-f PRIVATE
        include
)

target_link_libraries(nyabi-f PRIVATE
        opencv_core opencv_imgproc opencv_imgcodecs opencv_highgui opencv_dnn
        onnxruntime::onnxruntime
        spdlog::spdlog
)

target_compile_definitions(nyabi-f PRIVATE
        DEFAULT_MODEL_PATH="${CMAKE_SOURCE_DIR}/models/yolo26n.onnx"
)
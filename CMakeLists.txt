cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0025 NEW) # Compiler id for Apple Clang is now AppleClang above Cmake 3.0

project(teaching_assistant_scheduling_framework)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_EXTENSIONS ON) # Boolean specifying whether compiler specific extensions are requested.

add_executable(${PROJECT_NAME}
    "src/main.cpp"
    "src/csvio.h"
    "src/lecturer.h"
    "src/course.h"
    "src/assistant.h"
    "src/data.h"
    "src/greedysolver.h"
    "src/optimalsolver.h"
    )

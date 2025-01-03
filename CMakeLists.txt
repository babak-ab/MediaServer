# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)


# Check if the compiler is MSVC (Microsoft Visual Studio)
set(Boost_USE_STATIC_LIBS ON)
# Set the Vcpkg toolchain file for MSVC
set(CMAKE_TOOLCHAIN_FILE "C:/Projects/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(VCPKG_HOST_TRIPLET "x64-windows")
set(CMAKE_CXX_STANDARD 20)
set(Boost_NO_WARN_NEW_VERSIONS 1)
# Project name and language
project(MediaServer LANGUAGES CXX)


include_directories(${CMAKE_SOURCE_DIR}/utils ${CMAKE_SOURCE_DIR}/protocols/rtp)

file(GLOB SOURCES
    ${CMAKE_SOURCE_DIR}/main.cpp
    ${CMAKE_SOURCE_DIR}/utils/*.cpp
    ${CMAKE_SOURCE_DIR}/protocols/rtp/*.cpp
)



add_executable(MediaServer  ${SOURCES})

# Find the required Boost components
find_package(Boost REQUIRED COMPONENTS system thread filesystem)
find_package(Threads REQUIRED)

# Create an executable for the MediaServer project (with the source files)

message(STATUS "Found Boost version: ${Boost_VERSION}")



target_include_directories(MediaServer PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(MediaServer ${Boost_LIBRARIES})
# Add the executable target

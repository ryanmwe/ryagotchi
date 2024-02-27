project(ryagotchi)
cmake_minimum_required(VERSION 3.13)

# Define your project name


# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Load and configure the PlatformIO CMake toolchain file
# This assumes you have PlatformIO Core CLI installed and available in your system's PATH
# You might need to adjust the path to the PlatformIO CMake toolchain file based on your PlatformIO installation
set(PLATFORMIO_CMAKE_TOOLCHAIN_PATH $ENV{HOME}/.platformio/packages/toolchain-xtensa/cmake/PlatformIOToolchain.cmake)
if(EXISTS ${PLATFORMIO_CMAKE_TOOLCHAIN_PATH})
    include(${PLATFORMIO_CMAKE_TOOLCHAIN_PATH})
else()
    message(FATAL_ERROR "Cannot find PlatformIO CMake toolchain file. Please check your PlatformIO installation.")
endif()

# Define the board and framework as you would in the platformio.ini
add_definitions(-DPLATFORMIO=50100) # Adjust the version as necessary
add_definitions(-DARDUINO_ESP8266_ESP12)
add_definitions(-DF_CPU=80000000L)
add_definitions(-DARDUINO_ARCH_ESP8266)
add_definitions(-DARDUINO=10805) # Adjust based on your Arduino framework version

# Include the Arduino framework and libraries
# Adjust the paths based on your PlatformIO and Arduino framework installations
include_directories($ENV{HOME}/.platformio/packages/framework-arduinoespressif8266/cores/esp8266)
include_directories($ENV{HOME}/.platformio/packages/framework-arduinoespressif8266/tools/sdk/include)
include_directories($ENV{HOME}/.platformio/packages/framework-arduinoespressif8266/tools/sdk/lwip2/include)
include_directories($ENV{HOME}/.platformio/packages/framework-arduinoespressif8266/variants/nodemcu)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/Adafruit_GFX_Library)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/Adafruit_ILI9341)

# Add your source files
file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# Define your executable and link libraries
add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/Adafruit_GFX_Library ${CMAKE_CURRENT_SOURCE_DIR}/lib/Adafruit_ILI9341)

# Custom upload target (if needed)
add_custom_target(
        upload
        COMMAND platformio run --target upload
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

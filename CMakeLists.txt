# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
#set(PICO_CXX_ENABLE_EXCEPTIONS 1)
set(PICO_BOARD pico2_w CACHE STRING "Board type")

# Set top source code folder
set(SOURCE_FOLDER "src")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(ProgVehicle2 C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(ProgVehicle2 
ProgVehicle2.cpp 
"${SOURCE_FOLDER}/Source Files/Comms/BluetoothComms.cpp"
"${SOURCE_FOLDER}/Source Files/Json/Parsers/MetaPacket/MetaPacketParser.cpp"
"${SOURCE_FOLDER}/Source Files/Json/Parsers/TelemetryPacket/TelemetryPacketParser.cpp"
"${SOURCE_FOLDER}/Source Files/Json/Parsers/ProgramPacket/ProgramPacketParser.cpp"
"${SOURCE_FOLDER}/Source Files/Json/Parsers/ControlPacket/ControlPacketParser.cpp"
"${SOURCE_FOLDER}/Source Files/Json/Parsers/MovementPacket/MovementPacketParser.cpp"
"${SOURCE_FOLDER}/Source Files/Controllers/Command/CommandController.cpp"
"${SOURCE_FOLDER}/Source Files/Storage/Buffers/CircularBuffer.cpp"
"${SOURCE_FOLDER}/Source Files/TemplateDefinitions.cpp"
"${SOURCE_FOLDER}/Source Files/Controllers/CoreQueue/Core0Core1QueueController.cpp"
"${SOURCE_FOLDER}/Source Files/Cores/CoreTask/Core0Task.cpp"
"${SOURCE_FOLDER}/Source Files/Cores/CoreTask/Core1Task.cpp"
)

pico_set_program_name(ProgVehicle2 "ProgVehicle2")
pico_set_program_version(ProgVehicle2 "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(ProgVehicle2 1)
pico_enable_stdio_usb(ProgVehicle2 0)

# Add the standard library to the build
target_link_libraries(ProgVehicle2
        pico_stdlib
        pico_btstack_classic
        pico_btstack_cyw43
        pico_multicore
  )

# Add the standard include files to the build
target_include_directories(ProgVehicle2 PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        "${SOURCE_FOLDER}/Header Files/Comms/"
        "${SOURCE_FOLDER}/Header Files/"
        "${SOURCE_FOLDER}/Header Files/Types"
        "${SOURCE_FOLDER}/Header Files/Types/Controllers/"
        "${SOURCE_FOLDER}/Header Files/Types/JsonDefinitions/"
        "${SOURCE_FOLDER}/Header Files/Json/",
        "${SOURCE_FOLDER}/Header Files/Json/Converters",
        "${SOURCE_FOLDER}/Header Files/Json/Parsers"
        "${SOURCE_FOLDER}/Header Files/Json/Parsers/MetaPacket"
        "${SOURCE_FOLDER}/Header Files/Json/Parsers/TelemetryPacket"
        "${SOURCE_FOLDER}/Header Files/Json/Parsers/ProgramPacket"
        "${SOURCE_FOLDER}/Header Files/Json/Parsers/ControlPacket"
        "${SOURCE_FOLDER}/Header Files/Json/Parsers/MovementPacket"
        "${SOURCE_FOLDER}/Header Files/Control/"      
        "${SOURCE_FOLDER}/Header Files/Controllers/Command/"  
        "${SOURCE_FOLDER}/Header Files/Controllers/CoreQueue/" 
        "${SOURCE_FOLDER}/Header Files/Storage/Buffers/" 
        "${SOURCE_FOLDER}/Source Files/Storage/Buffers/"
        "${SOURCE_FOLDER}/Header Files/Cores/CoreTask"
)


# Add any user requested libraries
target_link_libraries(ProgVehicle2 
        pico_cyw43_arch_lwip_threadsafe_background
        )

pico_add_extra_outputs(ProgVehicle2)


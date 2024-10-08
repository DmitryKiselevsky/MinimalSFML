﻿# CMakeList.txt : CMake project for MinimalSFML, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("MinimalSFML")

# Path to libs
set(SFML_DIR "SFML-2.6.1")

# Search for SFML package
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    # For Linux 
    set(SFML_DIR "~/SFML-2.6.1/lib/cmake/SFML")
else()
    # For another OS SFML 2.6.1
    find_package(SFML 2.6.1 COMPONENTS graphics audio window system REQUIRED)
endif()

# Add source to this project's executable.
add_executable (MinimalSFML "main.cpp" "Button.cpp" "Label.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MinimalSFML PROPERTY CXX_STANDARD 20)
endif()

file(COPY ${CMAKE_SOURCE_DIR}/roboto.ttf DESTINATION ${CMAKE_BINARY_DIR})

# Link SFML to project
if (WIN32)
    target_link_libraries(MinimalSFML sfml-graphics sfml-window sfml-system)
    set_target_properties(MinimalSFML PROPERTIES
        WIN32_EXECUTABLE TRUE
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
        file(COPY ${CMAKE_SOURCE_DIR}/roboto.ttf DESTINATION ${CMAKE_BINARY_DIR}/bin)
else()
    target_link_libraries(MinimalSFML sfml-graphics sfml-window sfml-system)
endif()
# TODO: Add tests and install targets if needed.

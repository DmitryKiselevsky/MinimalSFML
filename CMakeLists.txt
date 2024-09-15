# CMakeList.txt : CMake project for MinimalSFML, include source and define
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
find_package(SFML 2.6.1 COMPONENTS graphics audio REQUIRED)

# Add source to this project's executable.
add_executable (MinimalSFML "MinimalSFML.cpp" "MinimalSFML.h" "Button.cpp" "Label.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MinimalSFML PROPERTY CXX_STANDARD 20)
endif()

# Link SFML to project
target_link_libraries(MinimalSFML PRIVATE sfml-graphics sfml-audio)
# TODO: Add tests and install targets if needed.

cmake_minimum_required(VERSION 3.21)

project(aoc_2023 VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

# project
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "src/*.h" "src/*.c")

add_executable("${PROJECT_NAME}" ${SOURCE_FILES})
set_target_properties("${PROJECT_NAME}" PROPERTIES DEBUG_POSTFIX "-Debug")
target_include_directories("${PROJECT_NAME}" PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/src")

# system
if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
  target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC LINUX)
endif()


target_compile_definitions("${PROJECT_NAME}" PUBLIC "$<$<CONFIG:DEBUG>:_DEBUG>")
target_compile_definitions("${PROJECT_NAME}" PUBLIC "$<$<CONFIG:RELEASE>:_RELEASE>")

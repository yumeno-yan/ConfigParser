cmake_minimum_required(VERSION 3.27)
project(ConfigParser)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCE_FILES HEADER_FILES "*.h")
file(GLOB SOURCE_FILES SOURCE_FILES "*.cpp")

include_directories(${CMAKE_SOURCE_DIR})
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

cmake_minimum_required(VERSION 3.10)
project(my_api_project)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Crow/include)

add_executable(my_api_project main.cpp)

find_package(Boost 1.71.0 COMPONENTS system thread REQUIRED)
target_link_libraries(my_api_project ${Boost_LIBRARIES})

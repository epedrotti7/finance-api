cmake_minimum_required(VERSION 3.10)
project(finance_api)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH /usr/lib/x86_64-linux-gnu)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/crow/include)

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})
include_directories(${JSONCPP_INCLUDE_DIRS})

find_library(MYSQL_CPP_CONN mysqlcppconn)
include_directories(/usr/include/mysql-cppconn-8)
link_directories(/usr/lib/x86_64-linux-gnu)
link_libraries(${MYSQL_CPP_CONN})

include_directories(src/headers)

add_executable(finance_api src/main.cpp src/database.cpp src/expense_repository.cpp)
target_link_libraries(finance_api ${MYSQL_LIBRARIES} -lmysqlclient)

cmake_minimum_required(VERSION 3.10)

project(HomeBudgetCpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SQLite3 REQUIRED)

add_executable(home_budget
    main.cpp
    budget.cpp
    transaction.cpp
    sqlite_storage.cpp
)

target_link_libraries(home_budget PRIVATE
    SQLite3::SQLite3
)

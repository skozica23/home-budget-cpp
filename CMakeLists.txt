cmake_minimum_required(VERSION 3.10)

project(HomeBudgetCpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(home_budget
    main.cpp
    budget.cpp
    transaction.cpp
)

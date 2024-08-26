project(lc_projects)

cmake_minimum_required(VERSION 3.5)

add_executable(task)

target_sources(task PRIVATE
    test.hpp
    test.cpp
    main.cpp
)

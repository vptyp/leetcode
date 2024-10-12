project(lc_projects)

cmake_minimum_required(VERSION 3.5)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(task)

target_include_directories(task PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    env
    problems
    variadic_table/include
)
target_sources(task PRIVATE
    env/test.hpp
    env/test.cpp
    problems/digital_key.hpp
    problems/digital_key.cpp
    problems/key.hpp
    problems/key.cpp
    main.cpp
)

install(TARGETS task DESTINATION bin)
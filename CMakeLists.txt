project(lc_projects)

cmake_minimum_required(VERSION 3.5)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CXX_STANDARD_REQUIRED 20)

find_package(glog REQUIRED)
find_package(readerwriterqueue REQUIRED)
add_executable(task)

target_link_libraries(task PRIVATE 
    glog::glog
    readerwriterqueue::readerwriterqueue
)
target_include_directories(task PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    env
    problems
)
target_sources(task PRIVATE
    env/test.hpp
    env/test.cpp
    problems/digital_key.hpp
    problems/digital_key.cpp
    main.cpp
)

install(TARGETS task DESTINATION bin)
cmake_minimum_required(VERSION 3.10)

project(webserver)

add_executable(webserver
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/")
target_link_libraries(webserver PUBLIC
    libs
)
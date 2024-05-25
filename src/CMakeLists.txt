add_library(libs
    "${CMAKE_CURRENT_SOURCE_DIR}/httpServer.cpp"
)

target_include_directories(libs PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../include/"
)
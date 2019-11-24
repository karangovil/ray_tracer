project(Catch)

# Make catch an object library so main.cpp gets reused across tests
add_library(catch OBJECT ${CMAKE_CURRENT_SOURCE_DIR}/test_main.cpp)

# INTERFACE targets only have INTERFACE properties
target_include_directories(catch INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

set(CMAKE_BUILD_TYPE Debug)

file(RELATIVE_PATH REL_PATH ${PROJECT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
STRING(REPLACE "/" "." REL_PATH ${REL_PATH})

set(TARGET1 ${REL_PATH}.testTuple)
set(SOURCES1 test_main.cpp
             test_tuple.cpp)

add_executable(${TARGET1} ${SOURCES1})

target_include_directories(${TARGET1} PUBLIC ${CMAKE_SOURCE_DIR}/libs/catch)

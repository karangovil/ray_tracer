enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

set(CMAKE_BUILD_TYPE Debug)

set(TARGET1 projectile)
set(SOURCES1 env.cpp)

add_executable(${TARGET1} ${SOURCES1})

target_include_directories(${TARGET1} PUBLIC ${CMAKE_SOURCE_DIR}/libs/catch)

set(TARGET2 clock)
set(SOURCES2 clock.cpp)

add_executable(${TARGET2} ${SOURCES2})

target_include_directories(${TARGET2} PUBLIC ${CMAKE_SOURCE_DIR}/libs/catch)

set(TARGET3 raySphere)
set(SOURCES3 raySphereProj.cpp)

add_executable(${TARGET3} ${SOURCES3})

target_include_directories(${TARGET3} PUBLIC ${CMAKE_SOURCE_DIR}/libs/catch)


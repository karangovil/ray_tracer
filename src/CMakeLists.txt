enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

set(CMAKE_BUILD_TYPE Release)

set(TARGET1 projectile)
set(SOURCES1 env.cpp)

add_executable(${TARGET1} ${SOURCES1})

set(TARGET2 clock)
set(SOURCES2 clock.cpp)

add_executable(${TARGET2} ${SOURCES2})

set(TARGET3 raySphere)
set(SOURCES3 raySphereProj.cpp)

add_executable(${TARGET3} ${SOURCES3})


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

set(TARGET2 ${REL_PATH}.testColors)
set(SOURCES2 test_main.cpp
             test_colors.cpp)

add_executable(${TARGET2} ${SOURCES2})

target_include_directories(${TARGET2} PUBLIC ${CMAKE_SOURCE_DIR}/libs/catch)

set(TARGET3 ${REL_PATH}.testMatrix)
set(SOURCES3 test_main.cpp
             test_matrix.cpp)

add_executable(${TARGET3} ${SOURCES3})

target_include_directories(${TARGET3} PUBLIC ${CMAKE_SOURCE_DIR}/libs/catch)

set(TARGET4 ${REL_PATH}.testMatrix4x4)
set(SOURCES4 test_main.cpp
             test_matrix4x4.cpp)

add_executable(${TARGET4} ${SOURCES4})

target_include_directories(${TARGET4} PUBLIC ${CMAKE_SOURCE_DIR}/libs/catch)

set(TARGET5 ${REL_PATH}.testTransformations)
set(SOURCES5 test_main.cpp
             test_transformations.cpp)

add_executable(${TARGET5} ${SOURCES5})

target_include_directories(${TARGET5} PUBLIC ${CMAKE_SOURCE_DIR}/libs/catch)

set(TARGET6 ${REL_PATH}.testCanvas)
set(SOURCES6 test_main.cpp
             test_canvas.cpp)

add_executable(${TARGET6} ${SOURCES6})

target_include_directories(${TARGET6} PUBLIC ${CMAKE_SOURCE_DIR}/libs/catch)

set(TARGET7 ${REL_PATH}.testRay)
set(SOURCES7 test_main.cpp
             test_ray.cpp)

add_executable(${TARGET7} ${SOURCES7})

target_include_directories(${TARGET7} PUBLIC ${CMAKE_SOURCE_DIR}/libs/catch)

set(TARGET8 ${REL_PATH}.testSphere)
set(SOURCES8 test_main.cpp
             test_sphere.cpp)

add_executable(${TARGET8} ${SOURCES8})

target_include_directories(${TARGET8} PUBLIC ${CMAKE_SOURCE_DIR}/libs/catch)

set(TARGET9 ${REL_PATH}.testIntersection)
set(SOURCES9 test_main.cpp
             test_intersection.cpp)

add_executable(${TARGET9} ${SOURCES9})

target_include_directories(${TARGET9} PUBLIC ${CMAKE_SOURCE_DIR}/libs/catch)


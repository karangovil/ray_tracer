enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

set(CMAKE_BUILD_TYPE Debug)

file(RELATIVE_PATH REL_PATH ${PROJECT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
STRING(REPLACE "/" "." REL_PATH ${REL_PATH})

function(add_new_test name)
    set(TARGET_NEW ${REL_PATH}.${name})
    add_executable(${TARGET_NEW} ${name}.cpp)
    target_link_libraries(${TARGET_NEW} catch)
    target_link_libraries(${TARGET_NEW} rayTracerImpl)
    target_link_libraries(${TARGET_NEW} ray_tracer)
    add_test(NAME ${name} COMMAND ${TARGET_NEW})
endfunction()

add_new_test(testSphere)
add_new_test(testMaterial)
add_new_test(testPlane)
add_new_test(testObject)

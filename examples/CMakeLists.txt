set(CMAKE_BUILD_TYPE Release)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

function(add_new_target name)
    set(TARGET_NEW ${name})
    add_executable(${TARGET_NEW} ${name}.cpp)
    target_link_libraries(${TARGET_NEW} ray_tracer)
    target_link_libraries(${TARGET_NEW} rayTracerImpl)
endfunction()

add_new_target(projectile)
add_new_target(clock)
add_new_target(raySphere)
add_new_target(multipleSpheres)
add_new_target(multipleSpheresPlane)
add_new_target(shadowPuppet)

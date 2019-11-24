set(CMAKE_BUILD_TYPE Release)

function(add_new_target name)
    set(TARGET_NEW ${name})
    add_executable(${TARGET_NEW} ${name}.cpp)
    target_link_libraries(${TARGET_NEW} ray_tracer)
endfunction()

add_new_target(projectile)
add_new_target(clock)
add_new_target(raySphere)

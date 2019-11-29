project(RayTracerImpl)

add_subdirectory(shapes)
add_subdirectory(graphics)

add_library(rayTracerImpl OBJECT ${SHAPE_SOURCES} ${GRAPHICS_SOURCES})

target_link_libraries(rayTracerImpl ray_tracer)

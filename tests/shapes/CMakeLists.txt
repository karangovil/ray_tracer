enable_testing()

file(RELATIVE_PATH REL_PATH ${PROJECT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
STRING(REPLACE "/" "." REL_PATH ${REL_PATH})

add_new_test(${REL_PATH} testSphere)
add_new_test(${REL_PATH} testMaterial)
add_new_test(${REL_PATH} testPlane)
add_new_test(${REL_PATH} testObject)

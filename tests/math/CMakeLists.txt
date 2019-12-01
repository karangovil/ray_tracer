enable_testing()

file(RELATIVE_PATH REL_PATH ${PROJECT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
STRING(REPLACE "/" "." REL_PATH ${REL_PATH})

add_new_test(${REL_PATH} testTuple)
add_new_test(${REL_PATH} testTransformations)
add_new_test(${REL_PATH} testMatrix4x4)
add_new_test(${REL_PATH} testMatrix)

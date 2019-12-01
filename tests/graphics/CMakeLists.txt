enable_testing()

file(RELATIVE_PATH REL_PATH ${PROJECT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
STRING(REPLACE "/" "." REL_PATH ${REL_PATH})

add_new_test(${REL_PATH} testColors)
add_new_test(${REL_PATH} testCanvas)
add_new_test(${REL_PATH} testReflection)
add_new_test(${REL_PATH} testRay)
add_new_test(${REL_PATH} testIntersection)
add_new_test(${REL_PATH} testLight)
add_new_test(${REL_PATH} testWorld)
add_new_test(${REL_PATH} testComputations)
add_new_test(${REL_PATH} testCamera)

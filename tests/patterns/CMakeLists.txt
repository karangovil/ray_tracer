enable_testing()

file(RELATIVE_PATH REL_PATH ${PROJECT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
STRING(REPLACE "/" "." REL_PATH ${REL_PATH})

add_new_test(${REL_PATH} testAllPatterns)
add_new_test(${REL_PATH} testPattern)
add_new_test(${REL_PATH} testJitter)

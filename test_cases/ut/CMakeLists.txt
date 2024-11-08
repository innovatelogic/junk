
if (${ENABLE_TESTING})

set(PROJECT_TEST_NAME unittest_${PROJECT_NAME})

include (CTest)

include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${PROJECT_DIR}/src/ut)

file(GLOB_RECURSE UT_SOURCE
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

# setup folder filters
#assign_source_group(${UT_SOURCE})

#set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_TEST_NAME} ${UT_SOURCE})

target_include_directories(${PROJECT_TEST_NAME} PRIVATE 
${PROJECT_DIR}/third_party
#${PROJECT_DIR}/third_party/Eigen
#${XTENSOR_BLAS_INCLUDE_DIR}
${Python3_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_TEST_NAME} 
${PROJECT_NAME} 
${Python3_LIBRARIES} 
GTest::gtest
LLVM
clang
clangAST 
clangBasic 
clangFrontend 
clangParse
clangTooling
clangFrontend
clangASTMatchers
clangParse
clangSema
clangAnalysis
clangEdit
clangLex
clangDriver
pthread 
dl)

add_definitions(-DUSE_MOCK)

add_test(NAME ${PROJECT_TEST_NAME}
         COMMAND ${PROJECT_TEST_NAME}
         WORKING_DIRECTORY ${G_BIN_DIR})

gtest_discover_tests(${PROJECT_TEST_NAME})

#set_target_properties(${PROJECT_TEST_NAME} PROPERTIES FOLDER "UT" )

set_target_properties(${PROJECT_TEST_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${G_BIN_DIR}
    LIBRARY_OUTPUT_DIRECTORY_DEBUG ${G_BIN_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${G_BIN_DIR}
    LIBRARY_OUTPUT_DIRECTORY_RELEASE ${G_BIN_DIR}
)

#set_target_properties( ${PROJECT_TEST_NAME} PROPERTIES
#        OUTPUT_NAME ${PROJECT_TEST_NAME}.test
#        DEBUG_POSTFIX ""
#)

if (${RUN_TESTS_AFTER_BUILD})
add_custom_command(
     TARGET ${PROJECT_TEST_NAME}
     COMMENT "Run core tests"
     POST_BUILD 
     WORKING_DIRECTORY ${G_BIN_DIR}
     COMMAND ${CMAKE_COMMAND} -E echo "Start"
     #COMMAND ${G_BIN_DIR}/${PROJECT_TEST_NAME}
     COMMAND ${CMAKE_COMMAND} -E echo "Complete"
)
endif()

#install(TARGETS ${PROJECT_TEST_NAME} DESTINATION .)

endif(${ENABLE_TESTING})

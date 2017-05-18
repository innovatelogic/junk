cmake_minimum_required(VERSION 3.0.0)

set(ENABLE_TESTING ON)

set(ENABLE_GTEST ON)
SET(GTEST_LIBRARIES optimized ${CMAKE_BINARY_DIR}/../Libs/gtest.lib debug ${CMAKE_BINARY_DIR}/../Libs/gtest_d.lib)
SET(GTEST_BOTH_LIBRARIES ${GTEST_LIBRARIES} optimized ${CMAKE_BINARY_DIR}/../Libs/gtest_main.lib 
											debug ${CMAKE_BINARY_DIR}/../Libs/gtest_main_d.lib)

SET(GMOCK_LIBRARY optimized ${CMAKE_BINARY_DIR}/../Libs/gmock.lib debug ${CMAKE_BINARY_DIR}/../Libs/gmock_d.lib)
SET(GMOCK_BOTH_LIBRARIES ${GMOCK_LIBRARY} optimized ${CMAKE_BINARY_DIR}/../Libs/gmock_main.lib debug ${CMAKE_BINARY_DIR}/../Libs/gmock_main_d.lib)

if(ENABLE_TESTING)
#find_package(GTest REQUIRED)
#find_package(GMock REQUIRED)
	enable_testing()
endif()

add_subdirectory(src_cie_conv)
add_subdirectory(src_arr)
add_subdirectory(src_bst)
add_subdirectory(src_dp)
add_subdirectory(src_str)
add_subdirectory(src_list)
add_subdirectory(src_graph)
add_subdirectory(src_cpp)
add_subdirectory(src)
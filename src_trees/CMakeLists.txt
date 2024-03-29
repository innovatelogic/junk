cmake_minimum_required(VERSION 2.8)

project(trees)

add_definitions(-DUNICODE -D_UNICODE)
add_definitions(-DTREES_LIB_COMPILE)
#add_definitions(-DGTEST_LINKED_AS_SHARED_LIBRARY)

set( GRAPH ${PROJECT_NAME} )

set(SOURCE 
	oembase.h
	defexport.h
	trees.h
	file.cpp
	binary_tree.h
	tree_is_balanced.h
	tree_traverse.h
	btree_is_subtree_probe_a.h
	btree_all_path_sum_probe_a.h
	find_max_path_in_tree.h
)

add_library(${PROJECT_NAME} SHARED ${SOURCE})

target_link_libraries(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES
					RUNTIME_OUTPUT_DIRECTORY_DEBUG ${G_BIN_DIR}
					LIBRARY_OUTPUT_DIRECTORY_DEBUG ${G_BIN_DIR}
					RUNTIME_OUTPUT_DIRECTORY_RELEASE ${G_BIN_DIR}
					LIBRARY_OUTPUT_DIRECTORY_RELEASE ${G_BIN_DIR}
					)

#-------------------------------------------------------------------------------		
# setup testing
#-------------------------------------------------------------------------------
if (${ENABLE_TESTING})

	set( PROJECT_NAME ${PROJECT_NAME} )
	set( PROJECT_TEST_NAME unittest_${PROJECT_NAME} )
	string( TOUPPER ${PROJECT_NAME} PROJECT_NAME_U )

	include_directories(${CMAKE_SOURCE_DIR}/utils/googletest/googletest/include)
	
	add_executable( ${PROJECT_TEST_NAME} 
					ut/main.cpp
					ut/ut_tree_is_balanced.cpp
					ut/ut_binary_tree_traverse.cpp
					ut/ut_tree_traverse.cpp
					ut/ut_btree_all_path_sum_probe_a.cpp
					ut/ut_btree_is_subtree_probe_a.cpp
					ut/ut_find_max_path_in_tree.cpp
					)

	target_link_libraries(${PROJECT_TEST_NAME} ${GTEST_BOTH_LIBRARIES} ${GMOCK_BOTH_LIBRARIES})

	add_definitions(-DUSE_MOCK)

	add_test(NAME ${PROJECT_NAME_U}_TEST COMMAND ${PROJECT_TEST_NAME})

	set_target_properties(${PROJECT_TEST_NAME} PROPERTIES FOLDER "UT" )

	set_target_properties(${PROJECT_TEST_NAME} PROPERTIES
						RUNTIME_OUTPUT_DIRECTORY_DEBUG ${G_BIN_DIR}
						LIBRARY_OUTPUT_DIRECTORY_DEBUG ${G_BIN_DIR}
						RUNTIME_OUTPUT_DIRECTORY_RELEASE ${G_BIN_DIR}
						LIBRARY_OUTPUT_DIRECTORY_RELEASE ${G_BIN_DIR}
						)

	set_target_properties( ${PROJECT_TEST_NAME} PROPERTIES
            OUTPUT_NAME ${PROJECT_TEST_NAME}.test
            DEBUG_POSTFIX ""
        )

endif( ${ENABLE_TESTING} )
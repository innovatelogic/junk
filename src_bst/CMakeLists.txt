cmake_minimum_required(VERSION 2.8)

project(bst)

add_definitions(-DUNICODE -D_UNICODE)
add_definitions(-DLIB_COMPILE)
#add_definitions(-DGTEST_LINKED_AS_SHARED_LIBRARY)

set( BST ${PROJECT_NAME} )

set(SOURCE 
	oembase.h
	defexport.h
	bst_tree_probe_a.h
	bst_tree_probe_b.h
	bst_tree_probe_c.h
	bst_tree_probe_d.h
	bst_probe_e.h
	bst_tree_find_max_distinct_path_probe_e.h
	bst_tree_check_bst_probe_f.h
	bst_tree_get_max_width_probe_a.h
	bst_build_level_order_list_probe_f.h
	bst_find_next_successor.h
	bst_to_dlinked_list_probe_a.h
	bst.h
	file.cpp
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
	include_directories(${CMAKE_SOURCE_DIR}/utils/googletest/googletest/include)

	set( PROJECT_NAME ${PROJECT_NAME} )
	set( PROJECT_TEST_NAME unittest_${PROJECT_NAME} )
	string( TOUPPER ${PROJECT_NAME} PROJECT_NAME_U )

	add_executable( ${PROJECT_TEST_NAME} 
					ut/main.cpp
					ut/ut_bst.cpp
					ut/ut_bst_build_level_order_list_probe_f.cpp
					ut/ut_bst_find_next_successor.cpp
					ut/ut_bst_probe_b.cpp
					ut/ut_bst_probe_c.cpp
					ut/ut_bst_probe_e.cpp
					ut/ut_bst_tree_probe_d.cpp
					ut/ut_bst_tree_find_max_distinct_path_probe_e.cpp
					ut/ut_bst_tree_get_max_width_probe_a.cpp
					ut/ut_bst_to_dlinked_list_probe_a.cpp
					ut/ut_bst_tree_check_bst_probe_f.cpp
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
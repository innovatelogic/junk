cmake_minimum_required(VERSION 2.8)

project(graph)

add_definitions(-DUNICODE -D_UNICODE)
add_definitions(-DLIB_COMPILE)
#add_definitions(-DGTEST_LINKED_AS_SHARED_LIBRARY)

set( GRAPH ${PROJECT_NAME} )

set(SOURCE 
	oembase.h
	defexport.h
	graph.h
	bfs_search_probe_a.h
	dijkstra_probe_a.h
	bellman_ford_probe_a.h
	dlist_probe_a.h
	array_2d_bfs_path_find.h
	array_2d_dyn_bfs_path_find.h
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

	set( PROJECT_NAME ${PROJECT_NAME} )
	set( PROJECT_TEST_NAME unittest_${PROJECT_NAME} )
	string( TOUPPER ${PROJECT_NAME} PROJECT_NAME_U )

	include_directories(${CMAKE_SOURCE_DIR}/utils/googletest/googletest/include)
	
	add_executable( ${PROJECT_TEST_NAME} 
					ut/main.cpp
					ut/ut_bellman_ford_probe_a.cpp
					ut/ut_dlist_probe_a.cpp
					ut/ut_array_2d_bfs_path_find.cpp
					ut/ut_array_2d_dyn_path_find.cpp
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
cmake_minimum_required(VERSION 2.8)

project(junk)

set(SOURCE 
	main.cpp
	custom_list.h
	custom_stack.h
	find_list_nth_from_end.h
	list_head_tail.h
	)

add_executable(${PROJECT_NAME} ${SOURCE})

set_target_properties( ${PROJECT_NAME} PROPERTIES
					RUNTIME_OUTPUT_DIRECTORY_DEBUG ${G_BIN_DIR}
					LIBRARY_OUTPUT_DIRECTORY_DEBUG ${G_BIN_DIR}
					RUNTIME_OUTPUT_DIRECTORY_RELEASE ${G_BIN_DIR}
					LIBRARY_OUTPUT_DIRECTORY_RELEASE ${G_BIN_DIR}
					)
					
#-------------------------------------------------------------------------------		
# setup testing
#-------------------------------------------------------------------------------
#if (${ENABLE_TESTING})

	enable_testing()

	include_directories(${CMAKE_SOURCE_DIR}/utils/googletest/googletest/include)
	add_executable( unittest.${PROJECT_NAME} 
					ut/ut_test.cpp
					ut/main.cpp )
	
	target_link_libraries(unittest.${PROJECT_NAME} ${GTEST_BOTH_LIBRARIES})

	set_target_properties(unittest.${PROJECT_NAME} PROPERTIES FOLDER "UT" )

	set_target_properties(unittest.${PROJECT_NAME} PROPERTIES
						RUNTIME_OUTPUT_DIRECTORY_DEBUG ${G_BIN_DIR}
						LIBRARY_OUTPUT_DIRECTORY_DEBUG ${G_BIN_DIR}
						RUNTIME_OUTPUT_DIRECTORY_RELEASE ${G_BIN_DIR}
						LIBRARY_OUTPUT_DIRECTORY_RELEASE ${G_BIN_DIR}
						)

#endif( ${ENABLE_TESTING} )					
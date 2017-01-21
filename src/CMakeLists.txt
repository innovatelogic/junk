cmake_minimum_required(VERSION 2.8)

project(junk)

add_definitions(-JUNK_LIB_COMPILE)
#add_definitions(-DLIB_COMPILE)
#add_definitions(-DGTEST_LINKED_AS_SHARED_LIBRARY)

set(SOURCE 
	oembase.h
	defexport.h
	custom_list.h
	custom_stack.h
	find_list_nth_from_end.h
	list_head_tail.h
	list_linearize.h
	circular_list.h
    inner_template_class.h
	inner_template_class.ipp	
	permutations_array.h
	smart_ptr.h
	junk.h
	file.cpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCE})

target_link_libraries(${PROJECT_NAME})

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
	include_directories(${CMAKE_SOURCE_DIR}/utils/googletest/googlemock/include)

	add_executable( unittest.${PROJECT_NAME} 
					ut/ut_test.cpp
					ut/ut_linearize.cpp
					ut/ut_circular_list.cpp
					ut/ut_smart_ptr.cpp
					ut/main.cpp )
	
	target_link_libraries(unittest.${PROJECT_NAME} ${PROJECT_NAME} ${GTEST_BOTH_LIBRARIES} ${GMOCK_BOTH_LIBRARIES})

	set_target_properties(unittest.${PROJECT_NAME} PROPERTIES FOLDER "UT" )

	set_target_properties(unittest.${PROJECT_NAME} PROPERTIES
						RUNTIME_OUTPUT_DIRECTORY_DEBUG ${G_BIN_DIR}
						LIBRARY_OUTPUT_DIRECTORY_DEBUG ${G_BIN_DIR}
						RUNTIME_OUTPUT_DIRECTORY_RELEASE ${G_BIN_DIR}
						LIBRARY_OUTPUT_DIRECTORY_RELEASE ${G_BIN_DIR}
						)

#endif( ${ENABLE_TESTING} )					
cmake_minimum_required(VERSION 2.8)

project(bits)

add_definitions(-DUNICODE -D_UNICODE)
add_definitions(-DLIB_BITS_COMPILE)
#add_definitions(-DGTEST_LINKED_AS_SHARED_LIBRARY)

set(SOURCE 
	oembase.h
	defexport.h
	bits_sum.h
	swap_no_tmp.h
	bits_lib.h
	tic_tac_toe.h
	binary_basic_operations.h
	binary_basic_operations.cpp
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
	set( PROJECT_TEST_NAME Tests_${PROJECT_NAME} )
	string( TOUPPER ${PROJECT_NAME} PROJECT_NAME_U )

	add_executable( ${PROJECT_TEST_NAME}
					ut/ut_bits_sum.cpp
					ut/ut_swap_no_tmp.cpp
					ut/ut_tic_tac_toe.cpp
					ut/ut_binary_basic_operations.cpp
					ut/main.cpp )
	
	target_link_libraries(${PROJECT_TEST_NAME} ${PROJECT_NAME} ${GTEST_BOTH_LIBRARIES})

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
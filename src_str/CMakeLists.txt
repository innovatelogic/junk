project(str_lib)

add_definitions(-DUNICODE -D_UNICODE)
add_definitions(-DLIB_COMPILE)
#add_definitions(-DGTEST_LINKED_AS_SHARED_LIBRARY)

set( STR ${PROJECT_NAME} )

set(SOURCE 
	oembase.h
	defexport.h
	file.cpp
	str.h
	string_convert_probe_a.h
	string_bin_frac_to_dec.h
	string_find_first_unique_probe_a.h
	shortest_substring_problem.h
	is_unique_chars_in_string.h
	is_unique_chars_in_string.cpp
	check_braces.h
	strings.h
	strings.cpp
	get_all_split_strings.h
	combinations.h
	subsets_in_string.h
	subsets_str_sum_probe_a.h
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
					ut/ut_str_find_first_unique_probe_a.cpp
					ut/ut_shortest_substring_problem.cpp
					ut/ut_braces_check.cpp
					ut/ut_strings.cpp
					ut/ut_get_all_split_strings.cpp
					ut/ut_combinations.cpp
					ut/ut_is_unique_chars_in_string.cpp
					ut/ut_string_convert_probe_a.cpp
					ut/ut_string_bin_frac_to_dec.cpp
					ut/ut_subsets_str_sum_probe_a.cpp
					)

	target_link_libraries(${PROJECT_TEST_NAME} ${PROJECT_NAME} ${GTEST_BOTH_LIBRARIES} ${GMOCK_BOTH_LIBRARIES})

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
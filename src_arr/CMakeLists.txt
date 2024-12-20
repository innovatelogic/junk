cmake_minimum_required(VERSION 2.8)

project(arr)

add_definitions(-DUNICODE -D_UNICODE)
add_definitions(-DLIB_COMPILE)
#add_definitions(-DGTEST_LINKED_AS_SHARED_LIBRARY)

include_directories(${CMAKE_SOURCE_DIR}/utils/googletest/googletest/include)
include_directories(${CMAKE_SOURCE_DIR}/utils/googletest/googlemock/include)

include_directories(${CMAKE_SOURCE_DIR}/src_arr)

set( ARR ${PROJECT_NAME} )

set(SOURCE 
	oembase.h
	defexport.h
	file.cpp
	bin_search_probe_a.h
	max_subarray_probe_a.h
	rev_int_probe_a.h
	array_sorted_rotation_point.h
	str_equation_analise_probe_a.h
	min_range_vacation_selector_probe_a.h
	histogram_max_rect_probe_a.h
	matrix_ccw.h
	combinations_of_sum_num.h
	string_permute_probe_a.h
	union_intersection_array_probe_a.h
	remove_duplicates_probe_b.h
	permutate.h
	array_combinations_probe_a.h
	array_frequency_rand.h
	array_reverse_inplace.h
	find_min_in_shifted_sorted_array.h
	arr.h
	is_palindrome.h
	two_sum_in_array.h
	peak_finding.h
	permutations_array.h
	permutate_probe_a.h
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

	add_executable( ${PROJECT_TEST_NAME} 
					ut/main.cpp
					ut/ut_rev_int.cpp
					ut/combinations_of_sum_num.cpp
					ut/matrix_ccw.cpp
					ut/ut_remove_duplicates_probe_b.cpp
					ut/ut_string_permute_probe_a.cpp
					ut/ut_union_intersection_array_probe_a.cpp
					ut/ut_str_find_substring_probe_a.cpp
					ut/ut_array_sorted_rotation_point.cpp
					ut/ut_str_equation_analise_probe_a.cpp
					ut/ut_histogram_max_rect_probe_a.cpp
					ut/ut_array_min_range_vacation_selector_probe_a.cpp
					ut/ut_array_binary_search_probe_a.cpp
					ut/ut_array_combinations_probe_a.cpp
					ut/ut_array_frequency_rand.cpp
					ut/ut_array_reverse_inplace.cpp
					ut/ut_find_min_in_shifted_sorted_array.cpp
					ut/ut_is_palindrome.cpp
					ut/ut_two_sum_in_array.cpp
					ut/ut_array_max_subarray.cpp
					ut/ut_peak_find.cpp
					ut/ut_permutate_probe_a.cpp
					ut/ut_partitions_of_set.cpp
					ut/ut_permutate_str.cpp
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
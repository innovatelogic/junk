cmake_minimum_required(VERSION 2.8)

project(junk_Tests)

set(JUNK ${PROJECT_NAME} )

add_definitions(-DUNICODE -D_UNICODE)
add_definitions(-DLIB_COMPILE)
#add_definitions(-DGTEST_LINKED_AS_SHARED_LIBRARY)

include_directories(${CMAKE_SOURCE_DIR}/utils/googletest/googletest/include)
include_directories(${CMAKE_SOURCE_DIR}/utils/googletest/googlemock/include)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src_cpp)
include_directories(${CMAKE_SOURCE_DIR}/src_bits)
include_directories(${CMAKE_SOURCE_DIR}/src_list)
include_directories(${CMAKE_SOURCE_DIR}/src_arr)
include_directories(${CMAKE_SOURCE_DIR}/src_bst)
include_directories(${CMAKE_SOURCE_DIR}/src_dp)
include_directories(${CMAKE_SOURCE_DIR}/src_str)
include_directories(${CMAKE_SOURCE_DIR}/src_graph)

set(SOURCE 
	oembase.h
	defexport.h
	custom_stack.h
    inner_template_class.h
	inner_template_class.ipp	
	permutations_array.h
	permutate_probe_a.h
	file.cpp
	heap.h
	heap_chart.h
	heap_sort_probe_a.h
	heap_min_probe_a.h
	find_min_in_shifted_sorted_array.h
	kevin_beakon_steps.h
	find_max_path_in_tree.h
	two_sum_in_array.h
	hash_table.h
	rotate_list_kth_element.h
	combinations.h
	subsets_in_string.h
	subsets_str_sum_probe_a.h
	telephone_numbers.h
	telephone_numbers_nonreq.h
	step_ladder.h
	get_all_split_strings.h
	is_palindrome.h
	queue_probe_a.h
	queue_probe_b.h
	junk.h
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

	set( PROJECT_NAME ${PROJECT_NAME} )
	set( PROJECT_TEST_NAME unittest_${PROJECT_NAME} )
	string( TOUPPER ${PROJECT_NAME} PROJECT_NAME_U )

	add_executable( ${PROJECT_TEST_NAME} 
					ut/ut_test.cpp
					ut/ut_array_max_subarray.cpp
					ut/ut_linearize.cpp
					ut/ut_dijkstra_probe_a.cpp
					ut/ut_peak_find.cpp
					ut/ut_heap.cpp
					ut/ut_heap_sort_probe_a.cpp
					ut/ut_find_min_in_shifted_sorted_array.cpp
					ut/ut_graph_bfs_search.cpp
					ut/ut_is_unique_chars_in_string.cpp
					ut/ut_string_convert_probe_a.cpp
					ut/ut_string_bin_frac_to_dec.cpp
					ut/ut_matrix_rotation.cpp
					ut/ut_kevin_beakon_steps.cpp
					ut/ut_find_max_path_in_tree.cpp
					ut/ut_list_find_duplicates.cpp
					ut/ut_list_to_int.cpp
					ut/ut_list_is_palindrome.cpp
					ut/ut_list_circular_find_start_loop.cpp
					ut/ut_permutate_str.cpp
					ut/ut_permutate_probe_a.cpp
					ut/ut_cpp_const_call.cpp
					ut/ut_static_global_local_init.cpp
					ut/ut_list_initializer.cpp
					ut/ut_rvalue_instantiate.cpp
					ut/ut_is_signed_char.cpp
					ut/ut_explicit_class_int.cpp
					ut/ut_two_sum_in_array.cpp
					ut/ut_numeric_limits_0xf.cpp
					ut/ut_static_construct_exeption.cpp
					ut/ut_rvalue_function_call.cpp
					ut/ut_hash_table.cpp
					ut/ut_heap_chart.cpp
					ut/ut_rotate_list_kth_element.cpp
					ut/ut_combinations.cpp
					ut/ut_partitions_of_set.cpp
					ut/ut_telephone_number.cpp
					ut/ut_egg_drop.cpp
					ut/ut_step_ladder.cpp
					ut/ut_get_all_split_strings.cpp
					ut/ut_is_palindrome.cpp
					ut/ut_list_c_probe_a.cpp
					ut/ut_list_cpp_probe_a.cpp
					ut/ut_list_cpp_probe_b.cpp
					ut/ut_list_cpp_probe_c.cpp
					ut/ut_heap_min_probe_a.cpp
					ut/ut_subsets_str_sum_probe_a.cpp
					ut/ut_queue_probe_a.cpp
					ut/ut_queue_probe_b.cpp
					ut/main.cpp
					)

	set(LIBRARIES
		${JUNK}
		${GRAPH}
		str_lib
		${GTEST_BOTH_LIBRARIES}
		${GMOCK_BOTH_LIBRARIES})
	
	target_link_libraries(${PROJECT_TEST_NAME} ${LIBRARIES})

	add_definitions(-DUSE_MOCK)

	set_target_properties(${PROJECT_TEST_NAME} PROPERTIES FOLDER "UT" )

	set_target_properties(${PROJECT_TEST_NAME} PROPERTIES
						RUNTIME_OUTPUT_DIRECTORY_DEBUG ${G_BIN_DIR}
						LIBRARY_OUTPUT_DIRECTORY_DEBUG ${G_BIN_DIR}
						RUNTIME_OUTPUT_DIRECTORY_RELEASE ${G_BIN_DIR}
						LIBRARY_OUTPUT_DIRECTORY_RELEASE ${G_BIN_DIR}
						)

#endif( ${ENABLE_TESTING} )					
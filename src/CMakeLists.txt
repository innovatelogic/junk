cmake_minimum_required(VERSION 2.8)

project(junk_Tests)

add_definitions(-DUNICODE -D_UNICODE)
add_definitions(-DLIB_COMPILE)
#add_definitions(-DGTEST_LINKED_AS_SHARED_LIBRARY)

include_directories(${CMAKE_SOURCE_DIR}/utils/googletest/googletest/include)
include_directories(${CMAKE_SOURCE_DIR}/utils/googletest/googlemock/include)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src_arr)
include_directories(${CMAKE_SOURCE_DIR}/src_bst)
include_directories(${CMAKE_SOURCE_DIR}/src_dp)
include_directories(${CMAKE_SOURCE_DIR}/src_str)
include_directories(${CMAKE_SOURCE_DIR}/src_graph)

set(SOURCE 
	oembase.h
	defexport.h
	array_frequency_rand.h
	array_combinations_probe_a.h
	btree_is_subtree_probe_a.h
	btree_all_path_sum_probe_a.h
	custom_list.h
	custom_stack.h
	find_list_nth_from_end.h
	list_head_tail.h
	list_linearize.h
	circular_list.h
    inner_template_class.h
	inner_template_class.ipp	
	permutations_array.h
	permutate_probe_a.h
	smart_ptr.h
	junk.h
	file.cpp
	merge_sort.h
	heap.h
	heap_chart.h
	heap_sort_probe_a.h
	heap_min_probe_a.h
	find_min_in_shifted_sorted_array.h
	compare_binary_hex_digit.h
	compare_binary_hex_digit.cpp
	is_unique_chars_in_string.h
	is_unique_chars_in_string.cpp
	strings.h
	strings.cpp
	matrix_rotation.h
	kevin_beakon_steps.h
	find_max_path_in_tree.h
	list_find_duplicates.h
	list_delete_nth_element.h
	list_rearrange_by_kth_element.h
	list_is_palindrome.h
	list_to_int.h
	list_circular_find_start_loop.h
	permutate.h
	stack.h
	stack_probe_a.h
	stack_min_track.h
	set_of_stacks.h
	hanoi_tower.h
	hanoi_tower.cpp
	two_stack_queue.h
	stack_sort.h
	animal_shelter.h
	binary_basic_operations.h
	binary_basic_operations.cpp
	binary_float.h
	binary_float.cpp
	sort_selection_rec.h
	sort_selection_rec.cpp
	sort_selection.h
	sort_selection.cpp
	sort_selection_stable.h
	sort_selection_stable.cpp
	sort_qsort.h
	sort_qsort.cpp
	sort_insertion.h
	sort_insertion_probe_b.h
	sort_merge.h
	merge_sort_probe_a.h
	sort_insertion_probe_a.h
	sort_selection_probe_a.h
	sort_merge_probe_b.h
	sort_merge_probe_c.h
	two_sum_in_array.h
	hash_table.h
	rotate_list_kth_element.h
	combinations.h
	subsets_in_string.h
	subsets_str_sum_probe_a.h
	telephone_numbers.h
	telephone_numbers_nonreq.h
	step_ladder.h
	egg_drop.h
	get_all_split_strings.h
	tree_is_balanced.h
	tree_traverse.h
	array_reverse_inplace.h
	is_palindrome.h
	check_braces.h
	list_c_probe_a.h
	list_cpp_probe_a.h
	list_cpp_probe_b.h
	list_cpp_probe_c.h
	qsort_probe_a.h
	qsort_probe_b.h
	sort_qsort_pobe_c.h
	queue_probe_a.h
	queue_probe_b.h
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

	set(SRC_DP
		ut/ut_fib_probe_a.cpp
	)

	set(SRC_GRAPH
		ut/ut_bellman_ford_probe_a.cpp
	)
	set(SRC_ARR
		ut/ut_rev_int.cpp
		ut/ut_array_sorted_rotation_point.cpp
		ut/ut_str_equation_analise_probe_a.cpp
	)
	add_executable( ${PROJECT_TEST_NAME} 
					ut/ut_test.cpp
					ut/ut_array_frequency_rand.cpp
					ut/ut_array_combinations_probe_a.cpp
					ut/ut_array_binary_search_probe_a.cpp
					ut/ut_array_max_subarray.cpp
					ut/ut_btree_is_subtree_probe_a.cpp
					ut/ut_btree_all_path_sum_probe_a.cpp
					ut/ut_linearize.cpp
					ut/ut_circular_list.cpp
					ut/ut_dijkstra_probe_a.cpp
					ut/ut_binary_tree_traverse.cpp
					ut/ut_peak_find.cpp
					ut/ut_swap_sort.cpp
					ut/ut_merge_sort.cpp
					ut/ut_heap.cpp
					ut/ut_heap_sort_probe_a.cpp
					ut/ut_find_min_in_shifted_sorted_array.cpp
					ut/ut_graph_bfs_search.cpp
					ut/ut_compare_binary_hex_digit.cpp
					ut/ut_is_unique_chars_in_string.cpp
					ut/ut_strings.cpp
					ut/ut_string_convert_probe_a.cpp
					ut/ut_string_bin_frac_to_dec.cpp
					ut/ut_matrix_rotation.cpp
					ut/ut_smart_ptr.cpp
					ut/ut_kevin_beakon_steps.cpp
					ut/ut_find_max_path_in_tree.cpp
					ut/ut_list_find_duplicates.cpp
					ut/ut_list_to_int.cpp
					ut/ut_list_is_palindrome.cpp
					ut/ut_list_circular_find_start_loop.cpp
					ut/ut_permutate_str.cpp
					ut/ut_permutate_probe_a.cpp
					ut/ut_stack.cpp
					ut/ut_stack_probe_a.cpp
					ut/ut_stack_min_track.cpp
					ut/ut_set_of_stacks.cpp
					ut/ut_hanoi_tower.cpp
					ut/ut_two_stack_queue.cpp
					ut/ut_stack_sort.cpp
					ut/ut_animal_shelter.cpp
					ut/ut_binary_basic_operations.cpp
					ut/ut_binary_float.cpp
					ut/ut_sort_selection_rec.cpp
					ut/ut_sort_selection.cpp
					ut/ut_sort_selection_stable.cpp
					ut/ut_sort_qsort.cpp
					ut/ut_sort_insertion_probe_a.cpp
					ut/ut_cpp_const_call.cpp
					ut/ut_static_global_local_init.cpp
					ut/ut_list_initializer.cpp
					ut/ut_rvalue_instantiate.cpp
					ut/ut_is_signed_char.cpp
					ut/ut_explicit_class_int.cpp
					ut/ut_two_sum_in_array.cpp
					ut/ut_numeric_limits_0xf.cpp
					ut/ut_static_construct_exeption.cpp
					ut/ut_type_traits_is_same.cpp
					ut/ut_rvalue_function_call.cpp
					ut/ut_sort_insertion.cpp
					ut/ut_sort_merge.cpp
					ut/ut_hash_table.cpp
					ut/ut_heap_chart.cpp
					ut/ut_rotate_list_kth_element.cpp
					ut/ut_combinations.cpp
					ut/ut_partitions_of_set.cpp
					ut/ut_telephone_number.cpp
					ut/ut_egg_drop.cpp
					ut/ut_step_ladder.cpp
					ut/ut_get_all_split_strings.cpp
					ut/ut_tree_is_balanced.cpp
					ut/ut_tree_traverse.cpp
					ut/ut_array_reverse_inplace.cpp
					ut/ut_is_palindrome.cpp
					ut/ut_braces_check.cpp
					ut/ut_bst.cpp
					ut/ut_bst_probe_b.cpp
					ut/ut_bst_probe_c.cpp
					ut/ut_bst_probe_e.cpp
					ut/ut_bst_tree_probe_d.cpp
					ut/ut_bst_tree_find_max_distinct_path_probe_e.cpp
					ut/ut_bst_tree_get_max_width_probe_a.cpp
					ut/ut_bst_build_level_order_list_probe_f.cpp
					ut/ut_bst_find_next_successor.cpp
					ut/ut_list_c_probe_a.cpp
					ut/ut_list_cpp_probe_a.cpp
					ut/ut_list_cpp_probe_b.cpp
					ut/ut_list_cpp_probe_c.cpp
					ut/ut_heap_min_probe_a.cpp
					ut/ut_qsort_probe_a.cpp
					ut/ut_qsort_probe_b.cpp
					ut/ut_merge_sort_probe_a.cpp
					ut/ut_bst_tree_check_bst_probe_f.cpp
					ut/ut_subsets_str_sum_probe_a.cpp
					ut/ut_sort_insertion_probe_b.cpp
					ut/ut_sort_selection_probe_a.cpp
					ut/ut_merge_sort_probe_b.cpp
					ut/ut_sort_merge_probe_c.cpp
					ut/ut_sort_qsort_probe_c.cpp
					ut/ut_queue_probe_a.cpp
					ut/ut_queue_probe_b.cpp
					ut/main.cpp
					${SRC_ARR}
					${SRC_DP}
					${SRC_GRAPH}
					)


	
	target_link_libraries(${PROJECT_TEST_NAME} ${PROJECT_NAME} ${ARR} ${BST} ${STR} ${GRAPH} ${GTEST_BOTH_LIBRARIES} ${GMOCK_BOTH_LIBRARIES})

	add_definitions(-DUSE_MOCK)

	set_target_properties(${PROJECT_TEST_NAME} PROPERTIES FOLDER "UT" )

	set_target_properties(${PROJECT_TEST_NAME} PROPERTIES
						RUNTIME_OUTPUT_DIRECTORY_DEBUG ${G_BIN_DIR}
						LIBRARY_OUTPUT_DIRECTORY_DEBUG ${G_BIN_DIR}
						RUNTIME_OUTPUT_DIRECTORY_RELEASE ${G_BIN_DIR}
						LIBRARY_OUTPUT_DIRECTORY_RELEASE ${G_BIN_DIR}
						)

#endif( ${ENABLE_TESTING} )					
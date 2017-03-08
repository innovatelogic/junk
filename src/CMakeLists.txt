cmake_minimum_required(VERSION 2.8)

project(junk_Tests)

add_definitions(-DUNICODE -D_UNICODE)
add_definitions(-DLIB_COMPILE)
#add_definitions(-DGTEST_LINKED_AS_SHARED_LIBRARY)

include_directories(${CMAKE_SOURCE_DIR}/utils/googletest/googletest/include)
include_directories(${CMAKE_SOURCE_DIR}/utils/googletest/googlemock/include)

include_directories(${CMAKE_SOURCE_DIR}/src)

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
	merge_sort.h
	heap.h
	heap_chart.h
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
	sort_merge.h
	two_sum_in_array.h
	hash_table.h
	rotate_list_kth_element.h
	combinations.h
	subsets_in_string.h
	telephone_numbers.h
	telephone_numbers_nonreq.h
	step_ladder.h
	egg_drop.h
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
					ut/ut_linearize.cpp
					ut/ut_circular_list.cpp
					ut/ut_binary_tree_traverse.cpp
					ut/ut_peak_find.cpp
					ut/ut_swap_sort.cpp
					ut/ut_merge_sort.cpp
					ut/ut_heap.cpp
					ut/ut_find_min_in_shifted_sorted_array.cpp
					ut/ut_compare_binary_hex_digit.cpp
					ut/ut_is_unique_chars_in_string.cpp
					ut/ut_strings.cpp
					ut/ut_matrix_rotation.cpp
					ut/ut_smart_ptr.cpp
					ut/ut_kevin_beakon_steps.cpp
					ut/ut_find_max_path_in_tree.cpp
					ut/ut_list_find_duplicates.cpp
					ut/ut_list_to_int.cpp
					ut/ut_list_is_palindrome.cpp
					ut/ut_list_circular_find_start_loop.cpp
					ut/ut_permutate_str.cpp
					ut/ut_stack.cpp
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
					ut/main.cpp )
	
	target_link_libraries(${PROJECT_TEST_NAME} ${PROJECT_NAME} ${GTEST_BOTH_LIBRARIES} ${GMOCK_BOTH_LIBRARIES})

	add_definitions(-DUSE_MOCK)

	set_target_properties(${PROJECT_TEST_NAME} PROPERTIES FOLDER "UT" )

	set_target_properties(${PROJECT_TEST_NAME} PROPERTIES
						RUNTIME_OUTPUT_DIRECTORY_DEBUG ${G_BIN_DIR}
						LIBRARY_OUTPUT_DIRECTORY_DEBUG ${G_BIN_DIR}
						RUNTIME_OUTPUT_DIRECTORY_RELEASE ${G_BIN_DIR}
						LIBRARY_OUTPUT_DIRECTORY_RELEASE ${G_BIN_DIR}
						)

#endif( ${ENABLE_TESTING} )					
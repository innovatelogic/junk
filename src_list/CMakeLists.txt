cmake_minimum_required(VERSION 2.8)

project(list)

add_definitions(-DUNICODE -D_UNICODE)
add_definitions(-DLIB_COMPILE)
#add_definitions(-DGTEST_LINKED_AS_SHARED_LIBRARY)

set( LIST ${PROJECT_NAME} )

set(SOURCE 
	oembase.h
	defexport.h
	list_merge_sort_probe_a.h
	find_list_nth_from_end.h
	custom_list.h
	list_c_probe_a.h
	list_find_duplicates.h
	list_circular_find_start_loop.h
	list_to_int.h
	list_cpp_probe_a.h
	list_cpp_probe_b.h
	list_cpp_probe_c.h
	list_delete_nth_element.h
	list_head_tail.
	list_is_palindrome.h
	list_rearrange_by_kth_element.h
	lst.h
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
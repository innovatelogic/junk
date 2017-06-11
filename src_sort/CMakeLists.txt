cmake_minimum_required(VERSION 2.8)

project(sort_lib)

add_definitions(-DUNICODE -D_UNICODE)
add_definitions(-DSORT_LIB_COMPILE)
#add_definitions(-DGTEST_LINKED_AS_SHARED_LIBRARY)

set(SOURCE 
	oembase.h
	defexport.h
	sort_lib.h
	qsort_probe_a.h
	qsort_probe_b.h
	sort_insertion.h
	sort_insertion_probe_a.h
	sort_insertion_probe_b.h
	sort_selection_probe_a.h
	merge_sort.h
	merge_sort_probe_a.h
	sort_merge_probe_b.h
	sort_merge_probe_c.h
	swap_sort.h
	sort_selection_rec.h
	sort_selection_rec.cpp
	sort_selection.h
	sort_selection.cpp
	sort_selection_stable.h
	sort_selection_stable.cpp
	sort_qsort.h
	sort_qsort.cpp
	sort_merge.h
	sort_qsort_pobe_c.h
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
					ut/ut_qsort_probe_a.cpp
					ut/ut_qsort_probe_b.cpp
					ut/ut_sort_insertion.cpp
					ut/ut_sort_insertion_probe_a.cpp
					ut/ut_sort_insertion_probe_b.cpp
					ut/ut_sort_selection_probe_a.cpp
					ut/ut_merge_sort_probe_a.cpp
					ut/ut_merge_sort_probe_b.cpp
					ut/ut_merge_sort.cpp
					ut/ut_sort_merge_probe_c.cpp
					ut/ut_swap_sort.cpp
					ut/ut_sort_selection_rec.cpp
					ut/ut_sort_selection.cpp
					ut/ut_sort_selection_stable.cpp
					ut/ut_sort_qsort.cpp
					ut/ut_sort_qsort_probe_c.cpp
					ut/ut_sort_merge.cpp
					)

	target_link_libraries(${PROJECT_TEST_NAME}  ${PROJECT_NAME} ${GTEST_BOTH_LIBRARIES} ${GMOCK_BOTH_LIBRARIES})

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
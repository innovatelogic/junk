cmake_minimum_required(VERSION 2.8)

project(cpp)

add_definitions(-DUNICODE -D_UNICODE)
add_definitions(-DLIB_COMPILE)
#add_definitions(-DGTEST_LINKED_AS_SHARED_LIBRARY)

set( GRAPH ${PROJECT_NAME} )

set(SOURCE 
	oembase.h
	defexport.h
	is_derived_class_probe_a.h
	threadpool_probe_a.h
	segment_sphere_collision_2d.h
	tcp_read_state_machine.h
	triangle_point_2d.h
	cpp.h
	file.cpp
	inner_template_class.h
	inner_template_class.ipp
	class_inheritance.h
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
					ut/triangle_point_2d_probe_a.cpp
					ut/ut_is_derived_class.cpp
					ut/ut_threadpool_probe_a.cpp
					ut/ut_segment_sphere_collision_2d.cpp
					ut/ut_tcp_read_state_machine.cpp
					ut/ut_type_traits_is_same.cpp
					ut/ut_empty.cpp
					ut/ut_cpp_const_call.cpp
					ut/ut_explicit_class_int.cpp
					ut/ut_is_signed_char.cpp
					ut/ut_numeric_limits_0xf.cpp
					ut/ut_static_global_local_init.cpp
					ut/ut_rvalue_instantiate.cpp
					ut/ut_static_construct_exeption.cpp
					ut/ut_rvalue_function_call.cpp
					ut/ut_class_inheritance.cpp
					ut/ut_data_layout.cpp
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
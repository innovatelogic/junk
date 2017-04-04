cmake_minimum_required(VERSION 2.8)

project(graph)

add_definitions(-DUNICODE -D_UNICODE)
add_definitions(-DLIB_COMPILE)
#add_definitions(-DGTEST_LINKED_AS_SHARED_LIBRARY)

set( GRAPH ${PROJECT_NAME} )

set(SOURCE 
	oembase.h
	defexport.h
	graph.h
	bfs_search_probe_a.h
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
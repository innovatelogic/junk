cmake_minimum_required(VERSION 3.0.0)

#get_filename_component(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/Build/cmake" REALPATH)
#include(macros)

include(ExternalProject)
include(CMakeParseArguments)

#---------------------------------------------------------------------------
#googlemock	
ExternalProject_Add(googletest
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/utils/googletest
	#DOWNLOAD_COMMAND ""
	INSTALL_DIR ${CMAKE_BINARY_DIR}/..
    # cmake arguments
	
	
    CMAKE_ARGS
			#-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
				-DBUILD_GMOCK=ON
				-DBUILD_GTEST=ON
				-DGTEST_INSTALL=ON
				-DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_BINARY_DIR}/..
               #-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=${CMAKE_BINARY_DIR}/../Libs
               #-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=${CMAKE_BINARY_DIR}/../Libs
			   #-DCMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG:PATH=${CMAKE_BINARY_DIR}/../bin
			   #-DCMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE:PATH=${CMAKE_BINARY_DIR}/../bin
			   -DCMAKE_DEBUG_POSTFIX=_d
			   -DBUILD_SHARED_LIBS=ON
			   -DGTEST_CREATE_SHARED_LIBRARY=1
			${ARGS_CMAKE_ARGS}# Disable install step
	PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
    
	#BUILD_COMMAND     ""
	#INSTALL_COMMAND   ""
	TEST_COMMAND      ""

    # Wrap download, configure and build steps in a script to log output
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON
    )	

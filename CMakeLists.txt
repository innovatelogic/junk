cmake_minimum_required(VERSION 3.3...3.5 FATAL_ERROR)

#include(config/cmake/modules/Findclang.cmake)
#include(config/cmake/modules/platform.cmake)
#include(config/cmake/modules/colours.cmake)

set( LIB_VERSION_MAJOR 0 )
set( LIB_VERSION_MINOR 1 )
set( LIB_VERSION_PATCH 0 )

enable_testing()

project(junk VERSION "${LIB_VERSION_MAJOR}.${LIB_VERSION_MINOR}.${LIB_VERSION_PATCH}")

#set(CMAKE_C_COMPILER "/opt/homebrew/opt/llvm/bin/clang")
#set(CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm/bin/clang++")

#set(CMAKE_OSX_ARCHITECTURES "arm64")
#set(LLVM_DIR "/opt/homebrew/opt/llvm/lib/cmake/llvm")
#set(Clang_DIR "/opt/homebrew/opt/llvm/lib/cmake/clang")

find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

if (LLVM_FOUND)
    include_directories(${LLVM_INCLUDE_DIRS})
    add_definitions(${LLVM_DEFINITIONS})
    llvm_map_components_to_libnames(llvm_libs support core irreader)
    # Link your target to llvm_libs as needed
endif()

#SET(CMAKE_C_COMPILER ${LLVM_INSTALL_PREFIX}/bin/clang)

set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

foreach(path IN LISTS CMAKE_MODULE_PATH)
    message("Before Path: ${path}")
endforeach()

#set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${PROJECT_DIR}/src_cpp/config/cmake/modules/")
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/config/cmake/modules/)

foreach(path IN LISTS CMAKE_MODULE_PATH)
    message("After Path: ${path}")
endforeach()

#include(${CMAKE_CURRENT_SOURCE_DIR}/src_cpp/config/cmake/macros.cmake)

set(ENABLE_TESTING TRUE)

enable_language(C)
enable_language(CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS TRUE)

set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}")

message(STATUS "${BoldCyan}PROJECT:${ColourReset} ${PROJECT_NAME}")
message(STATUS "CMAKE_SYSTEM_PROCESSOR: " ${CMAKE_SYSTEM_PROCESSOR})

include(ProcessorCount)
ProcessorCount(N_PROC)

message("number of processors: "  ${N_PROC})

if(NOT N EQUAL 0)
    MATH(EXPR N_BUILD_PROC "${N_PROC}/2")

  set(CTEST_BUILD_FLAGS -j${N_BUILD_PROC})
  set(ctest_test_args ${ctest_test_args} PARALLEL_LEVEL ${N_BUILD_PROC})
  set(CMAKE_MAKE_PROGRAM "${CMAKE_MAKE_PROGRAM} -j ${N_BUILD_PROC}")  
endif()
message("cmake make program" ${CMAKE_MAKE_PROGRAM})

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(warnings "-Wall -Wextra -Werror")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(warnings "/W4 /EHa /MP /wd4996") #/WX
    set(add_debug_flags "/ZI /Od /fp:fast" CACHE STRING "" FORCE)
    set(add_release_flags "/Zi /Ox /Ob2 /Oi /Ot /Oy /GT /fp:fast" CACHE STRING "" FORCE)

    # avx compile time var
    if("${AVX}" STREQUAL "1")
        string(APPEND add_release_flags "/arch:AVX")
    elseif("${AVX}" STREQUAL "2")
        string(APPEND add_release_flags " /arch:AVX2")
    elseif("${AVX}" STREQUAL "3")
        string(APPEND add_release_flags " /arch:AVX2") # because msvc doesn't support avx 512 at the moment
    endif()    
    
    set(add_debug_linker_flags "/LTCG /DEBUG:FASTLINK /OPT:NOLBR")
    set(add_release_linker_flags "/LTCG /DEBUG:FASTLINK /OPT:NOLBR /OPT:REF") # /DEBUG:FULL for outside companies builds
endif()

if (NOT CONFIGURED_ONCE)
    set(CMAKE_CXX_FLAGS "${warnings}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
    set(CMAKE_C_FLAGS "${warnings}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)

    SET(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} ${add_release_linker_flags}"
        CACHE STRING "Flags used by the linker during Release build type." FORCE)
    SET(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} ${add_debug_linker_flags}"
        CACHE STRING "Flags used by the linker during Debug build type." FORCE)
    set(CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS_RELEASE} ${add_release_flags}"
        CACHE STRING "Flags used by the compiler during Release build type." FORCE)
    set(CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS_DEBUG} ${add_debug_flags}"
        CACHE STRING "Flags used by the compiler during Debug build type." FORCE)
endif()

message(STATUS "CMAKE_CXX_COMPILER_ID:" ${CMAKE_CXX_COMPILER_ID})
message(STATUS "CMAKE_GENERATOR_PLATFORM:" ${CMAKE_GENERATOR_PLATFORM})
message(STATUS "CMAKE_SYSTEM_NAME:" ${CMAKE_SYSTEM_NAME})

add_definitions(-DUNICODE -D_UNICODE)

if(NOT APPLE)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

if(CMAKE_COMPILER_IS_GNUCC)
  set(CMAKE_INCLUDE_SYSTEM_FLAG_C "-isystem")
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w -Wall -ldl -std=c++23") # -Ofast 
set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS}") #
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
#set(CMAKE_POSITION_INDEPENDENT_CODE ON)
#set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Ofast -w -Wall -Wno-sign-compare -flax-vector-conversions -fpermissive -msse4.1 -Wno-unused-parameter -Wno-sign-compare -Wno-unused-function -Wno-unused-variable -Wno-error=unused-variable -Wno-error=unused-parameter -Wno-error=sign-compare -Wno-error=pointer-sign")
#set(CMAKE_CXX_LINK_EXECUTABLE "{$CMAKE_CXX_LINK_EXECUTABLE} -R")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(G_BIN_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/bin)
set(G_LIB_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/lib)

message( STATUS "CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR})
message( STATUS "EXECUTABLE_OUTPUT_PATH:" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
message( STATUS "CMAKE_COMMAND:" ${CMAKE_COMMAND} )
message( STATUS "CMAKE_BUILD_TYPE:" ${CMAKE_BUILD_TYPE} )
message( STATUS "CMAKE_CXX_FLAGS_RELEASE:" ${CMAKE_CXX_FLAGS_RELEASE}) 
message( STATUS "CMAKE_SOURCE_DIR:" ${CMAKE_SOURCE_DIR})
message( STATUS "CMAKE_BINARY_DIR:" ${CMAKE_BINARY_DIR})
message( STATUS "PROJECT_DIR:" ${PROJECT_DIR})
message( STATUS "${BoldCyan}CMAKE_INSTALL_PREFIX:${ColourReset}" ${CMAKE_INSTALL_PREFIX})
message( STATUS "CMAKE_PREFIX_PATH:" ${CMAKE_PREFIX_PATH})
message( STATUS "G_BIN_DIR: " ${G_BIN_DIR})
message( STATUS "COMPILER: " ${CMAKE_CXX_COMPILER_ID})
message( STATUS "CMAKE_MODULE_PATH:" ${CMAKE_MODULE_PATH})

file(MAKE_DIRECTORY ${G_BIN_DIR})
file(MAKE_DIRECTORY ${G_LIB_DIR})

set(BUILD_INCLUDE_DIR ${G_BIN_DIR}/../include/)
file(MAKE_DIRECTORY ${BUILD_INCLUDE_DIR})

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

set(PATH_CORE_UT_DATA ${CMAKE_CURRENT_SOURCE_DIR}/testdata/)
set(PATH_CORE_UT_OUT ${G_BIN_DIR}/../core_tests_out/)
file(MAKE_DIRECTORY ${PATH_CORE_UT_OUT})

#configure_file("${CMAKE_CURRENT_SOURCE_DIR}/src_cpp/config/headers/ut_core_config.h.in" "${BUILD_INCLUDE_DIR}/ut_core_config.h")

set(CMAKE_EXTRA_INCLUDES ${G_BIN_DIR}/../include/)

include_directories(${PROJECT_SOURCE_DIR}/base)

# UT section
find_package(GTest REQUIRED)
find_package(Seastar REQUIRED)
#find_package(benchmark REQUIRED)

message( STATUS "GTEST_ROOT:" ${GTEST_ROOT})
message( STATUS "GTEST_LIBRARIES:" ${GTEST_LIBRARIES})

#message(STATUS "benchmark_INCLUDE_DIRS: ${benchmark_INCLUDE_DIRS}")
#message(STATUS "benchmark_LIBRARIES: ${benchmark_LIBRARIES}")

set(GTEST_INCLUDE_DIRS ${GTEST_PATH}/include)

set(ADD_CXX_FLAGS_DEBUG "-DDEBUG -g")
set(ADD_CXX_FLAGS_REL "-DRELEASE -DNDEBUG")

#SET (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${ADD_CXX_FLAGS_DEBUG}" CACHE STRING "cxx d compile flags" FORCE)
#SET (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${ADD_CXX_FLAGS_REL}" CACHE STRING "cxx r compile flags" FORCE)

add_subdirectory(test_cases)
add_subdirectory(demo_seastar)

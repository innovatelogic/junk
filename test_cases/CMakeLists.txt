
set(ENABLE_TESTING TRUE)

add_definitions(-DCORE_LIB_COMPILE)

#file(MAKE_DIRECTORY ${CORE_INCLUDE_DIR})

if (CMAKE_INSTALL_PREFIX MATCHES "^/usr/local")
    set(CMAKE_INSTALL_PREFIX ${G_BIN_DIR} CACHE PATH "Default installation directory" FORCE)
    message(STATUS "${BoldYellow}CMAKE_INSTALL_PREFIX not set. Use default value:${Reset} ${CMAKE_INSTALL_PREFIX}")
endif()

message( STATUS "${Yellow}CMAKE_INSTALL_PREFIX:${ColourReset}" ${CMAKE_INSTALL_PREFIX} )

set(PATH_BIN_INSTALL ${CMAKE_INSTALL_PREFIX}/)

message( STATUS "${Yellow}PATH_BIN_INSTALL:${ColourReset}" ${PATH_BIN_INSTALL} )

#set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};/usr/local/lib/cmake/opencv4/")
#set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};/usr/local/lib/aarch64-linux-gnu/cmake/opencv4/")
#set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};/usr/lib/aarch64-linux-gnu/cmake/opencv4/")
#set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};/usr/lib/x86_64-linux-gnu/cmake/opencv4/")

#find_package(OpenCV REQUIRED)
#message(STATUS "OpenCV_INCLUDE_DIRS : " ${OpenCV_INCLUDE_DIRS})
#message(STATUS "OpenCV_LIBS : " ${OpenCV_LIBS})

#find_package(LLVM REQUIRED CONFIG)
#find_package(Clang REQUIRED CONFIG)

set(LLVM_LINK_COMPONENTS
  Support
  )

find_package(Boost REQUIRED COMPONENTS date_time system filesystem)
message(STATUS "BOOST Found : " ${Boost_FOUND})
message(STATUS "BOOST_INCLUDE_DIRS : " ${Boost_INCLUDE_DIRS})
message(STATUS "BOOST_LIBRARIES : " ${Boost_LIBRARIES})

add_definitions(-DBOOST_BIND_GLOBAL_PLACEHOLDERS)

include_directories(${Boost_INCLUDE_DIRS})

#set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};/usr/share/cmake/geographiclib")
#find_package(GeographicLib REQUIRED)

set(LIBYAML_INCLUDE_DIR "${PROJECT_DIR}/third_party/yaml-cpp/include")


#set(base_LIBRARY_DIRS "")
#foreach(path IN LISTS CMAKE_MODULE_PATH)
#    list(APPEND base_LIBRARY_DIRS "${path}")
#endforeach()
#list(APPEND base_LIBRARY_DIRS "${CMAKE_SOURCE_DIR}/../base/build/bin/")


#find_library(base_LIBRARY NAMES base HINTS ${G_BIN_DIR} REQUIRED)
#find_library(libyaml_LIBRARY NAMES libyaml-cpp.a libyaml-cppd.a HINTS "${G_BIN_DIR}/../yaml-cpp" REQUIRED)

include_directories(${BUILD_INCLUDE_DIR})

include_directories(src)

file(GLOB_RECURSE SRC_INCLUDES
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
    )

file(GLOB_RECURSE SRC_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.ipp"
    )

file(GLOB_RECURSE SRC_BIND
    "${CMAKE_CURRENT_SOURCE_DIR}/bind/*.cpp"
    )

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

#add_clang_executable(${PROJECT_NAME} ${SRC_INCLUDES} ${SRC_FILES} ${SRC_BIND})

# Target creation section...
add_library(${PROJECT_NAME} SHARED ${SRC_INCLUDES} ${SRC_FILES} ${SRC_BIND})

target_include_directories(${PROJECT_NAME} PRIVATE 
${PROJECT_DIR}/third_party
#${PROJECT_DIR}/third_party/Eigen
${GeographicLib_INCLUDE_DIRS}
#${onnxruntime_INCLUDE_DIRS}
${Python3_INCLUDE_DIRS}
#${OpenCV_INCLUDE_DIRS}
${GEOGRAPHYCLIB_INCLUDE_DIR}
${LIBYAML_INCLUDE_DIR}
llvm
clangAST
clangBasic
clangFrontend
clangSerialization
clangTooling
)

#target_link_directories(${PROJECT_NAME} PUBLIC ${G_BIN_DIR}/../base/bin)
#target_link_libraries(${PROJECT_NAME} base)


target_link_libraries(${PROJECT_NAME} 
#${Python3_LIBRARIES}
#${OpenCV_LIBS}
#${libyaml_LIBRARY}
#${GeographicLib_LIBRARIES}
#${onnxruntime_LIBRARIES}
${Boost_LIBRARIES}
Seastar::seastar
LLVM
pthread
dl
)

set_target_properties(${PROJECT_NAME} PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${G_BIN_DIR}
                      LIBRARY_OUTPUT_DIRECTORY ${G_BIN_DIR}
                      ARCHIVE_OUTPUT_DIRECTORY ${G_BIN_DIR}
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE ${G_BIN_DIR}
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG ${G_BIN_DIR})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
#set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

if (LINUX)
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-Wl,-rpath,./")
elseif(APPLE)
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES SUFFIX ".so")
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
endif()

add_subdirectory(ut)

if (CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
add_subdirectory(ut_perf)
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION .)
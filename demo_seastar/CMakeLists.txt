cmake_minimum_required(VERSION 3.22.0 FATAL_ERROR)

project(demo_seastar)

add_definitions(-DBOOST_BIND_GLOBAL_PLACEHOLDERS)

add_executable(${PROJECT_NAME} driver.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${G_BIN_DIR}
                      LIBRARY_OUTPUT_DIRECTORY ${G_BIN_DIR}
                      ARCHIVE_OUTPUT_DIRECTORY ${G_BIN_DIR}
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE ${G_BIN_DIR}
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG ${G_BIN_DIR})

target_link_libraries(${PROJECT_NAME} Seastar::seastar ${Boost_LIBRARIES})

install(TARGETS ${PROJECT_NAME} DESTINATION .)
cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME "words_learning_server")
set(TESTS_NAME "tests_server")
set(CMAKE_CXX_STANDARD 17)

project(${PROJECT_NAME})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")
file(GLOB_RECURSE HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "src/*.hh")

file(GLOB_RECURSE TEST_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "test/*.cpp" "src/ConnectionHandler/*.cpp" "src/DatabaseHandlers/*.cpp" "src/RequestHandler/*.cpp")
file(GLOB_RECURSE TEST_HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "test/*.hh" "src/ConnectionHandler/*.hh" "src/DatabaseHandlers/*.hh" "src/RequestHandler/*.hh")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
add_executable(${TESTS_NAME} ${TEST_SOURCES} ${TEST_HEADERS})

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
target_link_libraries(${TESTS_NAME} ${CONAN_LIBS})
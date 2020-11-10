cmake_minimum_required(VERSION 3.10)
project(Production_line_simulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# include libs
## CPP-Argument-Parser
add_subdirectory(lib/CPP-Argument-Parser)
include_directories(lib/CPP-Argument-Parser/include)
## Simplelogging
add_subdirectory(lib/SimpleLogging)
include_directories(lib/SimpleLogging/include)

add_subdirectory(src)

add_executable(Production_line_simulator ${src_files}  src/main.cpp )

target_link_libraries(Production_line_simulator  CPPArgvParsLib SimpleLoggingLib)
#message( "src: " ${src_files} )
find_package(GTest)
if (GTest_FOUND)
    message(" -- gtest found at " ${GTEST_INCLUDE_DIRS})
    include_directories(${GTEST_INCLUDE_DIRS})
    add_subdirectory(tests)
    add_executable(selftest ${src_files} ${test_files})
    target_link_libraries(selftest ${GTEST_LIBRARIES} pthread CPPArgvParsLib SimpleLoggingLib)

else ()
    message(WARNING "to enable self test install gtest")
endif ()



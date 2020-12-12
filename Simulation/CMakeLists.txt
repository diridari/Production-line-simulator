cmake_minimum_required(VERSION 3.10)
project(Production_line_simulator)
message("proj located at: " ${CMAKE_SOURCE_DIR})
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

find_path(ZeroMQ_INCLUDE_DIR
        NAMES zmq.hpp
        PATHS ${CMAKE_SOURCE_DIR}\\lib\\zeromq
        REQUIRED
        )

## use the hint from about to find the location of libzmq
find_library(ZeroMQ_LIBRARY
        NAMES zmq libzmq 0mq zeromq libzmq-v141-mt-s-4_3.lib
        PATHS ${CMAKE_SOURCE_DIR}\\lib\\zeromq
        HINTS ${CMAKE_SOURCE_DIR}\\lib\\zeromq
        REQUIRED
        )


include_directories(lib/zeromq)
message("zeroMQ found at: " ${ZeroMQ_LIBRARY})
    message("Build for testing")
    find_package(GTest)

    message("Build for simulation")
    # QT 5
    find_package(Qt5Widgets)
    if(Qt5Widgets_FOUND)
        message("found QT Lib at" ${Qt5Widgets_INCLUDE_DIRS})
        set(CMAKE_AUTOMOC ON)
        set(CMAKE_AUTOUIC ON)
        set(CMAKE_AUTORCC ON)
        add_executable(Production_line_simulator ${src_files}  ${src_gui} src/main.cpp )
        target_link_libraries(Production_line_simulator pthread CPPArgvParsLib SimpleLoggingLib  Qt5::Widgets ${ZeroMQ_LIBRARY} )

        #message( "src: " ${src_files} )
    endif()

find_package(GTest)
if (GTest_FOUND)
    message(" -- gtest found at " ${GTEST_INCLUDE_DIRS})
    include_directories(${GTEST_INCLUDE_DIRS})
    add_subdirectory(tests)
    add_executable(selftest ${src_files} ${test_files})
    target_link_libraries(selftest ${GTEST_LIBRARIES} ${ZeroMQ_LIBRARY}  pthread CPPArgvParsLib SimpleLoggingLib)
    add_compile_definitions(selftest PRIVATE selfTest=1)

else ()
    message(WARNING "to enable self test install gtest")
endif ()

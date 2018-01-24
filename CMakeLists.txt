cmake_minimum_required(VERSION 2.6)
project (serializer)

#define Sources and headers
set (SERIAL_SRC   src/serial.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg -O3")


#Check if Boost is available on system
find_package(Boost 1.40.0 COMPONENTS serialization)
if (NOT ${Boost_FOUND})
    message( FATAL_ERROR "libboost-all-dev was not found : ${Boost_NOT_FOUND_MESSAGE}" )
else ()
	include_directories(${Boost_INCLUDE_DIRS})
endif(NOT ${Boost_FOUND})

#compiling step
add_executable(serializer ${SERIAL_SRC} ${Boost_INCLUDE_DIRS})

#link step
target_link_libraries(serializer ${Boost_LIBRARIES} -lpthread -lrt)

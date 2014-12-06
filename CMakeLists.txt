cmake_minimum_required ( VERSION 2.6 )
project ( GAMELOGIC )
include ( ExternalProject )

# Output compiled files in root directory
set ( LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/.. )
set ( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/.. )

# Use C++11 standard
if ( CMAKE_CXX_COMPILER MATCHES ".*clang" )
    set ( CMAKE_COMPILER_IS_CLANG )
endif ( CMAKE_CXX_COMPILER MATCHES ".*clang" )

if ( CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANG )
    list ( APPEND CMAKE_CXX_FLAGS "-std=c++11" )
endif ( CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANG )

# Add compiler options
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall" )
set ( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O1" )

# Store external dependencies in build/external/
set ( EXTERNALS_PREFIX ${PROJECT_BINARY_DIR}/external CACHE FILEPATH "Installation Path" )
set ( EXTERNALS_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNALS_PREFIX} )

# Add the source directories
include_directories ( ${CMAKE_SOURCE_DIR}/inc )
add_subdirectory ( ${CMAKE_SOURCE_DIR}/src )

set ( COMPILE_TESTS OFF CACHE COMPILE_TESTS "Compile test_executable" )

# Add the tests subdirectory
if ( COMPILE_TESTS )
    add_subdirectory ( ${CMAKE_SOURCE_DIR}/tests )
endif ( COMPILE_TESTS )

file ( GLOB_RECURSE GAMELOGIC_HEADERS ${CMAKE_SOURCE_DIR}/inc *.(h|hpp) )
install ( FILES ${GAMELOGIC_HEADERS} DESTINATION include )

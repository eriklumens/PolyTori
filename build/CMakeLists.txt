cmake_minimum_required(VERSION 2.8)

PROJECT(PolyTori)

#-- Where to search for the PolyTori lib
LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/..bin/)
#-- Where to output the PolyTori lib

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
#-- Display warnings and compile with debug information and optimize
SET(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -Wall -g -O3")

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

IF(APPLE)
    SET(
        LIB_LIBRARIES
        "GLEW"
        #"glfw"
        ) 
    SET(
        CMAKE_CXX_LINK_FLAGS
        "-Wall -framework OpenGL"
        )
ELSE()
    SET(
        LIB_LIBRARIES
        "GL"
        "GLEW"
        #"glfw"
        )
ENDIF()


SET(LIB_NAME "PolyTori")

SET(
    LIB_SOURCES
    
    "../src/lattice.cpp"
    "../src/polytope.cpp"
    "../src/line.cpp"
    "../src/cone.cpp"
    "../src/fan.cpp"
                                                                                                                                                                                                                                                         
)

                                                                                                                                                                                                                                                    SET(
                                                                                                                                                                                                                                                            LIB_INCLUDES
                                                                                                                                                                                                                                                                "../include"
                                                                                                                                                                                                                                                                    "../ext"
                                                                                                                                                                                                                                                                        )

                                                                                                                                                                                                                                                                    ADD_DEFINITIONS(-DGLEW_STATIC)

                                                                                                                                                                                                                                                                    INCLUDE_DIRECTORIES( ${LIB_INCLUDES} )
                                                                                                                                                                                                                                                                    ADD_LIBRARY( ${LIB_NAME} STATIC ${LIB_SOURCES} )
                                                                                                                                                                                                                                                                    TARGET_LINK_LIBRARIES( ${LIB_NAME} ${LIB_LIBRARIES} )
#target_link_libraries(simple ${GLFW_LIBRARIES})
target_link_libraries(${LIB_NAME} ${GLFW_STATIC_LIBRARIES}) 

ADD_SUBDIRECTORY(../application/build ../application/build)
                                                                                                                                                                                                                                                                    #-- ADD_SUBDIRECTORY(../tools/build ../tools/build)

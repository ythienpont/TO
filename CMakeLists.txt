cmake_minimum_required(VERSION 3.5)

project(Autocorrect)

############################################################
# Set compiler flags
############################################################
set(OWN_GXX_FLAGS "-Wall -Wextra -fstack-protector-all -std=c++14")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${OWN_GXX_FLAGS} -pg -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${OWN_GXX_FLAGS}")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${OWN_GXX_FLAGS}")

############################################################
# List all sources
############################################################
set(engine_sources
    Automaton.cpp
    DFA.cpp
    ENFA.cpp
    #RE.cpp
    json.hpp
    NFA.cpp
    main.cpp RE.cpp RE.h)

############################################################
# Create an executable
############################################################
set(exe_name "Autocorrect")
add_executable( ${exe_name} ${engine_sources} )
install( TARGETS ${exe_name} DESTINATION .)

# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/clion/151/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/151/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/benjamin/CLionProjects/TO

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/benjamin/CLionProjects/TO/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/TA1_13_02.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TA1_13_02.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TA1_13_02.dir/flags.make

CMakeFiles/TA1_13_02.dir/main.cpp.o: CMakeFiles/TA1_13_02.dir/flags.make
CMakeFiles/TA1_13_02.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/benjamin/CLionProjects/TO/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TA1_13_02.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TA1_13_02.dir/main.cpp.o -c /home/benjamin/CLionProjects/TO/main.cpp

CMakeFiles/TA1_13_02.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TA1_13_02.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/benjamin/CLionProjects/TO/main.cpp > CMakeFiles/TA1_13_02.dir/main.cpp.i

CMakeFiles/TA1_13_02.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TA1_13_02.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/benjamin/CLionProjects/TO/main.cpp -o CMakeFiles/TA1_13_02.dir/main.cpp.s

CMakeFiles/TA1_13_02.dir/DFA.cpp.o: CMakeFiles/TA1_13_02.dir/flags.make
CMakeFiles/TA1_13_02.dir/DFA.cpp.o: ../DFA.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/benjamin/CLionProjects/TO/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/TA1_13_02.dir/DFA.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TA1_13_02.dir/DFA.cpp.o -c /home/benjamin/CLionProjects/TO/DFA.cpp

CMakeFiles/TA1_13_02.dir/DFA.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TA1_13_02.dir/DFA.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/benjamin/CLionProjects/TO/DFA.cpp > CMakeFiles/TA1_13_02.dir/DFA.cpp.i

CMakeFiles/TA1_13_02.dir/DFA.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TA1_13_02.dir/DFA.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/benjamin/CLionProjects/TO/DFA.cpp -o CMakeFiles/TA1_13_02.dir/DFA.cpp.s

CMakeFiles/TA1_13_02.dir/NFA.cpp.o: CMakeFiles/TA1_13_02.dir/flags.make
CMakeFiles/TA1_13_02.dir/NFA.cpp.o: ../NFA.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/benjamin/CLionProjects/TO/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/TA1_13_02.dir/NFA.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TA1_13_02.dir/NFA.cpp.o -c /home/benjamin/CLionProjects/TO/NFA.cpp

CMakeFiles/TA1_13_02.dir/NFA.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TA1_13_02.dir/NFA.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/benjamin/CLionProjects/TO/NFA.cpp > CMakeFiles/TA1_13_02.dir/NFA.cpp.i

CMakeFiles/TA1_13_02.dir/NFA.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TA1_13_02.dir/NFA.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/benjamin/CLionProjects/TO/NFA.cpp -o CMakeFiles/TA1_13_02.dir/NFA.cpp.s

# Object files for target TA1_13_02
TA1_13_02_OBJECTS = \
"CMakeFiles/TA1_13_02.dir/main.cpp.o" \
"CMakeFiles/TA1_13_02.dir/DFA.cpp.o" \
"CMakeFiles/TA1_13_02.dir/NFA.cpp.o"

# External object files for target TA1_13_02
TA1_13_02_EXTERNAL_OBJECTS =

TA1_13_02: CMakeFiles/TA1_13_02.dir/main.cpp.o
TA1_13_02: CMakeFiles/TA1_13_02.dir/DFA.cpp.o
TA1_13_02: CMakeFiles/TA1_13_02.dir/NFA.cpp.o
TA1_13_02: CMakeFiles/TA1_13_02.dir/build.make
TA1_13_02: CMakeFiles/TA1_13_02.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/benjamin/CLionProjects/TO/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable TA1_13_02"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TA1_13_02.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TA1_13_02.dir/build: TA1_13_02

.PHONY : CMakeFiles/TA1_13_02.dir/build

CMakeFiles/TA1_13_02.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TA1_13_02.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TA1_13_02.dir/clean

CMakeFiles/TA1_13_02.dir/depend:
	cd /home/benjamin/CLionProjects/TO/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/benjamin/CLionProjects/TO /home/benjamin/CLionProjects/TO /home/benjamin/CLionProjects/TO/cmake-build-debug /home/benjamin/CLionProjects/TO/cmake-build-debug /home/benjamin/CLionProjects/TO/cmake-build-debug/CMakeFiles/TA1_13_02.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TA1_13_02.dir/depend


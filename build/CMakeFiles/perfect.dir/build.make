# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/matvey/Documents/research/Caches

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/matvey/Documents/research/Caches/build

# Include any dependencies generated for this target.
include CMakeFiles/perfect.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/perfect.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/perfect.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/perfect.dir/flags.make

CMakeFiles/perfect.dir/perfect_cache/src/main.cpp.o: CMakeFiles/perfect.dir/flags.make
CMakeFiles/perfect.dir/perfect_cache/src/main.cpp.o: ../perfect_cache/src/main.cpp
CMakeFiles/perfect.dir/perfect_cache/src/main.cpp.o: CMakeFiles/perfect.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/matvey/Documents/research/Caches/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/perfect.dir/perfect_cache/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/perfect.dir/perfect_cache/src/main.cpp.o -MF CMakeFiles/perfect.dir/perfect_cache/src/main.cpp.o.d -o CMakeFiles/perfect.dir/perfect_cache/src/main.cpp.o -c /home/matvey/Documents/research/Caches/perfect_cache/src/main.cpp

CMakeFiles/perfect.dir/perfect_cache/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/perfect.dir/perfect_cache/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/matvey/Documents/research/Caches/perfect_cache/src/main.cpp > CMakeFiles/perfect.dir/perfect_cache/src/main.cpp.i

CMakeFiles/perfect.dir/perfect_cache/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/perfect.dir/perfect_cache/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/matvey/Documents/research/Caches/perfect_cache/src/main.cpp -o CMakeFiles/perfect.dir/perfect_cache/src/main.cpp.s

# Object files for target perfect
perfect_OBJECTS = \
"CMakeFiles/perfect.dir/perfect_cache/src/main.cpp.o"

# External object files for target perfect
perfect_EXTERNAL_OBJECTS =

perfect: CMakeFiles/perfect.dir/perfect_cache/src/main.cpp.o
perfect: CMakeFiles/perfect.dir/build.make
perfect: CMakeFiles/perfect.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/matvey/Documents/research/Caches/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable perfect"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/perfect.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/perfect.dir/build: perfect
.PHONY : CMakeFiles/perfect.dir/build

CMakeFiles/perfect.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/perfect.dir/cmake_clean.cmake
.PHONY : CMakeFiles/perfect.dir/clean

CMakeFiles/perfect.dir/depend:
	cd /home/matvey/Documents/research/Caches/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/matvey/Documents/research/Caches /home/matvey/Documents/research/Caches /home/matvey/Documents/research/Caches/build /home/matvey/Documents/research/Caches/build /home/matvey/Documents/research/Caches/build/CMakeFiles/perfect.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/perfect.dir/depend


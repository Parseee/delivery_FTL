# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.27.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.27.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/ilababakov/Documents/code/study_solutions/prac/delivery_FTL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ilababakov/Documents/code/study_solutions/prac/delivery_FTL/build

# Include any dependencies generated for this target.
include CMakeFiles/delivery_FTL.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/delivery_FTL.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/delivery_FTL.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/delivery_FTL.dir/flags.make

CMakeFiles/delivery_FTL.dir/main.cpp.o: CMakeFiles/delivery_FTL.dir/flags.make
CMakeFiles/delivery_FTL.dir/main.cpp.o: /Users/ilababakov/Documents/code/study_solutions/prac/delivery_FTL/main.cpp
CMakeFiles/delivery_FTL.dir/main.cpp.o: CMakeFiles/delivery_FTL.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ilababakov/Documents/code/study_solutions/prac/delivery_FTL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/delivery_FTL.dir/main.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/delivery_FTL.dir/main.cpp.o -MF CMakeFiles/delivery_FTL.dir/main.cpp.o.d -o CMakeFiles/delivery_FTL.dir/main.cpp.o -c /Users/ilababakov/Documents/code/study_solutions/prac/delivery_FTL/main.cpp

CMakeFiles/delivery_FTL.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/delivery_FTL.dir/main.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ilababakov/Documents/code/study_solutions/prac/delivery_FTL/main.cpp > CMakeFiles/delivery_FTL.dir/main.cpp.i

CMakeFiles/delivery_FTL.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/delivery_FTL.dir/main.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ilababakov/Documents/code/study_solutions/prac/delivery_FTL/main.cpp -o CMakeFiles/delivery_FTL.dir/main.cpp.s

# Object files for target delivery_FTL
delivery_FTL_OBJECTS = \
"CMakeFiles/delivery_FTL.dir/main.cpp.o"

# External object files for target delivery_FTL
delivery_FTL_EXTERNAL_OBJECTS =

delivery_FTL: CMakeFiles/delivery_FTL.dir/main.cpp.o
delivery_FTL: CMakeFiles/delivery_FTL.dir/build.make
delivery_FTL: CMakeFiles/delivery_FTL.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/ilababakov/Documents/code/study_solutions/prac/delivery_FTL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable delivery_FTL"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/delivery_FTL.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/delivery_FTL.dir/build: delivery_FTL
.PHONY : CMakeFiles/delivery_FTL.dir/build

CMakeFiles/delivery_FTL.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/delivery_FTL.dir/cmake_clean.cmake
.PHONY : CMakeFiles/delivery_FTL.dir/clean

CMakeFiles/delivery_FTL.dir/depend:
	cd /Users/ilababakov/Documents/code/study_solutions/prac/delivery_FTL/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ilababakov/Documents/code/study_solutions/prac/delivery_FTL /Users/ilababakov/Documents/code/study_solutions/prac/delivery_FTL /Users/ilababakov/Documents/code/study_solutions/prac/delivery_FTL/build /Users/ilababakov/Documents/code/study_solutions/prac/delivery_FTL/build /Users/ilababakov/Documents/code/study_solutions/prac/delivery_FTL/build/CMakeFiles/delivery_FTL.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/delivery_FTL.dir/depend


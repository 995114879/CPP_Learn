# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.30.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.30.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/lisprez/Documents/C++教学/2024-09-04/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/lisprez/Documents/C++教学/2024-09-04/src/build

# Include any dependencies generated for this target.
include sub/CMakeFiles/sublib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include sub/CMakeFiles/sublib.dir/compiler_depend.make

# Include the progress variables for this target.
include sub/CMakeFiles/sublib.dir/progress.make

# Include the compile flags for this target's objects.
include sub/CMakeFiles/sublib.dir/flags.make

sub/CMakeFiles/sublib.dir/sub.cpp.o: sub/CMakeFiles/sublib.dir/flags.make
sub/CMakeFiles/sublib.dir/sub.cpp.o: /Users/lisprez/Documents/C++教学/2024-09-04/src/sub/sub.cpp
sub/CMakeFiles/sublib.dir/sub.cpp.o: sub/CMakeFiles/sublib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/lisprez/Documents/C++教学/2024-09-04/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object sub/CMakeFiles/sublib.dir/sub.cpp.o"
	cd /Users/lisprez/Documents/C++教学/2024-09-04/src/build/sub && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT sub/CMakeFiles/sublib.dir/sub.cpp.o -MF CMakeFiles/sublib.dir/sub.cpp.o.d -o CMakeFiles/sublib.dir/sub.cpp.o -c /Users/lisprez/Documents/C++教学/2024-09-04/src/sub/sub.cpp

sub/CMakeFiles/sublib.dir/sub.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/sublib.dir/sub.cpp.i"
	cd /Users/lisprez/Documents/C++教学/2024-09-04/src/build/sub && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lisprez/Documents/C++教学/2024-09-04/src/sub/sub.cpp > CMakeFiles/sublib.dir/sub.cpp.i

sub/CMakeFiles/sublib.dir/sub.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/sublib.dir/sub.cpp.s"
	cd /Users/lisprez/Documents/C++教学/2024-09-04/src/build/sub && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lisprez/Documents/C++教学/2024-09-04/src/sub/sub.cpp -o CMakeFiles/sublib.dir/sub.cpp.s

# Object files for target sublib
sublib_OBJECTS = \
"CMakeFiles/sublib.dir/sub.cpp.o"

# External object files for target sublib
sublib_EXTERNAL_OBJECTS =

sub/libsublib.a: sub/CMakeFiles/sublib.dir/sub.cpp.o
sub/libsublib.a: sub/CMakeFiles/sublib.dir/build.make
sub/libsublib.a: sub/CMakeFiles/sublib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/lisprez/Documents/C++教学/2024-09-04/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libsublib.a"
	cd /Users/lisprez/Documents/C++教学/2024-09-04/src/build/sub && $(CMAKE_COMMAND) -P CMakeFiles/sublib.dir/cmake_clean_target.cmake
	cd /Users/lisprez/Documents/C++教学/2024-09-04/src/build/sub && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sublib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
sub/CMakeFiles/sublib.dir/build: sub/libsublib.a
.PHONY : sub/CMakeFiles/sublib.dir/build

sub/CMakeFiles/sublib.dir/clean:
	cd /Users/lisprez/Documents/C++教学/2024-09-04/src/build/sub && $(CMAKE_COMMAND) -P CMakeFiles/sublib.dir/cmake_clean.cmake
.PHONY : sub/CMakeFiles/sublib.dir/clean

sub/CMakeFiles/sublib.dir/depend:
	cd /Users/lisprez/Documents/C++教学/2024-09-04/src/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/lisprez/Documents/C++教学/2024-09-04/src /Users/lisprez/Documents/C++教学/2024-09-04/src/sub /Users/lisprez/Documents/C++教学/2024-09-04/src/build /Users/lisprez/Documents/C++教学/2024-09-04/src/build/sub /Users/lisprez/Documents/C++教学/2024-09-04/src/build/sub/CMakeFiles/sublib.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : sub/CMakeFiles/sublib.dir/depend


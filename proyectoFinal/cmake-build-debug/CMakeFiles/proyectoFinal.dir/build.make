# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/clion/121/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/121/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jpalexander1706/CLionProjects/proyectoFinal

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jpalexander1706/CLionProjects/proyectoFinal/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/proyectoFinal.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/proyectoFinal.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/proyectoFinal.dir/flags.make

CMakeFiles/proyectoFinal.dir/main.cpp.o: CMakeFiles/proyectoFinal.dir/flags.make
CMakeFiles/proyectoFinal.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jpalexander1706/CLionProjects/proyectoFinal/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/proyectoFinal.dir/main.cpp.o"
	/home/linuxbrew/.linuxbrew/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/proyectoFinal.dir/main.cpp.o -c /home/jpalexander1706/CLionProjects/proyectoFinal/main.cpp

CMakeFiles/proyectoFinal.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/proyectoFinal.dir/main.cpp.i"
	/home/linuxbrew/.linuxbrew/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jpalexander1706/CLionProjects/proyectoFinal/main.cpp > CMakeFiles/proyectoFinal.dir/main.cpp.i

CMakeFiles/proyectoFinal.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/proyectoFinal.dir/main.cpp.s"
	/home/linuxbrew/.linuxbrew/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jpalexander1706/CLionProjects/proyectoFinal/main.cpp -o CMakeFiles/proyectoFinal.dir/main.cpp.s

# Object files for target proyectoFinal
proyectoFinal_OBJECTS = \
"CMakeFiles/proyectoFinal.dir/main.cpp.o"

# External object files for target proyectoFinal
proyectoFinal_EXTERNAL_OBJECTS =

proyectoFinal: CMakeFiles/proyectoFinal.dir/main.cpp.o
proyectoFinal: CMakeFiles/proyectoFinal.dir/build.make
proyectoFinal: CMakeFiles/proyectoFinal.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jpalexander1706/CLionProjects/proyectoFinal/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable proyectoFinal"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/proyectoFinal.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/proyectoFinal.dir/build: proyectoFinal

.PHONY : CMakeFiles/proyectoFinal.dir/build

CMakeFiles/proyectoFinal.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/proyectoFinal.dir/cmake_clean.cmake
.PHONY : CMakeFiles/proyectoFinal.dir/clean

CMakeFiles/proyectoFinal.dir/depend:
	cd /home/jpalexander1706/CLionProjects/proyectoFinal/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jpalexander1706/CLionProjects/proyectoFinal /home/jpalexander1706/CLionProjects/proyectoFinal /home/jpalexander1706/CLionProjects/proyectoFinal/cmake-build-debug /home/jpalexander1706/CLionProjects/proyectoFinal/cmake-build-debug /home/jpalexander1706/CLionProjects/proyectoFinal/cmake-build-debug/CMakeFiles/proyectoFinal.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/proyectoFinal.dir/depend


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
CMAKE_COMMAND = /home/ashiq/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/211.7442.42/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/ashiq/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/211.7442.42/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ashiq/Documents/Workspaces/OpenGL/Offline2-Rasterization

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ashiq/Documents/Workspaces/OpenGL/Offline2-Rasterization/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Offline2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Offline2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Offline2.dir/flags.make

CMakeFiles/Offline2.dir/main.cpp.o: CMakeFiles/Offline2.dir/flags.make
CMakeFiles/Offline2.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ashiq/Documents/Workspaces/OpenGL/Offline2-Rasterization/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Offline2.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Offline2.dir/main.cpp.o -c /home/ashiq/Documents/Workspaces/OpenGL/Offline2-Rasterization/main.cpp

CMakeFiles/Offline2.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Offline2.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ashiq/Documents/Workspaces/OpenGL/Offline2-Rasterization/main.cpp > CMakeFiles/Offline2.dir/main.cpp.i

CMakeFiles/Offline2.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Offline2.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ashiq/Documents/Workspaces/OpenGL/Offline2-Rasterization/main.cpp -o CMakeFiles/Offline2.dir/main.cpp.s

# Object files for target Offline2
Offline2_OBJECTS = \
"CMakeFiles/Offline2.dir/main.cpp.o"

# External object files for target Offline2
Offline2_EXTERNAL_OBJECTS =

Offline2: CMakeFiles/Offline2.dir/main.cpp.o
Offline2: CMakeFiles/Offline2.dir/build.make
Offline2: CMakeFiles/Offline2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ashiq/Documents/Workspaces/OpenGL/Offline2-Rasterization/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Offline2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Offline2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Offline2.dir/build: Offline2

.PHONY : CMakeFiles/Offline2.dir/build

CMakeFiles/Offline2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Offline2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Offline2.dir/clean

CMakeFiles/Offline2.dir/depend:
	cd /home/ashiq/Documents/Workspaces/OpenGL/Offline2-Rasterization/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ashiq/Documents/Workspaces/OpenGL/Offline2-Rasterization /home/ashiq/Documents/Workspaces/OpenGL/Offline2-Rasterization /home/ashiq/Documents/Workspaces/OpenGL/Offline2-Rasterization/cmake-build-debug /home/ashiq/Documents/Workspaces/OpenGL/Offline2-Rasterization/cmake-build-debug /home/ashiq/Documents/Workspaces/OpenGL/Offline2-Rasterization/cmake-build-debug/CMakeFiles/Offline2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Offline2.dir/depend


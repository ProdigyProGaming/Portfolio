# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.15

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\Arron\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\192.7142.39\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\Arron\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\192.7142.39\bin\cmake\win\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "E:\C++ Games\Tic Tac Toe V2.1"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "E:\C++ Games\Tic Tac Toe V2.1\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Tic_Tac_Toe_V2_1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Tic_Tac_Toe_V2_1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Tic_Tac_Toe_V2_1.dir/flags.make

CMakeFiles/Tic_Tac_Toe_V2_1.dir/main.cpp.obj: CMakeFiles/Tic_Tac_Toe_V2_1.dir/flags.make
CMakeFiles/Tic_Tac_Toe_V2_1.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="E:\C++ Games\Tic Tac Toe V2.1\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Tic_Tac_Toe_V2_1.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Tic_Tac_Toe_V2_1.dir\main.cpp.obj -c "E:\C++ Games\Tic Tac Toe V2.1\main.cpp"

CMakeFiles/Tic_Tac_Toe_V2_1.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tic_Tac_Toe_V2_1.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "E:\C++ Games\Tic Tac Toe V2.1\main.cpp" > CMakeFiles\Tic_Tac_Toe_V2_1.dir\main.cpp.i

CMakeFiles/Tic_Tac_Toe_V2_1.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tic_Tac_Toe_V2_1.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "E:\C++ Games\Tic Tac Toe V2.1\main.cpp" -o CMakeFiles\Tic_Tac_Toe_V2_1.dir\main.cpp.s

# Object files for target Tic_Tac_Toe_V2_1
Tic_Tac_Toe_V2_1_OBJECTS = \
"CMakeFiles/Tic_Tac_Toe_V2_1.dir/main.cpp.obj"

# External object files for target Tic_Tac_Toe_V2_1
Tic_Tac_Toe_V2_1_EXTERNAL_OBJECTS =

Tic_Tac_Toe_V2_1.exe: CMakeFiles/Tic_Tac_Toe_V2_1.dir/main.cpp.obj
Tic_Tac_Toe_V2_1.exe: CMakeFiles/Tic_Tac_Toe_V2_1.dir/build.make
Tic_Tac_Toe_V2_1.exe: CMakeFiles/Tic_Tac_Toe_V2_1.dir/linklibs.rsp
Tic_Tac_Toe_V2_1.exe: CMakeFiles/Tic_Tac_Toe_V2_1.dir/objects1.rsp
Tic_Tac_Toe_V2_1.exe: CMakeFiles/Tic_Tac_Toe_V2_1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="E:\C++ Games\Tic Tac Toe V2.1\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Tic_Tac_Toe_V2_1.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Tic_Tac_Toe_V2_1.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Tic_Tac_Toe_V2_1.dir/build: Tic_Tac_Toe_V2_1.exe

.PHONY : CMakeFiles/Tic_Tac_Toe_V2_1.dir/build

CMakeFiles/Tic_Tac_Toe_V2_1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Tic_Tac_Toe_V2_1.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Tic_Tac_Toe_V2_1.dir/clean

CMakeFiles/Tic_Tac_Toe_V2_1.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "E:\C++ Games\Tic Tac Toe V2.1" "E:\C++ Games\Tic Tac Toe V2.1" "E:\C++ Games\Tic Tac Toe V2.1\cmake-build-debug" "E:\C++ Games\Tic Tac Toe V2.1\cmake-build-debug" "E:\C++ Games\Tic Tac Toe V2.1\cmake-build-debug\CMakeFiles\Tic_Tac_Toe_V2_1.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Tic_Tac_Toe_V2_1.dir/depend


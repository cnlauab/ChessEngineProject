# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.23.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.23.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/build

# Include any dependencies generated for this target.
include CMakeFiles/ChessEngineProject.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ChessEngineProject.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ChessEngineProject.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ChessEngineProject.dir/flags.make

CMakeFiles/ChessEngineProject.dir/ChessEngineProject.cpp.o: CMakeFiles/ChessEngineProject.dir/flags.make
CMakeFiles/ChessEngineProject.dir/ChessEngineProject.cpp.o: ../ChessEngineProject.cpp
CMakeFiles/ChessEngineProject.dir/ChessEngineProject.cpp.o: CMakeFiles/ChessEngineProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ChessEngineProject.dir/ChessEngineProject.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ChessEngineProject.dir/ChessEngineProject.cpp.o -MF CMakeFiles/ChessEngineProject.dir/ChessEngineProject.cpp.o.d -o CMakeFiles/ChessEngineProject.dir/ChessEngineProject.cpp.o -c /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/ChessEngineProject.cpp

CMakeFiles/ChessEngineProject.dir/ChessEngineProject.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChessEngineProject.dir/ChessEngineProject.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/ChessEngineProject.cpp > CMakeFiles/ChessEngineProject.dir/ChessEngineProject.cpp.i

CMakeFiles/ChessEngineProject.dir/ChessEngineProject.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChessEngineProject.dir/ChessEngineProject.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/ChessEngineProject.cpp -o CMakeFiles/ChessEngineProject.dir/ChessEngineProject.cpp.s

CMakeFiles/ChessEngineProject.dir/Position.cpp.o: CMakeFiles/ChessEngineProject.dir/flags.make
CMakeFiles/ChessEngineProject.dir/Position.cpp.o: ../Position.cpp
CMakeFiles/ChessEngineProject.dir/Position.cpp.o: CMakeFiles/ChessEngineProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ChessEngineProject.dir/Position.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ChessEngineProject.dir/Position.cpp.o -MF CMakeFiles/ChessEngineProject.dir/Position.cpp.o.d -o CMakeFiles/ChessEngineProject.dir/Position.cpp.o -c /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/Position.cpp

CMakeFiles/ChessEngineProject.dir/Position.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChessEngineProject.dir/Position.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/Position.cpp > CMakeFiles/ChessEngineProject.dir/Position.cpp.i

CMakeFiles/ChessEngineProject.dir/Position.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChessEngineProject.dir/Position.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/Position.cpp -o CMakeFiles/ChessEngineProject.dir/Position.cpp.s

CMakeFiles/ChessEngineProject.dir/State.cpp.o: CMakeFiles/ChessEngineProject.dir/flags.make
CMakeFiles/ChessEngineProject.dir/State.cpp.o: ../State.cpp
CMakeFiles/ChessEngineProject.dir/State.cpp.o: CMakeFiles/ChessEngineProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ChessEngineProject.dir/State.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ChessEngineProject.dir/State.cpp.o -MF CMakeFiles/ChessEngineProject.dir/State.cpp.o.d -o CMakeFiles/ChessEngineProject.dir/State.cpp.o -c /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/State.cpp

CMakeFiles/ChessEngineProject.dir/State.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChessEngineProject.dir/State.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/State.cpp > CMakeFiles/ChessEngineProject.dir/State.cpp.i

CMakeFiles/ChessEngineProject.dir/State.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChessEngineProject.dir/State.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/State.cpp -o CMakeFiles/ChessEngineProject.dir/State.cpp.s

CMakeFiles/ChessEngineProject.dir/Validator.cpp.o: CMakeFiles/ChessEngineProject.dir/flags.make
CMakeFiles/ChessEngineProject.dir/Validator.cpp.o: ../Validator.cpp
CMakeFiles/ChessEngineProject.dir/Validator.cpp.o: CMakeFiles/ChessEngineProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/ChessEngineProject.dir/Validator.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ChessEngineProject.dir/Validator.cpp.o -MF CMakeFiles/ChessEngineProject.dir/Validator.cpp.o.d -o CMakeFiles/ChessEngineProject.dir/Validator.cpp.o -c /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/Validator.cpp

CMakeFiles/ChessEngineProject.dir/Validator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChessEngineProject.dir/Validator.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/Validator.cpp > CMakeFiles/ChessEngineProject.dir/Validator.cpp.i

CMakeFiles/ChessEngineProject.dir/Validator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChessEngineProject.dir/Validator.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/Validator.cpp -o CMakeFiles/ChessEngineProject.dir/Validator.cpp.s

CMakeFiles/ChessEngineProject.dir/MoveGenerator.cpp.o: CMakeFiles/ChessEngineProject.dir/flags.make
CMakeFiles/ChessEngineProject.dir/MoveGenerator.cpp.o: ../MoveGenerator.cpp
CMakeFiles/ChessEngineProject.dir/MoveGenerator.cpp.o: CMakeFiles/ChessEngineProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/ChessEngineProject.dir/MoveGenerator.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ChessEngineProject.dir/MoveGenerator.cpp.o -MF CMakeFiles/ChessEngineProject.dir/MoveGenerator.cpp.o.d -o CMakeFiles/ChessEngineProject.dir/MoveGenerator.cpp.o -c /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/MoveGenerator.cpp

CMakeFiles/ChessEngineProject.dir/MoveGenerator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChessEngineProject.dir/MoveGenerator.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/MoveGenerator.cpp > CMakeFiles/ChessEngineProject.dir/MoveGenerator.cpp.i

CMakeFiles/ChessEngineProject.dir/MoveGenerator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChessEngineProject.dir/MoveGenerator.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/MoveGenerator.cpp -o CMakeFiles/ChessEngineProject.dir/MoveGenerator.cpp.s

CMakeFiles/ChessEngineProject.dir/ChessUtil.cpp.o: CMakeFiles/ChessEngineProject.dir/flags.make
CMakeFiles/ChessEngineProject.dir/ChessUtil.cpp.o: ../ChessUtil.cpp
CMakeFiles/ChessEngineProject.dir/ChessUtil.cpp.o: CMakeFiles/ChessEngineProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/ChessEngineProject.dir/ChessUtil.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ChessEngineProject.dir/ChessUtil.cpp.o -MF CMakeFiles/ChessEngineProject.dir/ChessUtil.cpp.o.d -o CMakeFiles/ChessEngineProject.dir/ChessUtil.cpp.o -c /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/ChessUtil.cpp

CMakeFiles/ChessEngineProject.dir/ChessUtil.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChessEngineProject.dir/ChessUtil.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/ChessUtil.cpp > CMakeFiles/ChessEngineProject.dir/ChessUtil.cpp.i

CMakeFiles/ChessEngineProject.dir/ChessUtil.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChessEngineProject.dir/ChessUtil.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/ChessUtil.cpp -o CMakeFiles/ChessEngineProject.dir/ChessUtil.cpp.s

CMakeFiles/ChessEngineProject.dir/LegalChecker.cpp.o: CMakeFiles/ChessEngineProject.dir/flags.make
CMakeFiles/ChessEngineProject.dir/LegalChecker.cpp.o: ../LegalChecker.cpp
CMakeFiles/ChessEngineProject.dir/LegalChecker.cpp.o: CMakeFiles/ChessEngineProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/ChessEngineProject.dir/LegalChecker.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ChessEngineProject.dir/LegalChecker.cpp.o -MF CMakeFiles/ChessEngineProject.dir/LegalChecker.cpp.o.d -o CMakeFiles/ChessEngineProject.dir/LegalChecker.cpp.o -c /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/LegalChecker.cpp

CMakeFiles/ChessEngineProject.dir/LegalChecker.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChessEngineProject.dir/LegalChecker.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/LegalChecker.cpp > CMakeFiles/ChessEngineProject.dir/LegalChecker.cpp.i

CMakeFiles/ChessEngineProject.dir/LegalChecker.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChessEngineProject.dir/LegalChecker.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/LegalChecker.cpp -o CMakeFiles/ChessEngineProject.dir/LegalChecker.cpp.s

CMakeFiles/ChessEngineProject.dir/Debug.cpp.o: CMakeFiles/ChessEngineProject.dir/flags.make
CMakeFiles/ChessEngineProject.dir/Debug.cpp.o: ../Debug.cpp
CMakeFiles/ChessEngineProject.dir/Debug.cpp.o: CMakeFiles/ChessEngineProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/ChessEngineProject.dir/Debug.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ChessEngineProject.dir/Debug.cpp.o -MF CMakeFiles/ChessEngineProject.dir/Debug.cpp.o.d -o CMakeFiles/ChessEngineProject.dir/Debug.cpp.o -c /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/Debug.cpp

CMakeFiles/ChessEngineProject.dir/Debug.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChessEngineProject.dir/Debug.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/Debug.cpp > CMakeFiles/ChessEngineProject.dir/Debug.cpp.i

CMakeFiles/ChessEngineProject.dir/Debug.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChessEngineProject.dir/Debug.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/Debug.cpp -o CMakeFiles/ChessEngineProject.dir/Debug.cpp.s

CMakeFiles/ChessEngineProject.dir/Evaluation.cpp.o: CMakeFiles/ChessEngineProject.dir/flags.make
CMakeFiles/ChessEngineProject.dir/Evaluation.cpp.o: ../Evaluation.cpp
CMakeFiles/ChessEngineProject.dir/Evaluation.cpp.o: CMakeFiles/ChessEngineProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/ChessEngineProject.dir/Evaluation.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ChessEngineProject.dir/Evaluation.cpp.o -MF CMakeFiles/ChessEngineProject.dir/Evaluation.cpp.o.d -o CMakeFiles/ChessEngineProject.dir/Evaluation.cpp.o -c /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/Evaluation.cpp

CMakeFiles/ChessEngineProject.dir/Evaluation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChessEngineProject.dir/Evaluation.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/Evaluation.cpp > CMakeFiles/ChessEngineProject.dir/Evaluation.cpp.i

CMakeFiles/ChessEngineProject.dir/Evaluation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChessEngineProject.dir/Evaluation.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/Evaluation.cpp -o CMakeFiles/ChessEngineProject.dir/Evaluation.cpp.s

CMakeFiles/ChessEngineProject.dir/SquareControl.cpp.o: CMakeFiles/ChessEngineProject.dir/flags.make
CMakeFiles/ChessEngineProject.dir/SquareControl.cpp.o: ../SquareControl.cpp
CMakeFiles/ChessEngineProject.dir/SquareControl.cpp.o: CMakeFiles/ChessEngineProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/ChessEngineProject.dir/SquareControl.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ChessEngineProject.dir/SquareControl.cpp.o -MF CMakeFiles/ChessEngineProject.dir/SquareControl.cpp.o.d -o CMakeFiles/ChessEngineProject.dir/SquareControl.cpp.o -c /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/SquareControl.cpp

CMakeFiles/ChessEngineProject.dir/SquareControl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChessEngineProject.dir/SquareControl.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/SquareControl.cpp > CMakeFiles/ChessEngineProject.dir/SquareControl.cpp.i

CMakeFiles/ChessEngineProject.dir/SquareControl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChessEngineProject.dir/SquareControl.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/SquareControl.cpp -o CMakeFiles/ChessEngineProject.dir/SquareControl.cpp.s

CMakeFiles/ChessEngineProject.dir/UCI.cpp.o: CMakeFiles/ChessEngineProject.dir/flags.make
CMakeFiles/ChessEngineProject.dir/UCI.cpp.o: ../UCI.cpp
CMakeFiles/ChessEngineProject.dir/UCI.cpp.o: CMakeFiles/ChessEngineProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/ChessEngineProject.dir/UCI.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ChessEngineProject.dir/UCI.cpp.o -MF CMakeFiles/ChessEngineProject.dir/UCI.cpp.o.d -o CMakeFiles/ChessEngineProject.dir/UCI.cpp.o -c /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/UCI.cpp

CMakeFiles/ChessEngineProject.dir/UCI.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChessEngineProject.dir/UCI.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/UCI.cpp > CMakeFiles/ChessEngineProject.dir/UCI.cpp.i

CMakeFiles/ChessEngineProject.dir/UCI.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChessEngineProject.dir/UCI.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/UCI.cpp -o CMakeFiles/ChessEngineProject.dir/UCI.cpp.s

CMakeFiles/ChessEngineProject.dir/Bitboards.cpp.o: CMakeFiles/ChessEngineProject.dir/flags.make
CMakeFiles/ChessEngineProject.dir/Bitboards.cpp.o: ../Bitboards.cpp
CMakeFiles/ChessEngineProject.dir/Bitboards.cpp.o: CMakeFiles/ChessEngineProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/ChessEngineProject.dir/Bitboards.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ChessEngineProject.dir/Bitboards.cpp.o -MF CMakeFiles/ChessEngineProject.dir/Bitboards.cpp.o.d -o CMakeFiles/ChessEngineProject.dir/Bitboards.cpp.o -c /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/Bitboards.cpp

CMakeFiles/ChessEngineProject.dir/Bitboards.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChessEngineProject.dir/Bitboards.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/Bitboards.cpp > CMakeFiles/ChessEngineProject.dir/Bitboards.cpp.i

CMakeFiles/ChessEngineProject.dir/Bitboards.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChessEngineProject.dir/Bitboards.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/Bitboards.cpp -o CMakeFiles/ChessEngineProject.dir/Bitboards.cpp.s

CMakeFiles/ChessEngineProject.dir/BitUtil.cpp.o: CMakeFiles/ChessEngineProject.dir/flags.make
CMakeFiles/ChessEngineProject.dir/BitUtil.cpp.o: ../BitUtil.cpp
CMakeFiles/ChessEngineProject.dir/BitUtil.cpp.o: CMakeFiles/ChessEngineProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/ChessEngineProject.dir/BitUtil.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ChessEngineProject.dir/BitUtil.cpp.o -MF CMakeFiles/ChessEngineProject.dir/BitUtil.cpp.o.d -o CMakeFiles/ChessEngineProject.dir/BitUtil.cpp.o -c /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/BitUtil.cpp

CMakeFiles/ChessEngineProject.dir/BitUtil.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChessEngineProject.dir/BitUtil.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/BitUtil.cpp > CMakeFiles/ChessEngineProject.dir/BitUtil.cpp.i

CMakeFiles/ChessEngineProject.dir/BitUtil.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChessEngineProject.dir/BitUtil.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/BitUtil.cpp -o CMakeFiles/ChessEngineProject.dir/BitUtil.cpp.s

CMakeFiles/ChessEngineProject.dir/MagicBits.cpp.o: CMakeFiles/ChessEngineProject.dir/flags.make
CMakeFiles/ChessEngineProject.dir/MagicBits.cpp.o: ../MagicBits.cpp
CMakeFiles/ChessEngineProject.dir/MagicBits.cpp.o: CMakeFiles/ChessEngineProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/ChessEngineProject.dir/MagicBits.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ChessEngineProject.dir/MagicBits.cpp.o -MF CMakeFiles/ChessEngineProject.dir/MagicBits.cpp.o.d -o CMakeFiles/ChessEngineProject.dir/MagicBits.cpp.o -c /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/MagicBits.cpp

CMakeFiles/ChessEngineProject.dir/MagicBits.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChessEngineProject.dir/MagicBits.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/MagicBits.cpp > CMakeFiles/ChessEngineProject.dir/MagicBits.cpp.i

CMakeFiles/ChessEngineProject.dir/MagicBits.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChessEngineProject.dir/MagicBits.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/MagicBits.cpp -o CMakeFiles/ChessEngineProject.dir/MagicBits.cpp.s

CMakeFiles/ChessEngineProject.dir/MagicUtil.cpp.o: CMakeFiles/ChessEngineProject.dir/flags.make
CMakeFiles/ChessEngineProject.dir/MagicUtil.cpp.o: ../MagicUtil.cpp
CMakeFiles/ChessEngineProject.dir/MagicUtil.cpp.o: CMakeFiles/ChessEngineProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/ChessEngineProject.dir/MagicUtil.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ChessEngineProject.dir/MagicUtil.cpp.o -MF CMakeFiles/ChessEngineProject.dir/MagicUtil.cpp.o.d -o CMakeFiles/ChessEngineProject.dir/MagicUtil.cpp.o -c /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/MagicUtil.cpp

CMakeFiles/ChessEngineProject.dir/MagicUtil.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChessEngineProject.dir/MagicUtil.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/MagicUtil.cpp > CMakeFiles/ChessEngineProject.dir/MagicUtil.cpp.i

CMakeFiles/ChessEngineProject.dir/MagicUtil.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChessEngineProject.dir/MagicUtil.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/MagicUtil.cpp -o CMakeFiles/ChessEngineProject.dir/MagicUtil.cpp.s

CMakeFiles/ChessEngineProject.dir/Perft.cpp.o: CMakeFiles/ChessEngineProject.dir/flags.make
CMakeFiles/ChessEngineProject.dir/Perft.cpp.o: ../Perft.cpp
CMakeFiles/ChessEngineProject.dir/Perft.cpp.o: CMakeFiles/ChessEngineProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object CMakeFiles/ChessEngineProject.dir/Perft.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ChessEngineProject.dir/Perft.cpp.o -MF CMakeFiles/ChessEngineProject.dir/Perft.cpp.o.d -o CMakeFiles/ChessEngineProject.dir/Perft.cpp.o -c /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/Perft.cpp

CMakeFiles/ChessEngineProject.dir/Perft.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChessEngineProject.dir/Perft.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/Perft.cpp > CMakeFiles/ChessEngineProject.dir/Perft.cpp.i

CMakeFiles/ChessEngineProject.dir/Perft.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChessEngineProject.dir/Perft.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/Perft.cpp -o CMakeFiles/ChessEngineProject.dir/Perft.cpp.s

CMakeFiles/ChessEngineProject.dir/Score.cpp.o: CMakeFiles/ChessEngineProject.dir/flags.make
CMakeFiles/ChessEngineProject.dir/Score.cpp.o: ../Score.cpp
CMakeFiles/ChessEngineProject.dir/Score.cpp.o: CMakeFiles/ChessEngineProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building CXX object CMakeFiles/ChessEngineProject.dir/Score.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ChessEngineProject.dir/Score.cpp.o -MF CMakeFiles/ChessEngineProject.dir/Score.cpp.o.d -o CMakeFiles/ChessEngineProject.dir/Score.cpp.o -c /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/Score.cpp

CMakeFiles/ChessEngineProject.dir/Score.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChessEngineProject.dir/Score.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/Score.cpp > CMakeFiles/ChessEngineProject.dir/Score.cpp.i

CMakeFiles/ChessEngineProject.dir/Score.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChessEngineProject.dir/Score.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/Score.cpp -o CMakeFiles/ChessEngineProject.dir/Score.cpp.s

# Object files for target ChessEngineProject
ChessEngineProject_OBJECTS = \
"CMakeFiles/ChessEngineProject.dir/ChessEngineProject.cpp.o" \
"CMakeFiles/ChessEngineProject.dir/Position.cpp.o" \
"CMakeFiles/ChessEngineProject.dir/State.cpp.o" \
"CMakeFiles/ChessEngineProject.dir/Validator.cpp.o" \
"CMakeFiles/ChessEngineProject.dir/MoveGenerator.cpp.o" \
"CMakeFiles/ChessEngineProject.dir/ChessUtil.cpp.o" \
"CMakeFiles/ChessEngineProject.dir/LegalChecker.cpp.o" \
"CMakeFiles/ChessEngineProject.dir/Debug.cpp.o" \
"CMakeFiles/ChessEngineProject.dir/Evaluation.cpp.o" \
"CMakeFiles/ChessEngineProject.dir/SquareControl.cpp.o" \
"CMakeFiles/ChessEngineProject.dir/UCI.cpp.o" \
"CMakeFiles/ChessEngineProject.dir/Bitboards.cpp.o" \
"CMakeFiles/ChessEngineProject.dir/BitUtil.cpp.o" \
"CMakeFiles/ChessEngineProject.dir/MagicBits.cpp.o" \
"CMakeFiles/ChessEngineProject.dir/MagicUtil.cpp.o" \
"CMakeFiles/ChessEngineProject.dir/Perft.cpp.o" \
"CMakeFiles/ChessEngineProject.dir/Score.cpp.o"

# External object files for target ChessEngineProject
ChessEngineProject_EXTERNAL_OBJECTS =

ChessEngineProject: CMakeFiles/ChessEngineProject.dir/ChessEngineProject.cpp.o
ChessEngineProject: CMakeFiles/ChessEngineProject.dir/Position.cpp.o
ChessEngineProject: CMakeFiles/ChessEngineProject.dir/State.cpp.o
ChessEngineProject: CMakeFiles/ChessEngineProject.dir/Validator.cpp.o
ChessEngineProject: CMakeFiles/ChessEngineProject.dir/MoveGenerator.cpp.o
ChessEngineProject: CMakeFiles/ChessEngineProject.dir/ChessUtil.cpp.o
ChessEngineProject: CMakeFiles/ChessEngineProject.dir/LegalChecker.cpp.o
ChessEngineProject: CMakeFiles/ChessEngineProject.dir/Debug.cpp.o
ChessEngineProject: CMakeFiles/ChessEngineProject.dir/Evaluation.cpp.o
ChessEngineProject: CMakeFiles/ChessEngineProject.dir/SquareControl.cpp.o
ChessEngineProject: CMakeFiles/ChessEngineProject.dir/UCI.cpp.o
ChessEngineProject: CMakeFiles/ChessEngineProject.dir/Bitboards.cpp.o
ChessEngineProject: CMakeFiles/ChessEngineProject.dir/BitUtil.cpp.o
ChessEngineProject: CMakeFiles/ChessEngineProject.dir/MagicBits.cpp.o
ChessEngineProject: CMakeFiles/ChessEngineProject.dir/MagicUtil.cpp.o
ChessEngineProject: CMakeFiles/ChessEngineProject.dir/Perft.cpp.o
ChessEngineProject: CMakeFiles/ChessEngineProject.dir/Score.cpp.o
ChessEngineProject: CMakeFiles/ChessEngineProject.dir/build.make
ChessEngineProject: CMakeFiles/ChessEngineProject.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Linking CXX executable ChessEngineProject"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ChessEngineProject.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ChessEngineProject.dir/build: ChessEngineProject
.PHONY : CMakeFiles/ChessEngineProject.dir/build

CMakeFiles/ChessEngineProject.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ChessEngineProject.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ChessEngineProject.dir/clean

CMakeFiles/ChessEngineProject.dir/depend:
	cd /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/build /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/build /Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/build/CMakeFiles/ChessEngineProject.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ChessEngineProject.dir/depend


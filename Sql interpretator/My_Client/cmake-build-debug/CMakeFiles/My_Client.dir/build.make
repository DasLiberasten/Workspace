# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /home/nikita/clion-2020.2.1/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/nikita/clion-2020.2.1/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/nikita/CLionProjects/My_Client

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nikita/CLionProjects/My_Client/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/My_Client.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/My_Client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/My_Client.dir/flags.make

CMakeFiles/My_Client.dir/Client.cpp.o: CMakeFiles/My_Client.dir/flags.make
CMakeFiles/My_Client.dir/Client.cpp.o: ../Client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nikita/CLionProjects/My_Client/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/My_Client.dir/Client.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/My_Client.dir/Client.cpp.o -c /home/nikita/CLionProjects/My_Client/Client.cpp

CMakeFiles/My_Client.dir/Client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/My_Client.dir/Client.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nikita/CLionProjects/My_Client/Client.cpp > CMakeFiles/My_Client.dir/Client.cpp.i

CMakeFiles/My_Client.dir/Client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/My_Client.dir/Client.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nikita/CLionProjects/My_Client/Client.cpp -o CMakeFiles/My_Client.dir/Client.cpp.s

CMakeFiles/My_Client.dir/Sock_client.cpp.o: CMakeFiles/My_Client.dir/flags.make
CMakeFiles/My_Client.dir/Sock_client.cpp.o: ../Sock_client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nikita/CLionProjects/My_Client/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/My_Client.dir/Sock_client.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/My_Client.dir/Sock_client.cpp.o -c /home/nikita/CLionProjects/My_Client/Sock_client.cpp

CMakeFiles/My_Client.dir/Sock_client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/My_Client.dir/Sock_client.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nikita/CLionProjects/My_Client/Sock_client.cpp > CMakeFiles/My_Client.dir/Sock_client.cpp.i

CMakeFiles/My_Client.dir/Sock_client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/My_Client.dir/Sock_client.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nikita/CLionProjects/My_Client/Sock_client.cpp -o CMakeFiles/My_Client.dir/Sock_client.cpp.s

# Object files for target My_Client
My_Client_OBJECTS = \
"CMakeFiles/My_Client.dir/Client.cpp.o" \
"CMakeFiles/My_Client.dir/Sock_client.cpp.o"

# External object files for target My_Client
My_Client_EXTERNAL_OBJECTS =

My_Client: CMakeFiles/My_Client.dir/Client.cpp.o
My_Client: CMakeFiles/My_Client.dir/Sock_client.cpp.o
My_Client: CMakeFiles/My_Client.dir/build.make
My_Client: CMakeFiles/My_Client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nikita/CLionProjects/My_Client/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable My_Client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/My_Client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/My_Client.dir/build: My_Client

.PHONY : CMakeFiles/My_Client.dir/build

CMakeFiles/My_Client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/My_Client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/My_Client.dir/clean

CMakeFiles/My_Client.dir/depend:
	cd /home/nikita/CLionProjects/My_Client/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nikita/CLionProjects/My_Client /home/nikita/CLionProjects/My_Client /home/nikita/CLionProjects/My_Client/cmake-build-debug /home/nikita/CLionProjects/My_Client/cmake-build-debug /home/nikita/CLionProjects/My_Client/cmake-build-debug/CMakeFiles/My_Client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/My_Client.dir/depend

# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/acceber/projects/eecs395/ORB_SLAM/debug/CvCMakeTest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/acceber/projects/eecs395/ORB_SLAM/debug/CvCMakeTest

# Include any dependencies generated for this target.
include CMakeFiles/CvTest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/CvTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CvTest.dir/flags.make

CMakeFiles/CvTest.dir/src/CvTest.o: CMakeFiles/CvTest.dir/flags.make
CMakeFiles/CvTest.dir/src/CvTest.o: src/CvTest.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/acceber/projects/eecs395/ORB_SLAM/debug/CvCMakeTest/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/CvTest.dir/src/CvTest.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/CvTest.dir/src/CvTest.o -c /home/acceber/projects/eecs395/ORB_SLAM/debug/CvCMakeTest/src/CvTest.cc

CMakeFiles/CvTest.dir/src/CvTest.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CvTest.dir/src/CvTest.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/acceber/projects/eecs395/ORB_SLAM/debug/CvCMakeTest/src/CvTest.cc > CMakeFiles/CvTest.dir/src/CvTest.i

CMakeFiles/CvTest.dir/src/CvTest.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CvTest.dir/src/CvTest.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/acceber/projects/eecs395/ORB_SLAM/debug/CvCMakeTest/src/CvTest.cc -o CMakeFiles/CvTest.dir/src/CvTest.s

CMakeFiles/CvTest.dir/src/CvTest.o.requires:
.PHONY : CMakeFiles/CvTest.dir/src/CvTest.o.requires

CMakeFiles/CvTest.dir/src/CvTest.o.provides: CMakeFiles/CvTest.dir/src/CvTest.o.requires
	$(MAKE) -f CMakeFiles/CvTest.dir/build.make CMakeFiles/CvTest.dir/src/CvTest.o.provides.build
.PHONY : CMakeFiles/CvTest.dir/src/CvTest.o.provides

CMakeFiles/CvTest.dir/src/CvTest.o.provides.build: CMakeFiles/CvTest.dir/src/CvTest.o

# Object files for target CvTest
CvTest_OBJECTS = \
"CMakeFiles/CvTest.dir/src/CvTest.o"

# External object files for target CvTest
CvTest_EXTERNAL_OBJECTS =

bin/CvTest: CMakeFiles/CvTest.dir/src/CvTest.o
bin/CvTest: CMakeFiles/CvTest.dir/build.make
bin/CvTest: /usr/lib/x86_64-linux-gnu/libopencv_videostab.so.2.4.8
bin/CvTest: /usr/lib/x86_64-linux-gnu/libopencv_video.so.2.4.8
bin/CvTest: /usr/lib/x86_64-linux-gnu/libopencv_ts.so.2.4.8
bin/CvTest: /usr/lib/x86_64-linux-gnu/libopencv_superres.so.2.4.8
bin/CvTest: /usr/lib/x86_64-linux-gnu/libopencv_stitching.so.2.4.8
bin/CvTest: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.2.4.8
bin/CvTest: /usr/lib/x86_64-linux-gnu/libopencv_ocl.so.2.4.8
bin/CvTest: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.2.4.8
bin/CvTest: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.2.4.8
bin/CvTest: /usr/lib/x86_64-linux-gnu/libopencv_legacy.so.2.4.8
bin/CvTest: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.2.4.8
bin/CvTest: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.2.4.8
bin/CvTest: /usr/lib/x86_64-linux-gnu/libopencv_gpu.so.2.4.8
bin/CvTest: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.2.4.8
bin/CvTest: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.2.4.8
bin/CvTest: /usr/lib/x86_64-linux-gnu/libopencv_core.so.2.4.8
bin/CvTest: /usr/lib/x86_64-linux-gnu/libopencv_contrib.so.2.4.8
bin/CvTest: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.2.4.8
bin/CvTest: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.2.4.8
bin/CvTest: /usr/lib/x86_64-linux-gnu/libopencv_legacy.so.2.4.8
bin/CvTest: /usr/lib/x86_64-linux-gnu/libopencv_video.so.2.4.8
bin/CvTest: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.2.4.8
bin/CvTest: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.2.4.8
bin/CvTest: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.2.4.8
bin/CvTest: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.2.4.8
bin/CvTest: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.2.4.8
bin/CvTest: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.2.4.8
bin/CvTest: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.2.4.8
bin/CvTest: /usr/lib/x86_64-linux-gnu/libopencv_core.so.2.4.8
bin/CvTest: CMakeFiles/CvTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable bin/CvTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CvTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CvTest.dir/build: bin/CvTest
.PHONY : CMakeFiles/CvTest.dir/build

CMakeFiles/CvTest.dir/requires: CMakeFiles/CvTest.dir/src/CvTest.o.requires
.PHONY : CMakeFiles/CvTest.dir/requires

CMakeFiles/CvTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CvTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CvTest.dir/clean

CMakeFiles/CvTest.dir/depend:
	cd /home/acceber/projects/eecs395/ORB_SLAM/debug/CvCMakeTest && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/acceber/projects/eecs395/ORB_SLAM/debug/CvCMakeTest /home/acceber/projects/eecs395/ORB_SLAM/debug/CvCMakeTest /home/acceber/projects/eecs395/ORB_SLAM/debug/CvCMakeTest /home/acceber/projects/eecs395/ORB_SLAM/debug/CvCMakeTest /home/acceber/projects/eecs395/ORB_SLAM/debug/CvCMakeTest/CMakeFiles/CvTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CvTest.dir/depend

# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\marti\Documents\StringBeat

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\marti\Documents\StringBeat\build

# Include any dependencies generated for this target.
include libs/raylib/src/CMakeFiles/raylib_static.dir/depend.make

# Include the progress variables for this target.
include libs/raylib/src/CMakeFiles/raylib_static.dir/progress.make

# Include the compile flags for this target's objects.
include libs/raylib/src/CMakeFiles/raylib_static.dir/flags.make

libs/raylib/src/CMakeFiles/raylib_static.dir/core.c.obj: libs/raylib/src/CMakeFiles/raylib_static.dir/flags.make
libs/raylib/src/CMakeFiles/raylib_static.dir/core.c.obj: libs/raylib/src/CMakeFiles/raylib_static.dir/includes_C.rsp
libs/raylib/src/CMakeFiles/raylib_static.dir/core.c.obj: ../libs/raylib/src/core.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\marti\Documents\StringBeat\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object libs/raylib/src/CMakeFiles/raylib_static.dir/core.c.obj"
	cd /d C:\Users\marti\Documents\StringBeat\build\libs\raylib\src && C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\raylib_static.dir\core.c.obj   -c C:\Users\marti\Documents\StringBeat\libs\raylib\src\core.c

libs/raylib/src/CMakeFiles/raylib_static.dir/core.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/raylib_static.dir/core.c.i"
	cd /d C:\Users\marti\Documents\StringBeat\build\libs\raylib\src && C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\marti\Documents\StringBeat\libs\raylib\src\core.c > CMakeFiles\raylib_static.dir\core.c.i

libs/raylib/src/CMakeFiles/raylib_static.dir/core.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/raylib_static.dir/core.c.s"
	cd /d C:\Users\marti\Documents\StringBeat\build\libs\raylib\src && C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\marti\Documents\StringBeat\libs\raylib\src\core.c -o CMakeFiles\raylib_static.dir\core.c.s

libs/raylib/src/CMakeFiles/raylib_static.dir/models.c.obj: libs/raylib/src/CMakeFiles/raylib_static.dir/flags.make
libs/raylib/src/CMakeFiles/raylib_static.dir/models.c.obj: libs/raylib/src/CMakeFiles/raylib_static.dir/includes_C.rsp
libs/raylib/src/CMakeFiles/raylib_static.dir/models.c.obj: ../libs/raylib/src/models.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\marti\Documents\StringBeat\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object libs/raylib/src/CMakeFiles/raylib_static.dir/models.c.obj"
	cd /d C:\Users\marti\Documents\StringBeat\build\libs\raylib\src && C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\raylib_static.dir\models.c.obj   -c C:\Users\marti\Documents\StringBeat\libs\raylib\src\models.c

libs/raylib/src/CMakeFiles/raylib_static.dir/models.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/raylib_static.dir/models.c.i"
	cd /d C:\Users\marti\Documents\StringBeat\build\libs\raylib\src && C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\marti\Documents\StringBeat\libs\raylib\src\models.c > CMakeFiles\raylib_static.dir\models.c.i

libs/raylib/src/CMakeFiles/raylib_static.dir/models.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/raylib_static.dir/models.c.s"
	cd /d C:\Users\marti\Documents\StringBeat\build\libs\raylib\src && C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\marti\Documents\StringBeat\libs\raylib\src\models.c -o CMakeFiles\raylib_static.dir\models.c.s

libs/raylib/src/CMakeFiles/raylib_static.dir/raudio.c.obj: libs/raylib/src/CMakeFiles/raylib_static.dir/flags.make
libs/raylib/src/CMakeFiles/raylib_static.dir/raudio.c.obj: libs/raylib/src/CMakeFiles/raylib_static.dir/includes_C.rsp
libs/raylib/src/CMakeFiles/raylib_static.dir/raudio.c.obj: ../libs/raylib/src/raudio.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\marti\Documents\StringBeat\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object libs/raylib/src/CMakeFiles/raylib_static.dir/raudio.c.obj"
	cd /d C:\Users\marti\Documents\StringBeat\build\libs\raylib\src && C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\raylib_static.dir\raudio.c.obj   -c C:\Users\marti\Documents\StringBeat\libs\raylib\src\raudio.c

libs/raylib/src/CMakeFiles/raylib_static.dir/raudio.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/raylib_static.dir/raudio.c.i"
	cd /d C:\Users\marti\Documents\StringBeat\build\libs\raylib\src && C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\marti\Documents\StringBeat\libs\raylib\src\raudio.c > CMakeFiles\raylib_static.dir\raudio.c.i

libs/raylib/src/CMakeFiles/raylib_static.dir/raudio.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/raylib_static.dir/raudio.c.s"
	cd /d C:\Users\marti\Documents\StringBeat\build\libs\raylib\src && C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\marti\Documents\StringBeat\libs\raylib\src\raudio.c -o CMakeFiles\raylib_static.dir\raudio.c.s

libs/raylib/src/CMakeFiles/raylib_static.dir/shapes.c.obj: libs/raylib/src/CMakeFiles/raylib_static.dir/flags.make
libs/raylib/src/CMakeFiles/raylib_static.dir/shapes.c.obj: libs/raylib/src/CMakeFiles/raylib_static.dir/includes_C.rsp
libs/raylib/src/CMakeFiles/raylib_static.dir/shapes.c.obj: ../libs/raylib/src/shapes.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\marti\Documents\StringBeat\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object libs/raylib/src/CMakeFiles/raylib_static.dir/shapes.c.obj"
	cd /d C:\Users\marti\Documents\StringBeat\build\libs\raylib\src && C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\raylib_static.dir\shapes.c.obj   -c C:\Users\marti\Documents\StringBeat\libs\raylib\src\shapes.c

libs/raylib/src/CMakeFiles/raylib_static.dir/shapes.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/raylib_static.dir/shapes.c.i"
	cd /d C:\Users\marti\Documents\StringBeat\build\libs\raylib\src && C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\marti\Documents\StringBeat\libs\raylib\src\shapes.c > CMakeFiles\raylib_static.dir\shapes.c.i

libs/raylib/src/CMakeFiles/raylib_static.dir/shapes.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/raylib_static.dir/shapes.c.s"
	cd /d C:\Users\marti\Documents\StringBeat\build\libs\raylib\src && C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\marti\Documents\StringBeat\libs\raylib\src\shapes.c -o CMakeFiles\raylib_static.dir\shapes.c.s

libs/raylib/src/CMakeFiles/raylib_static.dir/text.c.obj: libs/raylib/src/CMakeFiles/raylib_static.dir/flags.make
libs/raylib/src/CMakeFiles/raylib_static.dir/text.c.obj: libs/raylib/src/CMakeFiles/raylib_static.dir/includes_C.rsp
libs/raylib/src/CMakeFiles/raylib_static.dir/text.c.obj: ../libs/raylib/src/text.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\marti\Documents\StringBeat\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object libs/raylib/src/CMakeFiles/raylib_static.dir/text.c.obj"
	cd /d C:\Users\marti\Documents\StringBeat\build\libs\raylib\src && C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\raylib_static.dir\text.c.obj   -c C:\Users\marti\Documents\StringBeat\libs\raylib\src\text.c

libs/raylib/src/CMakeFiles/raylib_static.dir/text.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/raylib_static.dir/text.c.i"
	cd /d C:\Users\marti\Documents\StringBeat\build\libs\raylib\src && C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\marti\Documents\StringBeat\libs\raylib\src\text.c > CMakeFiles\raylib_static.dir\text.c.i

libs/raylib/src/CMakeFiles/raylib_static.dir/text.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/raylib_static.dir/text.c.s"
	cd /d C:\Users\marti\Documents\StringBeat\build\libs\raylib\src && C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\marti\Documents\StringBeat\libs\raylib\src\text.c -o CMakeFiles\raylib_static.dir\text.c.s

libs/raylib/src/CMakeFiles/raylib_static.dir/textures.c.obj: libs/raylib/src/CMakeFiles/raylib_static.dir/flags.make
libs/raylib/src/CMakeFiles/raylib_static.dir/textures.c.obj: libs/raylib/src/CMakeFiles/raylib_static.dir/includes_C.rsp
libs/raylib/src/CMakeFiles/raylib_static.dir/textures.c.obj: ../libs/raylib/src/textures.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\marti\Documents\StringBeat\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object libs/raylib/src/CMakeFiles/raylib_static.dir/textures.c.obj"
	cd /d C:\Users\marti\Documents\StringBeat\build\libs\raylib\src && C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\raylib_static.dir\textures.c.obj   -c C:\Users\marti\Documents\StringBeat\libs\raylib\src\textures.c

libs/raylib/src/CMakeFiles/raylib_static.dir/textures.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/raylib_static.dir/textures.c.i"
	cd /d C:\Users\marti\Documents\StringBeat\build\libs\raylib\src && C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\marti\Documents\StringBeat\libs\raylib\src\textures.c > CMakeFiles\raylib_static.dir\textures.c.i

libs/raylib/src/CMakeFiles/raylib_static.dir/textures.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/raylib_static.dir/textures.c.s"
	cd /d C:\Users\marti\Documents\StringBeat\build\libs\raylib\src && C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\marti\Documents\StringBeat\libs\raylib\src\textures.c -o CMakeFiles\raylib_static.dir\textures.c.s

libs/raylib/src/CMakeFiles/raylib_static.dir/utils.c.obj: libs/raylib/src/CMakeFiles/raylib_static.dir/flags.make
libs/raylib/src/CMakeFiles/raylib_static.dir/utils.c.obj: libs/raylib/src/CMakeFiles/raylib_static.dir/includes_C.rsp
libs/raylib/src/CMakeFiles/raylib_static.dir/utils.c.obj: ../libs/raylib/src/utils.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\marti\Documents\StringBeat\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object libs/raylib/src/CMakeFiles/raylib_static.dir/utils.c.obj"
	cd /d C:\Users\marti\Documents\StringBeat\build\libs\raylib\src && C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\raylib_static.dir\utils.c.obj   -c C:\Users\marti\Documents\StringBeat\libs\raylib\src\utils.c

libs/raylib/src/CMakeFiles/raylib_static.dir/utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/raylib_static.dir/utils.c.i"
	cd /d C:\Users\marti\Documents\StringBeat\build\libs\raylib\src && C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\marti\Documents\StringBeat\libs\raylib\src\utils.c > CMakeFiles\raylib_static.dir\utils.c.i

libs/raylib/src/CMakeFiles/raylib_static.dir/utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/raylib_static.dir/utils.c.s"
	cd /d C:\Users\marti\Documents\StringBeat\build\libs\raylib\src && C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\marti\Documents\StringBeat\libs\raylib\src\utils.c -o CMakeFiles\raylib_static.dir\utils.c.s

# Object files for target raylib_static
raylib_static_OBJECTS = \
"CMakeFiles/raylib_static.dir/core.c.obj" \
"CMakeFiles/raylib_static.dir/models.c.obj" \
"CMakeFiles/raylib_static.dir/raudio.c.obj" \
"CMakeFiles/raylib_static.dir/shapes.c.obj" \
"CMakeFiles/raylib_static.dir/text.c.obj" \
"CMakeFiles/raylib_static.dir/textures.c.obj" \
"CMakeFiles/raylib_static.dir/utils.c.obj"

# External object files for target raylib_static
raylib_static_EXTERNAL_OBJECTS = \
"C:/Users/marti/Documents/StringBeat/build/libs/raylib/src/external/glfw/src/CMakeFiles/glfw_objlib.dir/context.c.obj" \
"C:/Users/marti/Documents/StringBeat/build/libs/raylib/src/external/glfw/src/CMakeFiles/glfw_objlib.dir/init.c.obj" \
"C:/Users/marti/Documents/StringBeat/build/libs/raylib/src/external/glfw/src/CMakeFiles/glfw_objlib.dir/input.c.obj" \
"C:/Users/marti/Documents/StringBeat/build/libs/raylib/src/external/glfw/src/CMakeFiles/glfw_objlib.dir/monitor.c.obj" \
"C:/Users/marti/Documents/StringBeat/build/libs/raylib/src/external/glfw/src/CMakeFiles/glfw_objlib.dir/vulkan.c.obj" \
"C:/Users/marti/Documents/StringBeat/build/libs/raylib/src/external/glfw/src/CMakeFiles/glfw_objlib.dir/window.c.obj" \
"C:/Users/marti/Documents/StringBeat/build/libs/raylib/src/external/glfw/src/CMakeFiles/glfw_objlib.dir/win32_init.c.obj" \
"C:/Users/marti/Documents/StringBeat/build/libs/raylib/src/external/glfw/src/CMakeFiles/glfw_objlib.dir/win32_joystick.c.obj" \
"C:/Users/marti/Documents/StringBeat/build/libs/raylib/src/external/glfw/src/CMakeFiles/glfw_objlib.dir/win32_monitor.c.obj" \
"C:/Users/marti/Documents/StringBeat/build/libs/raylib/src/external/glfw/src/CMakeFiles/glfw_objlib.dir/win32_time.c.obj" \
"C:/Users/marti/Documents/StringBeat/build/libs/raylib/src/external/glfw/src/CMakeFiles/glfw_objlib.dir/win32_thread.c.obj" \
"C:/Users/marti/Documents/StringBeat/build/libs/raylib/src/external/glfw/src/CMakeFiles/glfw_objlib.dir/win32_window.c.obj" \
"C:/Users/marti/Documents/StringBeat/build/libs/raylib/src/external/glfw/src/CMakeFiles/glfw_objlib.dir/wgl_context.c.obj" \
"C:/Users/marti/Documents/StringBeat/build/libs/raylib/src/external/glfw/src/CMakeFiles/glfw_objlib.dir/egl_context.c.obj" \
"C:/Users/marti/Documents/StringBeat/build/libs/raylib/src/external/glfw/src/CMakeFiles/glfw_objlib.dir/osmesa_context.c.obj"

libs/raylib/src/libraylib_static.a: libs/raylib/src/CMakeFiles/raylib_static.dir/core.c.obj
libs/raylib/src/libraylib_static.a: libs/raylib/src/CMakeFiles/raylib_static.dir/models.c.obj
libs/raylib/src/libraylib_static.a: libs/raylib/src/CMakeFiles/raylib_static.dir/raudio.c.obj
libs/raylib/src/libraylib_static.a: libs/raylib/src/CMakeFiles/raylib_static.dir/shapes.c.obj
libs/raylib/src/libraylib_static.a: libs/raylib/src/CMakeFiles/raylib_static.dir/text.c.obj
libs/raylib/src/libraylib_static.a: libs/raylib/src/CMakeFiles/raylib_static.dir/textures.c.obj
libs/raylib/src/libraylib_static.a: libs/raylib/src/CMakeFiles/raylib_static.dir/utils.c.obj
libs/raylib/src/libraylib_static.a: libs/raylib/src/external/glfw/src/CMakeFiles/glfw_objlib.dir/context.c.obj
libs/raylib/src/libraylib_static.a: libs/raylib/src/external/glfw/src/CMakeFiles/glfw_objlib.dir/init.c.obj
libs/raylib/src/libraylib_static.a: libs/raylib/src/external/glfw/src/CMakeFiles/glfw_objlib.dir/input.c.obj
libs/raylib/src/libraylib_static.a: libs/raylib/src/external/glfw/src/CMakeFiles/glfw_objlib.dir/monitor.c.obj
libs/raylib/src/libraylib_static.a: libs/raylib/src/external/glfw/src/CMakeFiles/glfw_objlib.dir/vulkan.c.obj
libs/raylib/src/libraylib_static.a: libs/raylib/src/external/glfw/src/CMakeFiles/glfw_objlib.dir/window.c.obj
libs/raylib/src/libraylib_static.a: libs/raylib/src/external/glfw/src/CMakeFiles/glfw_objlib.dir/win32_init.c.obj
libs/raylib/src/libraylib_static.a: libs/raylib/src/external/glfw/src/CMakeFiles/glfw_objlib.dir/win32_joystick.c.obj
libs/raylib/src/libraylib_static.a: libs/raylib/src/external/glfw/src/CMakeFiles/glfw_objlib.dir/win32_monitor.c.obj
libs/raylib/src/libraylib_static.a: libs/raylib/src/external/glfw/src/CMakeFiles/glfw_objlib.dir/win32_time.c.obj
libs/raylib/src/libraylib_static.a: libs/raylib/src/external/glfw/src/CMakeFiles/glfw_objlib.dir/win32_thread.c.obj
libs/raylib/src/libraylib_static.a: libs/raylib/src/external/glfw/src/CMakeFiles/glfw_objlib.dir/win32_window.c.obj
libs/raylib/src/libraylib_static.a: libs/raylib/src/external/glfw/src/CMakeFiles/glfw_objlib.dir/wgl_context.c.obj
libs/raylib/src/libraylib_static.a: libs/raylib/src/external/glfw/src/CMakeFiles/glfw_objlib.dir/egl_context.c.obj
libs/raylib/src/libraylib_static.a: libs/raylib/src/external/glfw/src/CMakeFiles/glfw_objlib.dir/osmesa_context.c.obj
libs/raylib/src/libraylib_static.a: libs/raylib/src/CMakeFiles/raylib_static.dir/build.make
libs/raylib/src/libraylib_static.a: libs/raylib/src/CMakeFiles/raylib_static.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\marti\Documents\StringBeat\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking C static library libraylib_static.a"
	cd /d C:\Users\marti\Documents\StringBeat\build\libs\raylib\src && $(CMAKE_COMMAND) -P CMakeFiles\raylib_static.dir\cmake_clean_target.cmake
	cd /d C:\Users\marti\Documents\StringBeat\build\libs\raylib\src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\raylib_static.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libs/raylib/src/CMakeFiles/raylib_static.dir/build: libs/raylib/src/libraylib_static.a

.PHONY : libs/raylib/src/CMakeFiles/raylib_static.dir/build

libs/raylib/src/CMakeFiles/raylib_static.dir/clean:
	cd /d C:\Users\marti\Documents\StringBeat\build\libs\raylib\src && $(CMAKE_COMMAND) -P CMakeFiles\raylib_static.dir\cmake_clean.cmake
.PHONY : libs/raylib/src/CMakeFiles/raylib_static.dir/clean

libs/raylib/src/CMakeFiles/raylib_static.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\marti\Documents\StringBeat C:\Users\marti\Documents\StringBeat\libs\raylib\src C:\Users\marti\Documents\StringBeat\build C:\Users\marti\Documents\StringBeat\build\libs\raylib\src C:\Users\marti\Documents\StringBeat\build\libs\raylib\src\CMakeFiles\raylib_static.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : libs/raylib/src/CMakeFiles/raylib_static.dir/depend

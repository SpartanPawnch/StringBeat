# CMake generated Testfile for 
# Source directory: C:/Users/marti/Documents/StringBeat/libs/raylib/src
# Build directory: C:/Users/marti/Documents/StringBeat/build/libs/raylib/src
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(pkg-config--static "C:/Users/marti/Documents/StringBeat/libs/raylib/src/../cmake/test-pkgconfig.sh" "--static")
set_tests_properties(pkg-config--static PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/marti/Documents/StringBeat/libs/raylib/src/CMakeLists.txt;180;add_test;C:/Users/marti/Documents/StringBeat/libs/raylib/src/CMakeLists.txt;0;")
subdirs("external/glfw")

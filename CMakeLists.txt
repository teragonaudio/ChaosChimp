project(BeatCounter)
cmake_minimum_required(VERSION 2.6)

# set the output destination
set(BEATCOUNTER_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/Builds/Linux/build/BeatCounter.so)

# create a custom target called build_scintilla that is part of ALL
# and will run each time you type make 
add_custom_target(build_BeatCounter ALL 
                  COMMAND ${CMAKE_MAKE_PROGRAM}
                  WORKING_DIRECTORY
                  ${CMAKE_CURRENT_SOURCE_DIR}/Builds/Linux
                  COMMENT "Building Introjucer generated Makefile")

# now create an imported static target
add_library(BeatCounter SHARED IMPORTED)
set_target_properties(BeatCounter PROPERTIES PREFIX "")
set_property(TARGET BeatCounter APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(BeatCounter PROPERTIES IMPORTED_LOCATION_NOCONFIG "${BEATCOUNTER_LIBRARY}")

# now you can use scintilla as if it were a regular cmake built target in your
# project
add_dependencies(BeatCounter build_BeatCounter)

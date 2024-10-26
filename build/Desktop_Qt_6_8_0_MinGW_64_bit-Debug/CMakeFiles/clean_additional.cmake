# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\strafe-helper_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\strafe-helper_autogen.dir\\ParseCache.txt"
  "strafe-helper_autogen"
  )
endif()

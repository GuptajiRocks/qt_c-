# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\apphelloWidget_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\apphelloWidget_autogen.dir\\ParseCache.txt"
  "apphelloWidget_autogen"
  )
endif()

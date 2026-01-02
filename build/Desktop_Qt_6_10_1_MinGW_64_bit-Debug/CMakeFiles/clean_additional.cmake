# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\applocaltuna_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\applocaltuna_autogen.dir\\ParseCache.txt"
  "applocaltuna_autogen"
  )
endif()

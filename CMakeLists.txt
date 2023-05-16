cmake_minimum_required(VERSION 3.2)

project(Bitcoin_miner)

include(src/CMakeLists.txt)
foreach(FILE ${FILES})
  set(srcFiles ${srcFiles} src/${FILE})
endforeach()

# Setup output directories.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "$<0:>${CMAKE_BINARY_DIR}/bin") # .exe and .dll
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "$<0:>${CMAKE_BINARY_DIR}/lib") # .so and .dylib
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "$<0:>${CMAKE_BINARY_DIR}/lib") # .lib and .a

add_executable(Bitcoin_miner ${srcFiles})
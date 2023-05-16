cmake_minimum_required(VERSION 3.2)

project(Bitcoin_miner)

include(src/CMakeLists.txt)
foreach(FILE ${FILES})
  set(srcFiles ${srcFiles} src/${FILE})
endforeach()

# Setup output directories.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

add_executable(Bitcoin_miner ${srcFiles})
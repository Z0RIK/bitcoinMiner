cmake_minimum_required(VERSION 3.2)

project(bitcoinMiner)

# Setup output directories.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "$<0:>${CMAKE_BINARY_DIR}/bin") # .exe and .dll
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "$<0:>${CMAKE_BINARY_DIR}/lib") # .so and .dylib
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "$<0:>${CMAKE_BINARY_DIR}/lib") # .lib and .a

add_executable(bitcoinMiner 
  ${CMAKE_CURRENT_SOURCE_DIR}/src/sha256.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/miner.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/utility.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/utility.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/miner.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/sha256.cpp)


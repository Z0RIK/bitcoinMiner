cmake_minimum_required(VERSION 3.2)

project(Bitcoin_miner)

include(src/CMakeLists.txt)
foreach(FILE ${FILES})
  set(srcFiles ${srcFiles} src/${FILE})
endforeach()

add_executable(Bitcoin_miner ${srcFiles})
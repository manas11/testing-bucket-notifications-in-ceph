cmake_minimum_required(VERSION 3.2)
option(BUILD_SHARED_LIBS "Build shared libraries" ON)

project(sns-publish)
set (CMAKE_CXX_STANDARD 11)

# Locate the aws sdk for c++ package.
find_package(AWSSDK REQUIRED COMPONENTS sns)

set(EXAMPLES "")

list(APPEND EXAMPLES "adapter")

# The executables to build.
foreach(EXAMPLE IN LISTS EXAMPLES)
  add_executable(${EXAMPLE} ${EXAMPLE}.cpp)
	target_link_libraries(${EXAMPLE} ${AWSSDK_LINK_LIBRARIES})
endforeach()

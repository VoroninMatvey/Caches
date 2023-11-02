cmake_minimum_required(VERSION 3.5)

project(Tests)

add_executable(tests src/main.cpp)
target_include_directories(tests PRIVATE include)

set_target_properties(
	tests PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON
)

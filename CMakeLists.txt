cmake_minimum_required(VERSION 3.5)

project(Caches)

add_executable(lfu lfu_cache/src/main.cpp)
add_executable(perfect perfect_cache/src/main.cpp)

target_include_directories(lfu PRIVATE lfu_cache/include)
target_include_directories(perfect PRIVATE perfect_cache/include)


set_target_properties(
	lfu perfect PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON
)

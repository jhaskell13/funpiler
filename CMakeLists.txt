cmake_minimum_required(VERSION 3.14)

find_program(CCACHE_PROGRAM CMAKE_CACHEFILE_DIR)
if(CCACHE_PROGRAM)
	set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

set(CMAKE_BUILD_TYPE Debug)

project(FUNCompiler C)

add_executable(
	compile
	src/main.c
)

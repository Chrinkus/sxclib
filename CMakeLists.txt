cmake_minimum_required(VERSION 3.16)

project(sxclib VERSION 0.1 LANGUAGES C)

set(CMAKE_C_STANDARD 99)

if(MSVC)
	add_compile_options(/W4)
else()
	add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include_directories(include)

add_subdirectory(src)

enable_testing()
add_subdirectory(test)

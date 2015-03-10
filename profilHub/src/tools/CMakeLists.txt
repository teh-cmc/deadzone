# TOOLS CMAKELISTS

cmake_minimum_required(VERSION 2.8.7)

add_library(ph_tools STATIC

	    src/profilers/c_profilers.cpp
	    src/profilers/c_profiler.cpp
	    src/profilers/c_profiler_valgrind.cpp
	    src/profilers/c_profiler_gprof.cpp
	    src/profilers/c_profiler_option.cpp

	    src/calltree/c_calltree.cpp
	    src/calltree/c_calltree_element.cpp)

include_directories(include include/profilers include/calltree ph_api/include)

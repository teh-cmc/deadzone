# .PH FRAMEWORK CMAKELISTS

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.7)

PROJECT(ph)

SET(EXECUTABLE_OUTPUT_PATH .)
SET(LIBRARY_OUTPUT_PATH libs)
SET(CMAKE_PROJECT_NAME_UT ${CMAKE_PROJECT_NAME}_ut)
SET(__CMAKE_FILES CMakeCache.txt CMakeFiles cmake_install.cmake Makefile)

#C flags
SET(CMAKE_C_FLAGS_DEBUG "-g3 -O0 -fno-inline -DD_ERRORS_ON -DD_DEBUG_ON")
SET(CMAKE_C_FLAGS_RELEASE "-O3")

#C++ flags
SET(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0 -fno-inline -DD_ERRORS_ON -DD_DEBUG_ON")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3")

SET(${CMAKE_PROJECT_NAME}_srcs
	 src/errors.c
	 src/exec.c
	 src/launcher.c
	 src/linked_list.c
	 src/ph_io.c
	 src/stack.c
	 src/strstuff.c
	 src/valgrind/exec.c
	 src/valgrind/parameters.c
	 src/valgrind/parsing.c
	 )

SET(${CMAKE_PROJECT_NAME_UT}_srcs
	    src/main.c
	    )

SET(objs)
FOREACH(src ${CMAKE_PROJECT_NAME}_srcs)
	LIST(APPEND objs CMakeFiles/${CMAKE_PROJECT_NAME}.dir/${src}.o)
ENDFOREACH()
FOREACH(src ${CMAKE_PROJECT_NAME_UT}_srcs)
	LIST(APPEND objs CMakeFiles/${CMAKE_PROJECT_NAME_UT}.dir/${src}.o)
ENDFOREACH()

SET(include_dirs include)
SET(lib_dirs libs)

#32/64 bits
IF (CMAKE_SIZEOF_VOID_P EQUAL 8)
ELSE ()
ENDIF ()

SET(libs xml2)

FIND_LIBRARY(XML2_LIB LIBRARY NAMES xml2 HINTS ${lib_dirs})
if (XML2_LIB)
	message(STATUS ${XML2_LIB})
else ()
	message(FATAL_ERROR "Missing library xml2")
endif ()
FIND_PACKAGE(Threads REQUIRED)
INCLUDE_DIRECTORIES(${include_dirs})
LINK_DIRECTORIES(${lib_dirs})

ADD_DEFINITIONS(-Wall -Werror -Wextra -Wshadow -Wno-error=address -Wno-error=shadow)

ADD_LIBRARY(${CMAKE_PROJECT_NAME} SHARED ${${CMAKE_PROJECT_NAME}_srcs})
TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME} ${libs} ${CMAKE_THREAD_LIBS_INIT})

ADD_EXECUTABLE(${CMAKE_PROJECT_NAME_UT} ${${CMAKE_PROJECT_NAME}_srcs} ${${CMAKE_PROJECT_NAME_UT}_srcs})
TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME_UT} ${libs} ${CMAKE_THREAD_LIBS_INIT})

IF (UNIX)
	#'make d', clears objects and executable
	ADD_CUSTOM_TARGET(d COMMENT "DISTCLEAN ${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_NAME_UT}")
	ADD_CUSTOM_COMMAND(COMMAND rm ARGS -rf ${objs} ${LIBRARY_OUTPUT_PATH}/lib${CMAKE_PROJECT_NAME}.so ${EXECUTABLE_OUTPUT_PATH}/${CMAKE_PROJECT_NAME_UT} TARGET d)

	#'make dd', clears objects and executable, clears CMake files
	ADD_CUSTOM_TARGET(dd COMMENT "ANNIHILATING ${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_NAME_UT}")
	ADD_CUSTOM_COMMAND(COMMAND make ARGS d TARGET dd)
	ADD_CUSTOM_COMMAND(COMMAND rm ARGS -rf ${__CMAKE_FILES} TARGET dd)

	#'make r', toggles gcc/g++ and release flags for 'make', clears objects and executable, rebuilds (6 TH)
	ADD_CUSTOM_TARGET(r COMMENT "RELEASE ${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_NAME_UT}")
	ADD_CUSTOM_COMMAND(COMMAND make ARGS dd TARGET r)
	ADD_CUSTOM_COMMAND(COMMAND cmake ARGS . -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_C_COMPILER=/usr/bin/gcc -DCMAKE_CXX_COMPILER=/usr/bin/g++ TARGET r)
	ADD_CUSTOM_COMMAND(COMMAND make ARGS -j6 TARGET r)

	#'make gd', toggles gcc/g++ and debug flags for 'make', clears objects and executable, rebuilds (6 TH)
	ADD_CUSTOM_TARGET(gd COMMENT "GCC/G++ DEBUG ${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_NAME_UT}")
	ADD_CUSTOM_COMMAND(COMMAND make ARGS dd TARGET gd)
	ADD_CUSTOM_COMMAND(COMMAND cmake ARGS . -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_C_COMPILER=/usr/bin/gcc -DCMAKE_CXX_COMPILER=/usr/bin/g++ TARGET gd)
	ADD_CUSTOM_COMMAND(COMMAND make ARGS -j6 TARGET gd)

	#'make cd', toggles clang/clang++ and debug flags for 'make', clears objects and executable, rebuilds (6 TH)
	ADD_CUSTOM_TARGET(cd COMMENT "CLANG/CLANG++ ${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_NAME_UT}")
	ADD_CUSTOM_COMMAND(COMMAND make ARGS dd TARGET cd)
	ADD_CUSTOM_COMMAND(COMMAND cmake ARGS . -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++ TARGET cd)
	ADD_CUSTOM_COMMAND(COMMAND make ARGS -j6 TARGET cd)
ENDIF ()

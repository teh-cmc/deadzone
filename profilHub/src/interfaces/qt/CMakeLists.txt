# QT INTERFACE CMAKELISTS

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.7)

PROJECT(profilHub)

SET(EXECUTABLE_OUTPUT_PATH .)
SET(__CMAKE_FILES CMakeCache.txt CMakeFiles cmake_install.cmake Makefile)

#C flags
SET(CMAKE_C_FLAGS_DEBUG "-g3 -O0 -fno-inline -DD_ERRORS_ON -DD_DEBUG_ON")
SET(CMAKE_C_FLAGS_RELEASE "-O3")

#C++ flags
SET(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0 -fno-inline -DD_ERRORS_ON -DD_DEBUG_ON")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3")

SET(srcs
	src/main.cpp
	src/c_application.cpp
	src/c_window.cpp
	src/c_tab.cpp
	src/c_tab_content.cpp
	src/c_tab_header.cpp
	src/c_tab_content_calltree.cpp
	src/c_tab_calltree.cpp
	src/c_tab_displayer.cpp
	src/c_tab_main.cpp
	src/c_tab_label.cpp
	src/c_tab_content_main.cpp
	src/c_central_widget.cpp
	src/c_warning_lister.cpp
	src/c_lister.cpp
	src/c_filter_lister.cpp
	src/c_warning.cpp
	src/c_search_area.cpp
	src/c_filters.cpp
	src/c_warnings.cpp
	src/c_search_bar.cpp
	src/c_profilers_infos.cpp
	src/c_listing_area.cpp
	src/c_launching_options.cpp
	src/c_exec_infos.cpp
	src/c_filter.cpp
	src/c_profiler.cpp
	src/c_img.cpp
	src/c_tab_callgraph.cpp
	src/c_tab_content_callgraph.cpp
	src/c_tab_graph.cpp
	src/c_tab_content_graph.cpp
	src/c_main_content.cpp
	src/c_generalTab.cpp
	src/c_calltree_item.cpp
	src/c_options_popup.cpp
	src/c_menubar.cpp
	src/c_output_infos.cpp
	src/c_output_option.cpp
	 )

SET(headers
	include/c_application.h
	include/c_window.h
	include/c_tab.h
	include/c_tab_content.h
	include/c_tab_header.h
	include/c_tab_calltree.h
	include/c_tab_content_calltree.h
	include/c_warning.h
	include/c_tab_displayer.h
	include/c_tab_main.h
	include/c_tab_label.h
	include/c_tab_content_main.h
	include/c_lister.h
	include/c_central_widget.h
	include/c_launching_options.h
	include/c_listing_area.h
	include/c_profilers_infos.h
	include/c_exec_infos.h
	include/c_warning_lister.h
	include/c_filters.h
	include/c_calltree_item.h
	include/c_warnings.h
	include/c_img.h
	include/c_filter.h
	include/c_profiler.h
	include/c_main_content.h
	include/c_tab_callgraph.h
	include/c_tab_content_callgraph.h
	include/c_tab_content_graph.h
	include/c_tab_graph.h
	include/c_filter_lister.h
	include/c_search_area.h
	include/c_menubar.h
	include/c_generalTab.h
	include/c_options_popup.h
	include/c_search_bar.h
	include/c_output_infos.h
	include/c_output_option.h
	    )
#Translation files
SET(TRANS
	fr.ts
)

SET(FILES_TO_TRANSLATE ${headers} ${srcs})

ADD_SUBDIRECTORY(tools)

SET(objs)
FOREACH(src ${srcs})
	LIST(APPEND objs CMakeFiles/${CMAKE_PROJECT_NAME}.dir/${src}.o)
ENDFOREACH()

SET(include_dirs tools include define ph/include)

#32/64 bits
IF (CMAKE_SIZEOF_VOID_P EQUAL 8)
ELSE ()
ENDIF ()

SET(libs ph_tools ph)
SET(lib_dirs tools ph/libs)

FIND_LIBRARY(PH_LIB LIBRARY NAMES ph HINTS ${lib_dirs})
if (PH_LIB)
	message(STATUS ${PH_LIB})
else ()
	message(FATAL_ERROR "Missing library libph")
endif ()
FIND_PACKAGE(Qt4 REQUIRED)
FIND_PACKAGE(Threads REQUIRED)
INCLUDE_DIRECTORIES(${include_dirs})
INCLUDE(${QT_USE_FILE})
LINK_DIRECTORIES(${lib_dirs})

QT4_WRAP_CPP(moc_headers ${headers})

ADD_DEFINITIONS(-Wall -Werror -Wextra -Wshadow ${QT_DEFINITIONS})

QT4_CREATE_TRANSLATION(QM ${FILES_TO_TRANSLATE} ${TRANS})
QT4_ADD_TRANSLATION(QM ${TRANS})

ADD_EXECUTABLE(${CMAKE_PROJECT_NAME} ${srcs} ${moc_headers} ${QM})

TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME} ${libs} ${CMAKE_THREAD_LIBS_INIT} ${QT_LIBRARIES})

IF (UNIX)
	#'make d', clears objects and executable
	ADD_CUSTOM_TARGET(d COMMENT "DISTCLEAN ${CMAKE_PROJECT_NAME}")
	ADD_CUSTOM_COMMAND(COMMAND rm ARGS -rf ${objs} ${EXECUTABLE_OUTPUT_PATH}/${CMAKE_PROJECT_NAME} TARGET d)

	#'make dd', clears objects and executable, clears CMake files
	ADD_CUSTOM_TARGET(dd COMMENT "ANNIHILATING ${CMAKE_PROJECT_NAME}")
	ADD_CUSTOM_COMMAND(COMMAND make ARGS d TARGET dd)
	ADD_CUSTOM_COMMAND(COMMAND rm ARGS -rf ${__CMAKE_FILES} TARGET dd)

	#'make r', toggles gcc/g++ and release flags for 'make', clears objects and executable, rebuilds (6 TH)
	ADD_CUSTOM_TARGET(r COMMENT "RELEASE ${CMAKE_PROJECT_NAME}")
	ADD_CUSTOM_COMMAND(COMMAND make ARGS dd TARGET r)
	ADD_CUSTOM_COMMAND(COMMAND cmake ARGS . -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_C_COMPILER=/usr/bin/gcc -DCMAKE_CXX_COMPILER=/usr/bin/g++ TARGET r)
	ADD_CUSTOM_COMMAND(COMMAND make ARGS -j6 TARGET r)

	#'make gd', toggles gcc/g++ and debug flags for 'make', clears objects and executable, rebuilds (6 TH)
	ADD_CUSTOM_TARGET(gd COMMENT "GCC/G++ DEBUG ${CMAKE_PROJECT_NAME}")
	ADD_CUSTOM_COMMAND(COMMAND make ARGS dd TARGET gd)
	ADD_CUSTOM_COMMAND(COMMAND cmake ARGS . -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_C_COMPILER=/usr/bin/gcc -DCMAKE_CXX_COMPILER=/usr/bin/g++ TARGET gd)
	ADD_CUSTOM_COMMAND(COMMAND make ARGS -j6 TARGET gd)

	#'make cd', toggles clang/clang++ and debug flags for 'make', clears objects and executable, rebuilds (6 TH)
	ADD_CUSTOM_TARGET(cd COMMENT "CLANG/CLANG++ ${CMAKE_PROJECT_NAME}")
	ADD_CUSTOM_COMMAND(COMMAND make ARGS dd TARGET cd)
	ADD_CUSTOM_COMMAND(COMMAND cmake ARGS . -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++ TARGET cd)
	ADD_CUSTOM_COMMAND(COMMAND make ARGS -j6 TARGET cd)
ENDIF ()

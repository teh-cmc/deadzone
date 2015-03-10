# NCURSES INTERFACE CMAKELISTS

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
    src/c_popup_text_zone.cpp
    src/c_function_graphic.cpp
    src/c_label_numeric.cpp
    src/c_text_zone.cpp
    src/c_graphic.cpp
    src/c_scroll_tool.cpp
    src/c_graph.cpp
    src/c_filter_indicator.cpp
    src/c_function_indicator.cpp
    src/c_indicator.cpp
    src/c_info_function.cpp
    src/c_popup_info_function.cpp
    src/c_function_calltree.cpp
    src/c_calltree.cpp
    src/c_select_tab_menu.cpp
    src/c_profiler_infos_menu.cpp
    src/c_profiler_menu.cpp
    src/c_init_secondary_item.cpp
    src/c_data_ui.cpp
    src/c_init_ui.cpp
    tools/src/profilers/c_profiler.cpp
    tools/src/profilers/c_profilers.cpp
    tools/src/profilers/c_profiler_gprof.cpp
    tools/src/profilers/c_profiler_option.cpp
    tools/src/profilers/c_profiler_valgrind.cpp
    src/c_data.cpp
    src/c_tab.cpp
    src/c_tab_manager.cpp
    src/c_label_alphanum.cpp
    src/c_label.cpp
    src/c_color.cpp
    src/c_error_manager.cpp
    src/c_popup_read_dir_action.cpp
    src/c_popup_err_msg.cpp
    src/c_popup.cpp
    src/c_popup_manager.cpp
    src/callbacks_labels.cpp
    src/callbacks_tabs.cpp
    src/callbacks_menus.cpp
    src/callbacks_buttons.cpp
    src/c_button.cpp
    src/c_menu_scroll.cpp
    src/c_menu_button.cpp
    src/c_menu.cpp
    src/c_state_bar.cpp
    src/c_magnetic_border.cpp
    src/c_env.cpp
    src/c_pos_dim.cpp
    src/c_dim.cpp
    src/c_pos.cpp
    src/c_zone.cpp
    src/c_toolbar.cpp
    src/c_container.cpp
    src/c_base_container.cpp
    src/c_ui.cpp
    src/c_event.cpp
    src/c_window.cpp
    src/c_ncurses.cpp
    src/main.cpp)

SET(objs)
FOREACH(src ${srcs})
	LIST(APPEND objs CMakeFiles/${CMAKE_PROJECT_NAME}.dir/${src}.o)
ENDFOREACH()

SET(include_dirs include tools/include tools/include/profilers ph/include)

#32/64 bits
IF (CMAKE_SIZEOF_VOID_P EQUAL 8)
ELSE ()
ENDIF ()

SET(libs ncurses menu ph)
SET(lib_dirs ph/libs)

FIND_LIBRARY(PH_LIB LIBRARY NAMES ph HINTS ${lib_dirs})
if (PH_LIB)
	message(STATUS ${PH_LIB})
else ()
	message(FATAL_ERROR "Missing library libph")
endif ()
FIND_PACKAGE(Threads REQUIRED)
INCLUDE_DIRECTORIES(${include_dirs})
LINK_DIRECTORIES(${lib_dirs})

ADD_DEFINITIONS(-Wall -Werror -Wextra -Wshadow)

ADD_EXECUTABLE(${CMAKE_PROJECT_NAME} ${srcs})
TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME} ${libs} ${CMAKE_THREAD_LIBS_INIT})

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

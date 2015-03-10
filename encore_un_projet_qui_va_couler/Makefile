###
 # Makefile - dependencies, build, unit tests
 # Copyright (C) 2014  Clement 'cmc' Rey <cr.rey.clement@gmail.com>
 #
 # This file is part of EUPQVC.
 #
 # EUPQVC is free software: you can redistribute it and/or modify
 # it under the terms of the GNU General Public License as published by
 # the Free Software Foundation, either version 3 of the License, or
 # (at your option) any later version.
 #
 # This program is distributed in the hope that it will be useful,
 # but WITHOUT ANY WARRANTY; without even the implied warranty of
 # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 # GNU General Public License for more details.
 #
 # You should have received a copy of the GNU General Public License
 # along with this program.  If not, see <http://www.gnu.org/licenses/>.
###

###############
### GENERAL ###
###############

# VARS #

TS			=	$(shell date "+%Y%M%d-%H%M")
OS			=	$(shell uname -s)
LIBS_PATH	:=	$(LD_LIBRARY_PATH)

ifeq ($(OS),Linux)
  NB_CORES = $(shell grep -c ^processor /proc/cpuinfo)
endif
ifeq ($(OS),Darwin)
  NB_CORES = $(shell sysctl -n hw.ncpu)
endif

# $(CC) defaults to `cc` if not set
ifeq ($(CC),cc)
  CC = gcc
endif

# RULES #

all: init-obj-dir init-tests-obj-dir all-depencendies build

help:
	@echo "General"
	@echo "======="
	@echo "all.....................: 'all-depencendies' then 'build'"
	@echo "help....................: shows this help"

	@echo ""

	@echo "Dependencies"
	@echo "============"
	@echo "all-depencendies........: downloads and builds every dependencies"
	@echo "download-dependencies...: downloads every dependencies"
	@echo "build-dependencies......: builds every dependencies"
	@echo "init-lib-dir............: creates lib directory"
	@echo "download-sdl............: downloads $(SDL_LIB)"
	@echo "build-sdl...............: builds $(SDL_LIB)"
	@echo "download-glib...........: downloads $(GLIB_LIB)"
	@echo "build-glib..............: builds $(GLIB_LIB)"

	@echo ""

	@echo "Build"
	@echo "====="
	@echo "init-obj-dir............: creates mandatory $(OBJ_DIR) directory"
	@echo "build...................: builds $(BIN) (set DEBUG to 0/1)"
	@echo "run.....................: 'build' then run $(BIN) with right env vars"
	@echo "clean...................: cleans object files"
	@echo "distclean...............: 'clean' and remove executable"
	@echo "rebuild.................: 'distclean' and 'build'"

	@echo ""

	@echo "Tests"
	@echo "====="
	@echo "init-tests-obj-dir......: creates mandatory $(TESTS_OBJ_DIR) directory"
	@echo "build-tests.............: builds $(TESTS_BIN)"
	@echo "run-tests...............: 'build-tests' then run $(TESTS_BIN) with right env vars"
	@echo "clean-tests.............: cleans object files"
	@echo "distclean-tests.........: 'clean-tests' and remove executable and logs"
	@echo "rebuild-tests...........: 'distclean-tests' and 'build-tests'"


####################
### DEPENDENCIES ###
####################

# VARS #

LIB_DIR				=	lib


SDL_VERSION			=	2.0.3
SDL_LIB				=	SDL2-$(SDL_VERSION)
SDL_LIB_DIR			=	$(LIB_DIR)/$(SDL_LIB)/build/.libs
SDL_CFLAGS			=	-I$(LIB_DIR)/$(SDL_LIB)/include
SDL_LDFLAGS			=	-L$(SDL_LIB_DIR) -lSDL2

DOWNLOAD_SDL_URL	=	"http://www.libsdl.org/release/$(SDL_LIB).tar.gz"

LIBS_PATH			:=	$(LIBS_PATH):$(SDL_LIB_DIR)


GLIB_VERSION		=	2.40
GLIB_LIB			=	glib-$(GLIB_VERSION).0
GLIB_LIB_DIR		=	$(LIB_DIR)/$(GLIB_LIB)/glib/.libs
GLIB_CFLAGS			=	-I$(LIB_DIR)/$(GLIB_LIB) -I$(LIB_DIR)/$(GLIB_LIB)/glib
GLIB_LDFLAGS		=	-L$(GLIB_LIB_DIR) -lglib-2.0

DOWNLOAD_GLIB_URL	=	"http://ftp.gnome.org/pub/gnome/sources/glib/$(GLIB_VERSION)/$(GLIB_LIB).tar.xz"

LIBS_PATH			:=	$(LIBS_PATH):$(GLIB_LIB_DIR)

# RULES #

all-depencendies: download-dependencies build-dependencies

rebuild-dependencies: clean-dependencies all-depencendies

download-dependencies: download-sdl download-glib

build-dependencies: build-sdl build-glib

clean-dependencies:
	@rm -rf $(LIB_DIR)

init-lib-dir:
	@if [ ! -d $(LIB_DIR) ]; then \
		mkdir -p $(LIB_DIR) ; \
	fi

download-sdl: init-lib-dir
	@if [ ! -d $(LIB_DIR)/$(SDL_LIB) ]; then \
		cd $(LIB_DIR) ; \
		wget $(DOWNLOAD_SDL_URL) -O $(SDL_LIB).tar.gz ; \
		tar xzf $(SDL_LIB).tar.gz ; \
		rm -rf $(SDL_LIB).tar.gz ; \
		cd $(SDL_LIB) ; \
	fi

build-sdl:
	@if [ -d $(LIB_DIR)/$(SDL_LIB) ]; then \
		cd $(LIB_DIR)/$(SDL_LIB) ; \
		if [ ! -f build/.libs/libSDL2.so ]; then \
			./configure ; \
			make -j$(NB_CORES) ; \
		fi ; \
	fi

download-glib: init-lib-dir
	@if [ ! -d $(LIB_DIR)/$(GLIB_LIB) ]; then \
		cd $(LIB_DIR) ; \
		wget $(DOWNLOAD_GLIB_URL) -O $(GLIB_LIB).tar.xz ; \
		tar xJf $(GLIB_LIB).tar.xz ; \
		rm -rf $(GLIB_LIB).tar.xz ; \
		cd $(GLIB_LIB) ; \
	fi

build-glib:
	@if [ -d $(LIB_DIR)/$(GLIB_LIB) ]; then \
		cd $(LIB_DIR)/$(GLIB_LIB) ; \
		if [ ! -f glib/.libs/libglib-2.0.so ]; then \
			./configure ; \
			make -j$(NB_CORES) ; \
		fi ; \
	fi


#############
### BUILD ###
#############

# VARS #

BIN				=	executable

INCLUDE_DIR		=	include
SRC_DIR			=	src
OBJ_DIR			=	$(SRC_DIR)/obj

CFLAGS			=	-I$(INCLUDE_DIR) $(SDL_CFLAGS) $(GLIB_CFLAGS)
LDFLAGS			=	$(SDL_LDFLAGS) $(GLIB_LDFLAGS)

ifeq ($(DEBUG),1)
	ECFLAGS		=	-std=gnu99 -O0 -g -W -Wall -rdynamic -DDEBUG
	ELDFLAGS	=
else
	ECFLAGS		=	-std=gnu99 -O3 -W -Wall -Werror
	ELDFLAGS	=
endif

CFLAGS			+=	$(ECFLAGS)
LDFLAGS			+=	$(ELDFLAGS)

INCLUDE			=	$(shell find $(INCLUDE_DIR) -name "*.h")
SRC				=	$(shell find $(SRC_DIR) -name "*.c")
ifeq ($(OS),Linux)
   OBJ			=	$(shell ls $(SRC) | sed -r "s|$(SRC_DIR)/(.*)\.c|$(OBJ_DIR)/\1.o|g")
endif
ifeq ($(OS),Darwin)
   OBJ			=	$(shell ls $(SRC) | sed -E "s|$(SRC_DIR)/(.*)\.c|$(OBJ_DIR)/\1.o|g")
endif

# RULES #

.PHONY: build run clean distclean rebuild

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE)
	$(CC) -c -o $@ $< $(CFLAGS)

init-obj-dir:
	@if [ ! -d $(OBJ_DIR) ]; then \
		mkdir -p $(OBJ_DIR) ; \
	fi

build: $(OBJ)
	$(CC) -o $(BIN) $^ $(CFLAGS) $(LDFLAGS)

run: build
	@LD_LIBRARY_PATH=$(LIBS_PATH) ./$(BIN)

clean:
	rm -f $(OBJ)

distclean: clean
	rm -f $(BIN)

rebuild: distclean build

#############
### TESTS ###
#############

# VARS #

TESTER				=	$(LIB_DIR)/$(GLIB_LIB)/glib/gtester
TESTER_DUMP_DIR		=	$(TESTS_DIR)/dumps
TESTER_FLAGS		=	--verbose -k -o=$(TESTER_DUMP_DIR)/tests-$(TS).xml

TESTS_BIN			=	run_tests

TESTS_DIR			=	tests
TESTS_INCLUDE_DIR	=	$(TESTS_DIR)/include
TESTS_SRC_DIR		=	$(TESTS_DIR)/src
TESTS_OBJ_DIR		=	$(TESTS_SRC_DIR)/obj

TESTS_CFLAGS		=	$(CFLAGS) -I$(TESTS_INCLUDE_DIR)
TESTS_LDFLAGS		=	$(LDFLAGS)

TESTS_INCLUDE		=	$(shell find $(TESTS_INCLUDE_DIR) -name "*.h")
TESTS_SRC			=	$(shell find $(TESTS_SRC_DIR) -name "*.c")
ifeq ($(OS),Linux)
   TESTS_OBJ		=	$(shell ls $(TESTS_SRC) | sed -r "s|$(TESTS_SRC_DIR)/(.*)\.c|$(TESTS_OBJ_DIR)/\1.o|g")
endif
ifeq ($(OS),Darwin)
   TESTS_OBJ		=	$(shell ls $(TESTS_SRC) | sed -E "s|$(TESTS_SRC_DIR)/(.*)\.c|$(TESTS_OBJ_DIR)/\1.o|g")
endif

# RULES #

.PHONY: build-tests run-tests clean-tests distclean-tests rebuild-tests

$(TESTS_OBJ_DIR)/%.o: $(TESTS_SRC_DIR)/%.c $(TESTS_INCLUDE)
	$(CC) -c -o $@ $< $(TESTS_CFLAGS)

init-tests-obj-dir:
	@if [ ! -d $(TESTS_OBJ_DIR) ]; then \
		mkdir -p $(TESTS_OBJ_DIR) ; \
	fi

build-tests: $(filter-out $(OBJ_DIR)/main.o, $(OBJ)) $(TESTS_OBJ)
	$(CC) -o $(TESTS_BIN) $^ $(TESTS_CFLAGS) $(TESTS_LDFLAGS)

run-tests: build-tests
	@if [ ! -d $(TESTER_DUMP_DIR) ]; then \
		mkdir -p $(TESTER_DUMP_DIR) ; \
	fi
	@LD_LIBRARY_PATH=$(LIBS_PATH) ./$(TESTER) $(TESTER_FLAGS) $(TESTS_BIN)

clean-tests:
	rm -f $(TESTS_OBJ)

distclean-tests: clean-tests
	rm -f $(TESTS_BIN)
	rm -rf $(TESTER_DUMP_DIR)

rebuild-tests: distclean-tests build-tests

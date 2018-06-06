#
# Copyright (c) 2018, Cong Nga Le. All rights reserved.
#
# This application used C++ version 11
#

PROGRAM := home_service

# collect all .cc source files
SOURCES = $(shell find src -type f -name '*.cc')

# collect all .o object files
OBJECTS = $(patsubst %.cc,%.o,$(SOURCES) $(PROGRAM).cc)

# include inc folders
INCLUDE_DIRS = -Iinc

# include lib folders
LIBRARY_DIRS = -Ilibs/tinyb/api -Ilibs/tinyb/include -Ilibs/mosquitto/lib -Ilibs/mosquitto/lib/cpp -Ilibs

# include -l
LDFLAGS = -ltinyb -lmosquittopp

# include -L
LIBS_DIR = -Llibs/tinyb/build/src -Llibs/mosquitto/lib/cpp

# build flags
CXXFLAGS = -std=c++11 -Wall -Wextra -W

# include -I
CPPFLAGS = $(INCLUDE_DIRS) $(LIBRARY_DIRS)

.PHONY: all clean tinyb tinyb_clean mosquitto mosquitto_clean

all: clean tinyb mosquitto  $(PROGRAM)

tinyb:
	@- rm libs/tinyb/build/CMakeCache.txt
	@- cd libs/tinyb/build; cmake .. ; cd -
	$(MAKE) -C libs/tinyb/build

tinyb_clean:
	$(MAKE) clean -C libs/tinyb/build

mosquitto:
	@- rm libs/mosquitto/CMakeCache.txt
	@- cd libs/mosquitto; cmake . ; cd -
	$(MAKE) -C libs/mosquitto

mosquitto_clean:
	$(MAKE) clean -C libs/mosquitto

$(PROGRAM): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LIBRARY_DIRS) $(LIBS_DIR) $(OBJECTS) -o $(PROGRAM) $(LDFLAGS)

clean:
	@- $(RM) $(PROGRAM)
	@- $(RM) $(OBJECTS)

very_clean: clean tinyb_clean mosquitto_clean

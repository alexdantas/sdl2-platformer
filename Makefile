# platformer Makefile

EXE = platformer

CFLAGS   = -g `sdl2-config --cflags`
CXXFLAGS = -Wall -Wextra -g `sdl2-config --cflags` -std=c++0x
LDFLAGS  = `sdl2-config --libs` \
           -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_gfx -lm

INCLUDE = -I"/usr/include/SDL"

# No need to edit below here

# All C++ source files of the project
CXXFILES   = $(shell find src -maxdepth 1 -type f -name '*.cpp')
CXXOBJECTS = $(CXXFILES:.cpp=.o)

SOURCES = $(CXXFILES)
OBJECTS = $(CXXOBJECTS)

ifdef V
MUTE =
VTAG = -v
else
MUTE = @
endif

###################################################################
# This is a Makefile progress indicator.
# I couldn't understand how it was done - simply copied here.

# BUILD is initially undefined
ifndef BUILD

# max equals 256 x's
sixteen := x x x x x x x x x x x x x x x x
MAX := $(foreach x,$(sixteen),$(sixteen))

# T estimates how many targets we are building by replacing BUILD with
# a special string
T := $(shell $(MAKE) -nrRf $(firstword $(MAKEFILE_LIST)) $(MAKECMDGOALS) \
            BUILD="COUNTTHIS" | grep -c "COUNTTHIS")

# N is the number of pending targets in base 1, well in fact, base x
# :-)
N := $(wordlist 1,$T,$(MAX))

# auto-decrementing counter that returns the number of pending targets
# in base 10
counter = $(words $N)$(eval N := $(wordlist 2,$(words $N),$N))

# BUILD is now defined to show the progress, this also avoids
# redefining T in loop
BUILD = @echo $(counter) of $(T)
endif
###################################################################

all: $(EXE)
	# Build successful!

$(EXE): $(OBJECTS)
	# Linking...
	$(MUTE)$(CXX) $(OBJECTS) -o $(EXE) $(LDFLAGS)

src/%.o: src/%.cpp
	# Compiling $<...
	$(MUTE)$(CXX) $(CXXFLAGS) $(INCLUDE) $< -c -o $@
	$(BUILD)

src/%.o: src/%.c
	# Compiling $<...
	$(MUTE)$(CC) $(CFLAGS) $(INCLUDE) $< -c -o $@

run: all
	$(MUTE)./$(EXE)

clean:
	# Cleaning...
	-$(MUTE)rm -f $(EXE) $(OBJECTS)

# Generates full documentation for the project
dox:
	$(MUTE)doxygen Doxyfile
	# Documentation generated!

doxclean:
	$(MUTE)rm -rf doc/html
	# Documentation cleaned!


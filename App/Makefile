########################
### IMACMAN Makefile ###
########################

#THE TARGET
TARGETNAME := ImagesGeneriques
TARGET := build/$(TARGETNAME)

# SETUP
CXX := g++
SRCDIR := .
SRCEXT := cpp
LIBDIR := libs

UNAME_S := $(shell uname -s)

# FIND ALL PROJECT SOURCES
ifeq ($(OS),Windows_NT)
SOURCES := $(shell tree $(SRCDIR) -type f -name "**.$(SRCEXT)" -not -path "./$(LIBDIR)/*")
else
SOURCES := $(shell find $(SRCDIR) -type f -name "**.$(SRCEXT)" -not -path "./$(LIBDIR)/*")
endif

OBJECTS := $(SOURCES:.$(SRCEXT)=.o)

# COMPILER FLAGS
GCCOPTIONS = -g -std=c++11 -Wall -pedantic #-O2 -pipe -fno-common -fno-strict-aliasing
CXXFLAGS := $(GCCOPTIONS) -I$(LIBDIR) -I.
LDLIBS = `pkg-config --libs freetype2` #`pkg-config --libs assimp`
LDFLAGS = `pkg-config --cflags freetype2` #`pkg-config --cflags assimp`
BOOSTLIBS = -lboost_filesystem -lboost_system

# OS-DEPENDANT COMPILER FLAGS
ifeq ($(OS),Windows_NT)

# Windows (cygwin)
LDLIBS +=  -lGLEW -lGL -lSDL2 -lSDL2_image `python-config --cflags`
LDFLAGS +=
PYTHONLIBS = `python-config --libs`
PYTHONFLAGS = `python-config --cflags`

else ifeq ($(UNAME_S),Darwin)

# OS X
LDLIBS += -framework OpenGL -framework SDL2 -framework SDL2_image -lGLEW
LDFLAGS +=
PYTHONLIBS = `python-config --libs`
PYTHONFLAGS = -I/System/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7 -fno-strict-aliasing -fno-common -dynamic -arch x86_64 -DENABLE_DTRACE -DMACOSX -DNDEBUG #-Wstrict-prototypes -Wshorten-64-to-32


# Linux (default)
else
LDLIBS +=-lGLEW -lGL -lSDL2 -lSDL2_image
LDFLAGS +=
PYTHONLIBS = `python-config --libs`
PYTHONFLAGS = `python-config --includes`

endif

LDLIBS += $(BOOSTLIBS) $(PYTHONLIBS)
LDFLAGS += $(PYTHONFLAGS)
CXXFLAGS += $(LDFLAGS)


# BUILD THE PROGRAM
$(TARGET): linker

$(info )
$(info ========================================)
$(info    COMPILING $(TARGETNAME) on $(UNAME_S))
$(info ========================================)

#SAY HELLO
#hello:

#LINK EVERYTHING
linker: $(OBJECTS)
	@echo "\n  Compiling ok!"
	@echo "\n========================================"
	@echo "   LINKING"
	@echo "========================================\n"
	@echo " Working... "; $(CXX) $^ -o $(TARGET) $(LDFLAGS) $(LDLIBS) $(OSLIB)
#    @echo "  Cleaning objects..."
#    @$(RM) -r $(OBJECTS)
	@echo "\n========================================"
	@echo "   $(TARGETNAME) successfully compiled!"
	@echo "   Type \"./$(TARGET)\" to launch $(TARGETNAME)"
	@echo "========================================\n"

# COMPILE THE SOURCES
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo "  $(CXX) $(CXXFLAGS) $(LDFLAGS) -c -o -MMD $@ $<"; $(CXX) $(CXXFLAGS) $(LDFLAGS) -c -o -MMD $@ $<
	@mkdir -p $(BUILDDIR)

# REMOVE ALL OBJECTS
clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(OBJECTS) $(TARGET)"; $(RM) -r $(OBJECTS) $(TARGET)

.PHONY: clean

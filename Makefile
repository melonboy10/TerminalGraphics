# Define the compiler to use
CC := g++
# Define compiler flags used in all builds
CFLAGS := -std=c++11 -Wall

# Define the archive tool
AR := ar
# Define archive flags
ARFLAGS := -cr

# Define compiler flags used in debug & release builds
DEBUGFLAGS := -g -O0 -D DEBUG
RELEASEFLAGS := -O3

# Define the name of the output library
LIBNAME := TerminalGraphics

# Define various directories
SRCDIR := src
SPLITDIR := split
INCLUDEDIR := include
OBJDIR := obj
DEPDIR := $(OBJDIR)/deps
RELEASEDIR := release

# Create build files in the release directory if that is the make target
ifeq ($(MAKECMDGOALS),release)
	EXC := $(RELEASEDIR)/$(EXC)
	OBJDIR := $(RELEASEDIR)/$(OBJDIR)
	DEPDIR := $(RELEASEDIR)/$(DEPDIR)
endif

# Define a recursive wildcard function to search for source files
# I got this function from https://stackoverflow.com/a/18258352
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2)$(filter $(subst *,%,$2),$d))

SPLITSRCS := $(call rwildcard,$(SRCDIR),*.h)
# Find source files using the recursive wildcard function
SRCS := $(patsubst $(SRCDIR)/%.h,%.cpp,$(SPLITSRCS))

$(info ${SRCS})

# Create a list of subdirectories so that the directory structure can be recreated in the object directory
SUBDIRECTORIES := $(sort $(patsubst %/,%,$(dir $(addprefix $(OBJDIR)/,$(SRCS))))) $(sort $(patsubst %/,%,$(dir $(addprefix $(DEPDIR)/,$(SRCS)))))

# Platform specific things go here
# Detection of platform and archetecture are from https://stackoverflow.com/a/12099167
ifeq ($(OS),Windows_NT)
	CFLAGS += -D WIN32
	
	LIB := $(LIBNAME).lib
	MKDIR = mkdir $(subst /,\,$@) # Forwardslashes need to be turned into backslashes because Windows is stupid
define CLEAN = # Here the if function is used to prevent an error caused by attempting to deleting a file that does not exist
$(if $(wildcard $(OBJDIR) $(RELEASEDIR)), rmdir /Q /S $(wildcard $(OBJDIR) $(RELEASEDIR)))
$(if $(wildcard $(LIB)), del $(wildcard $(LIB)))
endef # I can't indent here because make doesn't like it

	ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
		CFLAGS += -D AMD64 -m64 # Here the extra -m64 flag tells the compiler to compile for 64 bit
	else
		ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
			CFLAGS += -D AMD64 -m64 # Here the extra -m64 flag tells the compiler to compile for 64 bit
		endif
		ifeq ($(PROCESSOR_ARCHITECTURE),x86)
			CFLAGS += -D IA32
		endif
	endif
else
	LIB := lib$(LIBNAME).a
	MKDIR = mkdir -p $@
	# Here the if function is used to prevent an error caused by attempting to deleting a file that does not exist
	CLEAN = $(if $(wildcard $(OBJDIR) $(RELEASEDIR) $(LIB)), rm -rf $(wildcard $(OBJDIR) $(RELEASEDIR) $(LIB))) 
	
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		CFLAGS += -D LINUX
	endif
	ifeq ($(UNAME_S),Darwin)
		CFLAGS += -D OSX
	endif
	UNAME_P := $(shell uname -p)
	ifeq ($(UNAME_P),x86_64)
		CFLAGS += -D AMD64 -m64 # Here the extra -m64 flag tells the compiler to compile for 64 bit
	endif
	ifneq ($(filter %86,$(UNAME_P)),)
		CFLAGS += -D IA32
	endif
	ifneq ($(filter arm%,$(UNAME_P)),)
		CFLAGS += -D ARM
	endif
endif

# Compiler flags to create dependency makefile (so things can be recompiled if header files are modified)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

# Compile command
COMPILE = $(CC) $(DEPFLAGS) $(CFLAGS) -c

# Declare phony targets (targets without a corresponding file)
.PHONY: all debug release clean split

# Run the program every time make is run
all: release

# Apply debug compiler flags & build library
debug: CFLAGS += $(DEBUGFLAGS)
debug: $(LIB)

# Apply release compiler flags & build library
release: CFLAGS += $(RELEASEFLAGS)
release: $(LIB)

# Delete all build files
clean:
	$(CLEAN)

split:
	> $(INCLUDEDIR)/$(LIBNAME).h
	@for file in $(SPLITSRCS); do \
		./split_file.sh $$file $(SPLITDIR) $(INCLUDEDIR)/$(LIBNAME).h; \

# Create all neccessary directories
$(SUBDIRECTORIES):
	$(MKDIR)

# The following is from https://make.mad-scientist.net/papers/advanced-auto-dependency-generation

# Create Library Archive
$(LIB): $(SRCS:%.cpp=$(OBJDIR)/%.o)
	$(AR) $(ARFLAGS) $@ $^

# Compile all object files
$(OBJDIR)/%.o : $(SPLITDIR)/%.cpp $(DEPDIR)/%.d | $(SUBDIRECTORIES)
	$(COMPILE) $(OUTPUT_OPTION) $<

# Split header files into source files
$(SPLITDIR)/%.cpp: $(SRCDIR)/%.h | $(SUBDIRECTORIES)
	./split_file.sh $< $(SPLITDIR) $(INCLUDEDIR)/$(LIBNAME).h

# Include all dependency files (so make knows which files to recompile when a header file is updated)
DEPFILES := $(SRCS:%.cpp=$(DEPDIR)/%.d)
$(DEPFILES):
include $(wildcard $(DEPFILES))
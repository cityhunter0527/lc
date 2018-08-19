#
# Defines
#
CC       = g++
CPPFLAGS = -std=c++11 -g -c -Wall -Werror -fpic
INCLUDES = -I./
ECHO     = echo
RM       = rm -f
MV       = mv
LIBPATH  = ~/lib
VPATH    = ../

SRCS = BSTUtil.cpp

OBJS  = $(SRCS:.cpp=.o)
DEPEND_SRCS = $(SRCS)

EXE = libBSTUtil.so

%.o: %.cpp
	$(CC) $(CPPFLAGS) $(INCLUDES) -c $<  

# The following rule should be put ahead of the ruls of building dependencies. 
# Otherwise it will only build all target without building dependencies for each source file.
all: $(EXE)

#
# Build dependency for each file.
# Patten Rules.
#
%.d: %.cpp
	@$(ECHO) "Building Dependencies for $<"; \
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

# Using '-include' instead of 'include' to avoid warning of 'Could not find..' at first run 
ifdef DEPEND_SRCS
-include $(DEPEND_SRCS:.cpp=.d)
endif

$(EXE): $(OBJS)
	@echo "Linking......"
	$(CC) -shared -o $(EXE) $(OBJS)

clean: 
	$(RM) $(OBJS)
	$(RM) $(EXE)
	$(RM) *.d

install:
	$(RM) $(LIBPATH)/$(EXE)
	$(MV) $(EXE) $(LIBPATH)

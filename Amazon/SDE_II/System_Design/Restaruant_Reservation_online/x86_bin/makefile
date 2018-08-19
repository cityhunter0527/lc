#
# Defines
#
CC       = g++
CPPFLAGS   = -std=c++11
INCLUDES = -I./
ECHO     = echo
RM = rm -f

VPATH = ../

ifdef DEBUG
CPPFLAGS += -g
endif

SRCS = solution.cpp \
	   resMgr.cpp

OBJS  = $(SRCS:.cpp=.o)
DEPEND_SRCS = $(SRCS)
LIBOPTS = 

EXE = resMgr

%.o: %.cpp
	$(CC) $(CPPFLAGS) $(INCLUDES) -c $<  

#The following rule should be put ahead of the ruls of building dependencies. 
#Otherwise it will only build all target without building dependencies for each source file.
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
	@echo "*********************************************************************************"
	@echo "********************************** resMgr *************************************"
	@echo "*********************************************************************************"
	@echo "Linking......"
	$(CC) $(CPPFLAGS) -o $(EXE) $(OBJS) $(LIBOPTS)

clean: 
	$(RM) $(OBJS)
	$(RM) $(EXE)
	$(RM) *.d


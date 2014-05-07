# ==============================================================================
# Cumulonimbus Makefile
#
# Copyright: Staff 42 Entertainment LTDA ME © 2013
# Author: Douglas M. de Freitas
# ==============================================================================

#colors
NC		:= \e[0m
Bold	:= \e[1m

Black	:= \e[0;30m
Blue	:= \e[0;34m
Green	:= \e[0;32m
Cyan	:= \e[0;36m
Red		:= \e[0;31m
Purple	:= \e[0;35m
Brown	:= \e[0;33m
LGray	:= \e[0;37m

DGray	:= \e[1;30m
LBlue	:= \e[1;34m
LGreen	:= \e[1;32m
LCyan	:= \e[1;36m
LRed	:= \e[1;31m
LPurple	:= \e[1;35m
Yellow	:= \e[1;33m
White	:= \e[1;37m

#Tools
CC := gcc
CPP := g++
ECHO := /bin/echo -e
CAT  := cat
RM   := rm

# Working directories
OUTPUT_DIR := dist
BUILD_DIR := build
SOURCE_DIR := source
DOC_DIR := doc

DEPENDENCIES_SOURCE_DIR := $(TYPHOON_ROOT)/dependencies/gcc/source

# Compiler configurations
CFLAGS := -Wall -fPIC -Wno-unused-local-typedefs -Wno-unused-variable -Wno-pointer-arith
CPPFLAGS := -std=c++11 -Wall -fPIC -Wno-unused-local-typedefs -Wno-unused-variable -Wno-pointer-arith
LDFLAGS := -Wl,-rpath,. -Wl,-rpath,./lib -Wl,-rpath-link,.

CDEFS := -DCUMULONIMBUS_EXPORTS -DGLEW_STATIC -D_CRT_SECURE_NO_WARNINGS
CPPDEFS := -DCUMULONIMBUS_EXPORTS -DGLEW_STATIC -D_CRT_SECURE_NO_WARNINGS

INCLUDE_DIR := -I./include -I$(TYPHOON_ROOT)/dependencies/gcc/include -I$(TYPHOON_ROOT)/dependencies/gcc/include/freetype2
LIBS_DIR := -L$(TYPHOON_ROOT)/dependencies/gcc/lib
 
LIBS := -lboost_locale -lfreetype -lGLEW -lphysfs -lpng -lz -ldl -lX11 -pthread

# Sources c++
CPPSOURCES := $(wildcard $(SOURCE_DIR)/*.cpp)
CPPSOURCES += $(wildcard $(SOURCE_DIR)/base/*.cpp)
CPPSOURCES += $(wildcard $(SOURCE_DIR)/data/*.cpp)
CPPSOURCES += $(wildcard $(SOURCE_DIR)/math/*.cpp)
CPPSOURCES += $(wildcard $(SOURCE_DIR)/window/linux/*.cpp)

# Sources c
CSOURCES := $(wildcard $(SOURCE_DIR)/*.c)
CSOURCES += $(wildcard $(SOURCE_DIR)/base/*.c)
CSOURCES += $(wildcard $(SOURCE_DIR)/data/*.c)
CSOURCES += $(wildcard $(SOURCE_DIR)/math/*.c)
CSOURCES += $(wildcard $(SOURCE_DIR)/window/linux/*.c)

# Dependencies Sources
DEPCPPSOURCES := $(wildcard $(DEPENDENCIES_SOURCE_DIR)/*.cpp)
DEPCSOURCES += $(wildcard $(DEPENDENCIES_SOURCE_DIR)/*.c)

# Objects
OBJECTS := $(patsubst $(SOURCE_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(CPPSOURCES))
OBJECTS += $(patsubst $(SOURCE_DIR)/%.c,$(BUILD_DIR)/%.o,$(CSOURCES))
OBJECTS += $(patsubst $(DEPENDENCIES_SOURCE_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(DEPCPPSOURCES))
OBJECTS += $(patsubst $(DEPENDENCIES_SOURCE_DIR)/%.c,$(BUILD_DIR)/%.o,$(DEPCSOURCES))

# ==============================================================================

#$(info ================================================================================)
#$(info Sources: $(CPPSOURCES))
#$(info Sources: $(CSOURCES))
#$(info Objects: $(OBJECTS))
#$(info Objects: $(OBJECTS:.o=.d))
#$(info ================================================================================)
#$(info )

# ==============================================================================
# link
all: dir $(OBJECTS)
	@$(ECHO) -n "$(LBlue)[LD]$(NC) $(BUILD_DIR)/libcumulonimbus.so ... "
	@$(CPP) $(LDFLAGS) $(OBJECTS) -shared $(CPPFLAGS) $(LIBS_DIR) $(LIBS) -o $(OUTPUT_DIR)/libcumulonimbus.so 2> temp.log || touch temp.errors
	@if test -e temp.errors; then $(ECHO) "$(LRed)[Error]$(NC)" && $(CAT) temp.log; elif test -s temp.log; then $(ECHO) "$(Yellow)[Warning]$(NC)" && $(CAT) temp.log; else $(ECHO) "$(LGreen)[Done]$(NC)"; fi;
	@if test -e temp.errors; then $(RM) -f temp.errors temp.log && exit 1; fi;
	@$(ECHO) "$(LGreen)[Build complete!]$(NC)"

# create build directories
dir:
	@mkdir -p $(OUTPUT_DIR)
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/base
	@mkdir -p $(BUILD_DIR)/data
	@mkdir -p $(BUILD_DIR)/math
	@mkdir -p $(BUILD_DIR)/window
	@mkdir -p $(BUILD_DIR)/window/linux
	@mkdir -p $(DOC_DIR)

# pull in dependency info for *existing* .o files
-include $(OBJECTS:.o=.d)

# compile c++ files
$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	@$(ECHO) -n "$(LBlue)[C++]$(NC) $*.o ... "
	@$(CPP) -c $(CPPFLAGS) $(CPPDEFS) $(INCLUDE_DIR) $(SOURCE_DIR)/$*.cpp -o $(BUILD_DIR)/$*.o 2> temp.log || touch temp.errors
	@if test -e temp.errors; then $(ECHO) "$(LRed)[Error]$(NC)" && $(CAT) temp.log; elif test -s temp.log; then $(ECHO) "$(Yellow)[Warning]$(NC)" && $(CAT) temp.log; else $(ECHO) "$(LGreen)[Done]$(NC)"; fi;
	@if test -e temp.errors; then $(RM) -f temp.errors temp.log && exit 1; fi;
	@$(CPP) -MM $(CPPFLAGS) $(CPPDEFS) $(INCLUDE_DIR) $(SOURCE_DIR)/$*.cpp -MT $(BUILD_DIR)/$*.o -MF $(BUILD_DIR)/$*.d

# compile c files
$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	@$(ECHO) -n "$(LBlue)[C]$(NC) $*.o ... "
	@$(CC) -c $(CFLAGS) $(CDEFS) $(INCLUDE_DIR) $(SOURCE_DIR)/$*.c -o $(BUILD_DIR)/$*.o 2> temp.log || touch temp.errors
	@if test -e temp.errors; then $(ECHO) "$(LRed)[Error]$(NC)" && $(CAT) temp.log; elif test -s temp.log; then $(ECHO) "$(Yellow)[Warning]$(NC)" && $(CAT) temp.log; else $(ECHO) "$(LGreen)[Done]$(NC)"; fi;
	@if test -e temp.errors; then $(RM) -f temp.errors temp.log && exit 1; fi;
	@$(CC) -MM $(CFLAGS) $(CDEFS) $(INCLUDE_DIR) $(SOURCE_DIR)/$*.c -MT $(BUILD_DIR)/$*.o -MF $(BUILD_DIR)/$*.d

# compile c++ dependencies files
$(BUILD_DIR)/%.o: $(DEPENDENCIES_SOURCE_DIR)/%.cpp
	@$(ECHO) -n "$(LBlue)[Dep. C++]$(NC) $*.o ... "
	@$(CPP) -c $(CPPFLAGS) $(CPPDEFS) $(INCLUDE_DIR) $(DEPENDENCIES_SOURCE_DIR)/$*.cpp -o $(BUILD_DIR)/$*.o 2> temp.log || touch temp.errors
	@if test -e temp.errors; then $(ECHO) "$(LRed)[Error]$(NC)" && $(CAT) temp.log; elif test -s temp.log; then $(ECHO) "$(Yellow)[Warning]$(NC)" && $(CAT) temp.log; else $(ECHO) "$(LGreen)[Done]$(NC)"; fi;
	@if test -e temp.errors; then $(RM) -f temp.errors temp.log && exit 1; fi;

# compile c dependencies files
$(BUILD_DIR)/%.o: $(DEPENDENCIES_SOURCE_DIR)/%.c
	@$(ECHO) -n "$(LBlue)[Dep. C]$(NC) $*.o ... "
	@$(CC) -c $(CFLAGS) $(CDEFS) $(INCLUDE_DIR) $(DEPENDENCIES_SOURCE_DIR)/$*.c -o $(BUILD_DIR)/$*.o 2> temp.log || touch temp.errors
	@if test -e temp.errors; then $(ECHO) "$(LRed)[Error]$(NC)" && $(CAT) temp.log; elif test -s temp.log; then $(ECHO) "$(Yellow)[Warning]$(NC)" && $(CAT) temp.log; else $(ECHO) "$(LGreen)[Done]$(NC)"; fi;
	@if test -e temp.errors; then $(RM) -f temp.errors temp.log && exit 1; fi;

# remove compilation products
.PHONY : clean
clean:
	@$(ECHO) -n "Cleaning ... "
	@$(RM) -f $(OUTPUT_DIR)/libcumulonimbus.so
	@$(RM) -f $(BUILD_DIR)/*.o $(BUILD_DIR)/*.d
	@$(RM) -f $(BUILD_DIR)/base/*.o $(BUILD_DIR)/base/*.d
	@$(RM) -f $(BUILD_DIR)/data/*.o $(BUILD_DIR)/data/*.d
	@$(RM) -f $(BUILD_DIR)/math/*.o $(BUILD_DIR)/math/*.d
	@$(RM) -f -r $(DOC_DIR)/*
	@$(RM) -rf $(OUTPUT_DIR)
	@$(RM) -rf $(BUILD_DIR)
	@$(RM) -rf $(DOC_DIR)
	@$(ECHO) "$(Green)$(Bold)[Done]$(NC)"

.PHONY : doc
doc:
	@$(ECHO) Building documentation
	@doxygen ./doxygen/cumulonimbus.doxyfile

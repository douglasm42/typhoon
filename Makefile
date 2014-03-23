# ==============================================================================
# Cumulonimbus Makefile
#
# Copyright: Staff 42 Entertainment LTDA ME © 2013
# Author: Douglas M. de Freitas
# ==============================================================================

# Working directories
OUTPUT_DIR := dist
BUILD_DIR := build
SOURCE_DIR := source
DOC_DIR := doc

# Compiler configurations
CC := gcc
CPP := g++

CFLAGS := -Wall -fPIC -Wno-unused-local-typedefs -Wno-unused-variable -Wno-pointer-arith
CPPFLAGS := -std=c++11 -Wall -fPIC -Wno-unused-local-typedefs -Wno-unused-variable -Wno-pointer-arith
LDFLAGS := -Wl,-rpath,. -Wl,-rpath,./lib -Wl,-rpath-link,.

CDEFS := -DCUMULONIMBUS_EXPORTS -DGLEW_STATIC -D_CRT_SECURE_NO_WARNINGS
CPPDEFS := -DCUMULONIMBUS_EXPORTS -DGLEW_STATIC -D_CRT_SECURE_NO_WARNINGS

INCLUDE_DIR := -I./include -I$(TYPHOON_ROOT)/dependencies/gcc/include -I$(TYPHOON_ROOT)/dependencies/gcc/include/freetype2
LIBS_DIR := -L$(TYPHOON_ROOT)/dependencies/gcc/lib
 
LIBS := -lboost_system -lboost_locale -lfreetype -lGLEW -lphysfs -lpng -lz -pthread

# Sources
SOURCES := $(wildcard $(SOURCE_DIR)/*.cpp)
SOURCES += $(wildcard $(SOURCE_DIR)/base/*.cpp)
SOURCES += $(wildcard $(SOURCE_DIR)/data/*.cpp)
SOURCES += $(wildcard $(SOURCE_DIR)/math/*.cpp)

# Objects
OBJECTS := $(patsubst $(SOURCE_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

# ==============================================================================

#$(info ================================================================================)
#$(info Sources: $(SOURCES))
#$(info Objects: $(OBJECTS))
#$(info ================================================================================)
#$(info )

# ==============================================================================
# link
all: dir $(OBJECTS)
	@echo [LD] $(BUILD_DIR)/libcumulonimbus.so
	@echo [LD] $(LIBS)
	@$(CPP) $(LDFLAGS) $(OBJECTS) -shared $(CPPFLAGS) $(LIBS_DIR) $(LIBS) -o $(OUTPUT_DIR)/libcumulonimbus.so

# create build directories
dir:
	@mkdir -p $(OUTPUT_DIR)
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/base
	@mkdir -p $(BUILD_DIR)/data
	@mkdir -p $(BUILD_DIR)/math
	@mkdir -p $(DOC_DIR)

# pull in dependency info for *existing* .o files
-include $(OBJECTS:.o=.d)

# compile and generate dependency info
$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	@echo [CPP] $*.o
	@$(CPP) -c $(CPPFLAGS) $(CPPDEFS) $(INCLUDE_DIR) $(SOURCE_DIR)/$*.cpp -o $(BUILD_DIR)/$*.o
	@$(CPP) -MM $(CPPFLAGS) $(CPPDEFS) $(INCLUDE_DIR) $(SOURCE_DIR)/$*.cpp -MF $(BUILD_DIR)/$*.d

# remove compilation products
.PHONY : clean
clean:
	@echo Cleaning...
	@rm -f $(OUTPUT_DIR)/libcumulonimbus.so
	@rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/*.d
	@rm -f $(BUILD_DIR)/base/*.o $(BUILD_DIR)/base/*.d
	@rm -f $(BUILD_DIR)/data/*.o $(BUILD_DIR)/data/*.d
	@rm -f $(BUILD_DIR)/math/*.o $(BUILD_DIR)/math/*.d
	@rm -f -r $(DOC_DIR)/*
	@rm -rf $(OUTPUT_DIR)
	@rm -rf $(BUILD_DIR)
	@rm -rf $(DOC_DIR)

.PHONY : doc
doc:
	@echo Building documentation
	@doxygen ./doxygen/cumulonimbus.doxyfile

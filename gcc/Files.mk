# Sources c++
CPPSOURCES := $(wildcard $(SOURCE_DIR)/*.cpp)
CPPSOURCES += $(wildcard $(SOURCE_DIR)/base/*.cpp)
CPPSOURCES += $(wildcard $(SOURCE_DIR)/data/*.cpp)
CPPSOURCES += $(wildcard $(SOURCE_DIR)/math/*.cpp)
CPPSOURCES += $(wildcard $(SOURCE_DIR)/video/linux/*.cpp)

# Sources c
CSOURCES := $(wildcard $(SOURCE_DIR)/*.c)
CSOURCES += $(wildcard $(SOURCE_DIR)/base/*.c)
CSOURCES += $(wildcard $(SOURCE_DIR)/data/*.c)
CSOURCES += $(wildcard $(SOURCE_DIR)/math/*.c)
CSOURCES += $(wildcard $(SOURCE_DIR)/video/linux/*.c)

# Dependencies Sources
DEPCPPSOURCES := $(wildcard $(DEPENDENCIES_SOURCE_DIR)/*.cpp)
DEPCSOURCES += $(wildcard $(DEPENDENCIES_SOURCE_DIR)/*.c)

# Objects
OBJECTS := $(patsubst $(SOURCE_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(CPPSOURCES))
OBJECTS += $(patsubst $(SOURCE_DIR)/%.c,$(BUILD_DIR)/%.o,$(CSOURCES))
OBJECTS += $(patsubst $(DEPENDENCIES_SOURCE_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(DEPCPPSOURCES))
OBJECTS += $(patsubst $(DEPENDENCIES_SOURCE_DIR)/%.c,$(BUILD_DIR)/%.o,$(DEPCSOURCES))

# Test sources
TESTSOURCES := $(wildcard $(TEST_DIR)/*.cpp)

# Test executables
TESTEXE := $(patsubst $(TEST_DIR)/%.cpp,$(OUTPUT_DIR)/test/%,$(TESTSOURCES))
RUNTESTEXE := $(patsubst $(TEST_DIR)/%.cpp,test.%,$(TESTSOURCES))


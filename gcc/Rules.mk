# link
all: cumulonimbus
	@$(ECHO) "$(LGreen)[Build complete!]$(NC)"

cumulonimbus: dir $(OUTPUT_DIR)/libcumulonimbus.so
	
$(OUTPUT_DIR)/libcumulonimbus.so: $(OBJECTS)
	@$(ECHO) -n "$(LBlue)[LD]$(NC) $(BUILD_DIR)/libcumulonimbus.so ... "
	@$(CPP) $(LDFLAGS) $(OBJECTS) -shared $(CPPFLAGS) $(LIBS_DIR) $(LIBS) -o $(OUTPUT_DIR)/libcumulonimbus.so 2> temp.log || touch temp.errors
	@if test -e temp.errors; then $(ECHO) "$(LRed)[Error]$(NC)" && $(CAT) temp.log; elif test -s temp.log; then $(ECHO) "$(Yellow)[Warning]$(NC)" && $(CAT) temp.log; else $(ECHO) "$(LGreen)[Done]$(NC)"; fi;
	@if test -e temp.errors; then $(RM) -f temp.errors temp.log && exit 1; fi;

# create build directories
dir:
	@mkdir -p $(OUTPUT_DIR)
	@mkdir -p $(OUTPUT_DIR)/test
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/base
	@mkdir -p $(BUILD_DIR)/data
	@mkdir -p $(BUILD_DIR)/math
	@mkdir -p $(BUILD_DIR)/video
	@mkdir -p $(BUILD_DIR)/video/linux
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
	@$(RM) -rf $(OUTPUT_DIR)
	@$(RM) -rf $(BUILD_DIR)
	@$(ECHO) "$(Green)$(Bold)[Done]$(NC)"

.PHONY : doc
doc:
	@$(ECHO) Building documentation
	@doxygen ./doxygen/cumulonimbus.doxyfile


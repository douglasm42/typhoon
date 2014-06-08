test: $(TESTEXE) $(RUNTESTEXE)

# compile tests
$(OUTPUT_DIR)/test/%: cumulonimbus $(TEST_DIR)/%.cpp
	@$(ECHO) -n "$(LBlue)[Test C++]$(NC) $* ... "
	@$(CPP) $(TEST_LDFLAGS) $(TEST_CPPFLAGS) $(TEST_INCLUDE_DIR) $(TEST_DIR)/$*.cpp $(TEST_CPPFLAGS) $(TEST_LIBS_DIR) $(TEST_LIBS) -o $(OUTPUT_DIR)/test/$* 2> temp.log || touch temp.errors
	@if test -e temp.errors; then $(ECHO) "$(LRed)[Error]$(NC)" && $(CAT) temp.log; elif test -s temp.log; then $(ECHO) "$(Yellow)[Warning]$(NC)" && $(CAT) temp.log; else $(ECHO) "$(LGreen)[Done]$(NC)"; fi;
	@if test -e temp.errors; then $(RM) -f temp.errors temp.log && exit 1; else $(RM) -f temp.errors temp.log; fi;

# run tests
test.%: $(OUTPUT_DIR)/test/%
	@$(ECHO) -n "$(LBlue)[Running]$(NC) $* ... "
	@cd $(TEST_ROOT_DIR); if ../$(OUTPUT_DIR)/test/$* > ../temp.log; then $(ECHO) "$(LGreen)[Pass]$(NC)"; else $(ECHO) "$(LRed)[Fail]$(NC)" && $(CAT) ../temp.log; fi;
	@$(RM) -f temp.log


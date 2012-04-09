# All Target
all: heap_test

# Tool invocations
heap_test: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++  -o"heap_test" heap_test.cpp Node.cpp
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-rm -fr Node.o heap_test.o heap_test
	-@echo ' '

.PHONY: all clean dependents


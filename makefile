flags = -Wno-write-strings
compiler = g++

# All Target
all: heap_test

# Tool invocations
heap_test: heap_test.cpp Node.o debug_print.o
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	$(compiler) $(flags) -o"heap_test" heap_test.cpp Node.o debug_print.o
	@echo 'Finished building target: $@'
	@echo ' '

debug_print.o: debug_print.cpp debug_print.h
	$(compiler) $(flags) -c debug_print.cpp

tree_test: tree_test.cpp Node.o Tree.o
	$(compiler) $(flags) -o "tree_test" tree_test.cpp Tree.o Node.o debug_print.cpp

Tree.o: Tree.h Tree.cpp Node.o
	$(compiler) $(flags) -c Tree.cpp Node.o debug_print.cpp

Node.o: Node.h Node.cpp
	$(compiler) $(flags) -c Node.cpp debug_print.cpp


# Other Targets
clean:
	-rm -fr Node.o heap_test.o heap_test
	-@echo ' '

.PHONY: all clean dependents


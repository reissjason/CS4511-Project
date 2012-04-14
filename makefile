flags = -Wno-write-strings
compiler = g++

# All Target
all: heap_test

# Tool invocations
heap_test: heap_test.cpp debug_print.o Heap.h Node.h
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	$(compiler) $(flags) -o"heap_test" heap_test.cpp debug_print.o
	@echo 'Finished building target: $@'
	@echo ' '

debug_print.o: debug_print.cpp debug_print.h
	$(compiler) $(flags) -c debug_print.cpp

tree_test: tree_test.cpp Node.h Tree.h
	$(compiler) $(flags) -o "tree_test" tree_test.cpp debug_print.cpp

pkmn:	pkmn.cpp pkmn.h attack.o
	g++ -c pkmn.cpp -o pkmn.o

attack:	attack.cpp attack.h
	g++ -c attack.cpp -o attack.o


# Other Targets
clean:
	-rm -fr *.o tree_test heap_test
	-@echo ' '

.PHONY: all clean dependents


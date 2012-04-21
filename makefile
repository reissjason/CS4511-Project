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

pokeman_test: pokeman_test.cpp tinyAttack.o pokeman.o
	$(compiler) $(flags) -o pokeman_test pokeman_test.cpp tinyAttack.o pokeman.o

pokeman.o: pokeman.cpp Pokeman.h
	$(compiler) $(flags) -c pokemon.cpp

minimax_test: minimax.cpp minimax_test.cpp
	$(compiler) $(flags) minimax_test.cpp minimax.cpp debug_print.cpp -o minimax_test

tinyAttack.o: tinyAttack.cpp TinyAttack.h
	g++ -c tinyAttack.cpp

# Other Targets
clean:
	-rm -fr *.o *_test
	-@echo ' '

.PHONY: all clean dependents


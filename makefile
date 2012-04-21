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

tiny_test: pokeman tinyattack state
	$(compiler) $(flags) -o"tiny_test" tiny_test.cpp Pokeman.o TinyAttack.o State.o

pokeman: Pokeman.cpp Pokeman.h tinyattack
	g++ -c Pokeman.cpp -o Pokeman.o

tinyattack: TinyAttack.cpp TinyAttack.h
	g++ -c TinyAttack.cpp -o TinyAttack.o

state: State.cpp State.h pokeman
	g++ -c State.cpp -o State.o
state_tree_test: state tree_test state_tree_test.cpp
	$(compiler) $(flags) -o"state_tree_test" state_tree_test.cpp debug_print.cpp State.o Pokeman.o TinyAttack.o

# Other Targets
clean:
	-rm -fr *.o tree_test heap_test tiny_test state_tree_test
	-@echo ' '

.PHONY: all clean dependents


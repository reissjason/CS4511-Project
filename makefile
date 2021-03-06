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
	$(compiler) $(flags) -c pkmn.cpp -o pkmn.o

attack:	attack.cpp attack.h
	$(compiler) $(flags) -c attack.cpp -o attack.o

pokeman_test: pokeman_test.cpp tinyAttack.o pokeman.o debug_print.o
	$(compiler) $(flags) -o pokeman_test pokeman_test.cpp tinyAttack.o pokeman.o debug_print.o

pokeman.o: pokeman.cpp Pokeman.h
	$(compiler) $(flags) -c pokeman.cpp

minimax_test: minimax.h minimax_test.cpp Tree.h Node.h
	$(compiler) $(flags) minimax_test.cpp debug_print.cpp -o minimax_test

tinyAttack.o: tinyAttack.cpp TinyAttack.h
	$(compiler) $(flags) -c tinyAttack.cpp

tiny_attack_test: tiny_attack_test.cpp tinyAttack.o debug_print.o
	$(compiler) $(flags) -o"tiny_attack_test" tiny_attack_test.cpp tinyAttack.o debug_print.o

tiny_test: pokeman tinyattack state
	$(compiler) $(flags) -o"tiny_test" tiny_test.cpp pokeman.o tinyAttack.o State.o

pokeman: pokeman.cpp Pokeman.h tinyattack
	$(compiler) $(flags) -c pokeman.cpp -o pokeman.o

tinyattack: tinyAttack.cpp TinyAttack.h
	$(compiler) $(flags) -c tinyAttack.cpp -o tinyAttack.o

state: State.cpp State.h pokeman
	$(compiler) $(flags) -c State.cpp -o State.o

state_test: state state_test.cpp pokeman.o debug_print.o
	$(compiler) $(flags) -o"state_test" state_test.cpp debug_print.o State.o pokeman.o tinyAttack.o

state_tree_test: state tree_test state_tree_test.cpp pokeman tinyattack
	$(compiler) $(flags) -o"state_tree_test" state_tree_test.cpp debug_print.cpp State.o pokeman.o tinyAttack.o

turn: Turn.cpp Turn.h state
	$(compiler) $(flags) -c Turn.cpp -o Turn.o

turn_test: turn_test.cpp turn turn_minimax.cpp 
	$(compiler) $(flags) -o"turn_test" turn_test.cpp debug_print.cpp turn_minimax.cpp State.o pokeman.o tinyAttack.o Turn.o 

ui: turn ui.cpp debug_print.o
	$(compiler) $(flags) -o"go" ui.cpp debug_print.o turn_minimax.cpp State.o pokeman.o tinyAttack.o Turn.o

battle.o: battle.cpp battle.h
	$(compiler) $(flags) -c battle.cpp

minimax_game: minimax_game.cpp pkmn attack.o battle.o type.o
	g++ minimax_game.cpp type.cpp pokeman.cpp battle.cpp Turn.cpp State.cpp tinyAttack.cpp team.cpp list.cpp debug_print.cpp turn_minimax.cpp -o minimax_game -w	

minimax_game2: minimax_game_2.cpp pkmn attack.o battle.o type.o
	g++ minimax_game_2.cpp type.cpp pokeman.cpp battle.cpp Turn.cpp State.cpp tinyAttack.cpp attack_minimax.cpp team.cpp list.cpp debug_print.cpp turn_minimax.cpp -o minimax_game2 -w -lrt	


random_game: minimax_game.cpp pkmn attack.o battle.o type.o
	g++ random_game.cpp type.cpp pokeman.cpp battle.cpp Turn.cpp State.cpp tinyAttack.cpp team.cpp list.cpp debug_print.cpp -o random_game -w	

# Other Targets
clean:
	-rm -fr *.o *_test *.out.txt minimax_game random_game minimax_game2 temp_results* temp_team_results processed_output*

.PHONY: all clean dependents


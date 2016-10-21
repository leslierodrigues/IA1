CC = gcc
CXX = g++
OPT = -std=c++11 -g -Wall -O3 -Wno-unused-function -Wno-unused-variable
PSVNOPT = --state_map --abstraction --backwards_moves --history_len=1

psvn2c_core.c:
	cp ../psvn-for-ci5437/src/psvn2c_core.c ./psvn2c_core.c

psvn2c_state_map.c:
	cp ../psvn-for-ci5437/src/psvn2c_state_map.c ./psvn2c_state_map.c

psvn2c_abstraction.c:
	cp ../psvn-for-ci5437/src/psvn2c_abstraction.c ./psvn2c_abstraction.c

%.c: ../Problemas/%.psvn psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	../psvn-for-ci5437/bin/psvn2c $(PSVNOPT) --name=$(*F) < $< > $@
	rm -f ./psvn2c_core.c  ./psvn2c_abstraction.c

.PRECIOUS: %.c

%.a_star.gap: %.c a_star.cpp heuristica_gap.cpp
	$(CXX) $(OPT) a_star.cpp  -include $< -include heuristica_gap.cpp -o $@
	rm -f $*.c

%.a_star.manhattan: %.c a_star.cpp heuristica_manhattan.cpp
	$(CXX) $(OPT) a_star.cpp  -include $< -include heuristica_manhattan.cpp -o $@
	rm -f $*.c

%.ida_star.gap: %.c ida_star.cpp heuristica_gap.cpp
	$(CXX) $(OPT) ida_star.cpp  -include $< -include heuristica_gap.cpp -o $@
	rm -f $*.c

%.ida_star.manhattan: %.c ida_star.cpp heuristica_manhattan.cpp
	$(CXX) $(OPT) ida_star.cpp  -include $< -include heuristica_manhattan.cpp -o $@
	rm -f $*.c

%.a_star_pdb: %.c a_star_pdb.cpp
	$(CXX) $(OPT) a_star_pdb.cpp  -include $< -o $@
	rm -f $*.c

%.ida_star_pdb: %.c ida_star_pdb.cpp
	$(CXX) $(OPT) ida_star_pdb.cpp  -include $< -o $@
	rm -f $*.c


%.succ: %.c ../../psvn-for-ci5437/global/succ.c
	$(CC) $(OPT) ../../psvn-for-ci5437/global/succ.c -include $< -o $@
	rm -f $*.c

%.dist: %.c ../../psvn-for-ci5437/global/dist.cpps
	$(CXX) $(OPT) ../../psvn-for-ci5437/global/dist.cpp -include $< -o $@
	rm -f $*.c

%.distSummary: %.c ../../psvn-for-ci5437/global/distSummary.cpp
	$(CXX) $(OPT) ../../psvn-for-ci5437/global/distSummary.cpp -include $< -o $@
	rm -f $*.c

%.calculadorHeuristicas: %.c calculadorHeuristicas.cpp
	$(CXX) $(OPT) calculadorHeuristicas.cpp -include $< -o $@
	rm -f $*.c



.PHONY: clean
clean:
	rm -fr *.ida_star_pdb *.a_star.manhattan *.a_star.gap *.ida_star.manhattan *.ida_star.gap *.a_star_pbd *.a_star_gap *.succ *.dist *.distSummary psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c *.dSYM *.o *~

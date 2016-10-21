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

%.wida.gap: %.c wida.cpp heuristica_gap.cpp
	$(CXX) $(OPT) wida.cpp  -include $< -include heuristica_gap.cpp -o $@
	rm -f $*.c

%.wida.manhattan: %.c wida.cpp heuristica_manhattan.cpp
	$(CXX) $(OPT) wida.cpp  -include $< -include heuristica_manhattan.cpp -o $@
	rm -f $*.c

%.wida_pdb: %.c wida_pdb.cpp
	$(CXX) $(OPT) wida_pdb.cpp  -include $< -o $@
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

.PHONY: clean
clean:
	rm -fr *.wida.manhattan *.wida.gap *.wida_pdb *.succ *.dist *.distSummary psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c *.dSYM *.o *~

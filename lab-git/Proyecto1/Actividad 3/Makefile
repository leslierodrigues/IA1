CC = gcc
CXX = g++
OPT = -std=c++11 -g -Wall -O3 -Wno-unused-function -Wno-unused-variable
PSVNOPT = --no_state_map --no_abstraction --backwards_moves --history_len=2

psvn2c_core.c:
	cp ../psvn-for-ci5437/src/psvn2c_core.c ./psvn2c_core.c

psvn2c_state_map.c:
	cp ../psvn-for-ci5437/src/psvn2c_state_map.c ./psvn2c_state_map.c

psvn2c_abstraction.c:
	cp ../psvn-for-ci5437/src/psvn2c_abstraction.c ./psvn2c_abstraction.c

%.c: ../Problemas/%.psvn psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	../psvn-for-ci5437/bin/psvn2c $(PSVNOPT) --name=$(*F) < $< > $@
	rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c

.PRECIOUS: %.c

%.iter_deepening: %.c iter_deepening.cpp
	$(CXX) $(OPT) iter_deepening.cpp -include $< -o $@
	rm -rf $*.c


%.succ: %.c ../../psvn-for-ci5437/global/succ.c
	$(CC) $(OPT) ../../psvn-for-ci5437/global/succ.c -include $< -o $@
	rm -f $*.c

%.dist: %.c ../../psvn-for-ci5437/global/dist.cpp
	$(CXX) $(OPT) ../../psvn-for-ci5437/global/dist.cpp -include $< -o $@
	rm -f $*.c

%.distSummary: %.c ../../psvn-for-ci5437/global/distSummary.cpp
	$(CXX) $(OPT) ../../psvn-for-ci5437/global/distSummary.cpp -include $< -o $@
	rm -f $*.c

.PHONY: clean
clean:
	rm -fr *.dfs *.succ *.iter_deepening *.dist *.distSummary psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c *.dSYM *.o *~

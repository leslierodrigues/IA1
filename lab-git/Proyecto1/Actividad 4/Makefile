CC = gcc
CXX = g++
OPT = -g -Wall -O3 -Wno-unused-function -Wno-unused-variable
PSVNOPT = --no_state_map --no_abstraction --backwards_moves --history_len=1

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

%.prueba: %.c prueba.cpp
	$(CXX) $(OPT) prueba.cpp  -include $< -o $@
	


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
	rm -fr *.prueba *.succ *.dist *.distSummary psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c *.dSYM *.o *~

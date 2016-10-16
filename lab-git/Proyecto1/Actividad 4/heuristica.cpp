#include <cstdio>
#include <iostream>

using namespace std;

unsigned int heuristic(state_t state){
    
    unsigned int number_not_adjacent = 0;
    int gap;
    for(unsigned int i=0; i<sizeof(state.vars)/sizeof(state.vars[0]) -1; i++){
        
        gap = state.vars[i] - state.vars[i+1]; 
        if ((gap < -1) || (gap > 1)){
            number_not_adjacent++;
        }
        
    }
    
    return number_not_adjacent;
}

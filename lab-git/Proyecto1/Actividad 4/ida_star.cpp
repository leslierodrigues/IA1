#include <iostream>
#include <ctime>
#include <cstdio>
#include <queue>
#include <map>
#include <climits>
#include "psvn2c_state_map.c"
#include "heuristica.cpp"

using namespace std;

long long generated_states;


// Estructutura que se almacena en la cola de prioridades
struct node{
	state_t s;
	unsigned int g;
	unsigned int h;
	unsigned int history;
};

struct par{
	node *n;
	unsigned int f;
};

struct node ida_star(state_t *);

struct par bounded_a(node, unsigned int,state_map_t *);


int main(){
	
	state_t start; 
	string state_string; // Almacena el estado dado por el usuario
	int result; // Valor retornado por la función
	int goalID;
	
	//map <state_t,int> m; //mapea un estado con su prioridad
	
	cout << "Introduzca el estado del problema: " << endl;
	
	getline(cin,state_string);
	if (read_state(state_string.c_str(),&start) == -1){

		cout << "No pudimos transformar tu input a un estado" << endl;
		cout << "Puede que este en formato incorrecto." << endl;

		int goalID;
		first_goal_state(&start,&goalID);

		cout << "La representacion del estado goal del problema es la siguiente" << endl;
		print_state(stdout,&start);
		cout << endl;
		return 0;
	}
	
	generated_states = 0;
	
	clock_t begin = clock();
	
	struct node nodo_result = ida_star(&start);
	result = nodo_result.g;

	clock_t end = clock();

	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	double gen_per_sec = double(generated_states)/elapsed_secs;

	cout << "algorithm, heuristic, domain, instance, cost, h0, generated, time, gen_per_sec " << endl;

	cout << " A*, gap, pancake28,\"" << state_string << "\", " << result << ", " << heuristic(&start);
	cout << ", " << generated_states << ", "  << elapsed_secs << ", ";
	cout << gen_per_sec << endl;
	
	return 0;
}


struct node ida_star(state_t *start){
    unsigned int b = heuristic(start);
    struct node n;
    n.s = *start;
    n.g=0;
    n.h=b;
    n.history = init_history;
    struct par p;
    state_map_t *stateMap = new_state_map();
    while(true){
        p = bounded_a(n, b, stateMap);
        if (p.n) {return *(p.n);}
        b = p.f;
    }
}

struct par bounded_a(node n, unsigned int b, state_map_t *stateMap){
    unsigned int f = n.g + n.h;
    if (f > b) {par p; p.n = NULL; p.f=f;return p;}
    if (is_goal(&(n.s))) {par p; p.n=&n;p.f=n.g;return p;}
    
    unsigned int t = UINT_MAX;
    int ruleID, new_hist;
    ruleid_iterator_t iter;
    state_map_add(stateMap,&(n.s),n.g);
    state_t hijo_estado;
    state_t current_state = n.s;
    
    init_fwd_iter(&iter,&current_state);
    struct node hijo;
    struct par p;
    while((ruleID = next_ruleid( &iter )) >= 0) {
        
        if (!fwd_rule_valid_for_history(n.history,ruleID)) {continue;}
        
        new_hist = next_fwd_history(n.history,ruleID);;
        
        apply_fwd_rule(ruleID, &current_state, &hijo_estado);
        generated_states++;
        hijo.history = new_hist;
        hijo.s = hijo_estado;
        hijo.g = n.g + 1;
        hijo.h = heuristic(&hijo_estado);
        state_map_add(stateMap,&hijo_estado,hijo.g);
        p = bounded_a(hijo,b, stateMap);
        if (p.n) {return p;}
        t = (t < p.f) ? t : p.f;
    }
    p.n = NULL;
    p.f = t;
    return p;
}



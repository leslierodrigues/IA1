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

int a_star(state_t*, unsigned int (*heuristica)(state_t));



// Estructutura que se almacena en la cola de prioridades
struct node{
    int priority;
    state_t s;
};

// Se modifica el operador para que la estructura node sea ordenable
bool operator<(const node &a,const node &b) {
return a.priority<b.priority;

}

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
	
	result = a_star(&start, &heuristic);

	clock_t end = clock();

	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	double gen_per_sec = double(generated_states)/elapsed_secs;

	cout << "algorithm, heuristic, domain, instance, cost, h0, generated, time, gen_per_sec " << endl;

	cout << " A*, gap, pancake28,\"" << state_string << "\", " << result << ", " << heuristic(start);
	cout << ", " << generated_states << ", "  << elapsed_secs << ", ";
	cout << gen_per_sec << endl;
    
    return 0;
}

int a_star(state_t *start, unsigned int (*heuristica)(state_t)){
    
	if (is_goal(start)) return 0;
	
	state_map_t *stateMap = new_state_map(); // Map con clave un estado y valor un entero 

    priority_queue<node> q; // Cola de prioridad
    
    struct node n;
    n.priority = 0; // Se calula la prioridad 
    n.s = *start;   // Se almacena el estado 
    
    state_map_add(stateMap,start,0); // Se mapea el nodo con la prioridad
    q.push(n); // Se inserta en la cola
    
    while (!q.empty()){
        n = q.top(); //Se guarda el primer elemento de la cola
        q.pop(); // Se desencola 
        state_t state = n.s; // Se almacena el estado desencolado
       
        // Eliminación de duplicados retardado
    if (n.priority < *state_map_get(stateMap,&state)){
            state_map_add(stateMap,&state,n.priority); //Se modifica la prioridad del estado en el Map
            if (is_goal(&state)) return n.priority; 
            
            int aux;
	        int ruleID, new_hist;
	        state_t child;
	        ruleid_iterator_t iter;

	        init_fwd_iter(&iter,&state);
	        //Expansión de nodos
	        while((ruleID = next_ruleid( &iter )) >= 0) {

		        if (!fwd_rule_valid_for_history(history,ruleID)) continue;

		        //if (cost + 1 >= max_cost) return -1;
		        
		        new_hist = next_fwd_history(history,ruleID);

		        apply_fwd_rule(ruleID, &state, &child);
		        generated_states++;

		        // Chequeamos si el nuevo hijo es un goal.
		        if (is_goal(&child)) return n.priority + 1;
                
                unsigned int h = heuristica(child);
                
                if (h < UINT_MAX-1) {
                    struct node nodoHijo;
                    nodoHijo.priority = *state_map_get(stateMap,&state) + get_fwd_rule_cost( ruleID ) + h;
                    nodoHijo.s = child;
                    state_map_add(stateMap,&child,nodoHijo.priority);
                    q.push(nodoHijo);
                }
                
		        //aux = dfs(&child,cost+1,max_cost,new_hist);

		        //if (aux != -1) return aux;
	        }
        }
       
    }
    
    return -1;
}

//1 2 3 4 6 16 11 10 5 8 7 9 14 12 15 13

#include <iostream>
#include <ctime>
#include <cstdio>
#include <queue>
#include <map>
#include <climits>

using namespace std;

long long generated_states;

int a_star(state_t*);
int heuristic(state_t*);

// Estructutura que se almacena en la cola de prioridades
struct node{
	int priority;
	state_t s;
	int cost;
	int history;
};

// Se modifica el operador para que la estructura node sea ordenable
bool operator<(const node &a,const node &b) {
return a.priority>b.priority;

}

state_map_t * grupo1, *grupo2, *grupo3;
abstraction_t *abs1, *abs2, *abs3;

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
	
	abs1 = read_abstraction_from_file("Abstracciones/PDB1/grupo1.abst");
	abs2 = read_abstraction_from_file("Abstracciones/PDB1/grupo2.abst");
	abs3 = read_abstraction_from_file("Abstracciones/PDB1/grupo3.abst");


	FILE* faux = fopen("Abstracciones/PDB1/grupo1.pdb", "r");
	grupo1 = read_state_map(faux);
	fclose(faux);

	faux = fopen("Abstracciones/PDB1/grupo2.pdb", "r");
	grupo2 = read_state_map(faux);
	fclose(faux);

	faux = fopen("Abstracciones/PDB1/grupo3.pdb", "r");
	grupo3 = read_state_map(faux);
	fclose(faux);

	clock_t begin = clock();
	
	result = a_star(&start);

	clock_t end = clock();

	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	double gen_per_sec = double(generated_states)/elapsed_secs;

	cout << "algorithm, heuristic, domain, instance, cost, h0, generated, time, gen_per_sec " << endl;

	cout << " A*, PDB5+5+5, 15puzzle,\"" << state_string << "\", " << result << ", " << heuristic(&start);
	cout << ", " << generated_states << ", "  << elapsed_secs << ", ";
	cout << gen_per_sec << endl;
	
	return 0;
}

int a_star(state_t *start){

	state_t child,current_state;
	unsigned int h;
	int cost, history;
	int ruleID, new_hist;
	ruleid_iterator_t iter;
	int *aux;

	if (is_goal(start)) return 0;
	
	state_map_t *stateMap = new_state_map(); // Map con clave un estado y valor un entero 

	priority_queue<node> q; // Cola de prioridad
	
	struct node n;
	n.priority = heuristic(start); // Se calula la prioridad
	n.cost = 0;
	n.history = init_history;
	n.s = *start;   // Se almacena el estado 
	
	//state_map_add(stateMap,start,1); // Se mapea el nodo con la prioridad
	q.push(n); // Se inserta en la cola
	
	while (!q.empty()){
		n = q.top(); //Se guarda el primer elemento de la cola
		q.pop(); // Se desencola 
		current_state = n.s; // Se almacena el estado desencolado

		init_fwd_iter(&iter,&current_state);
		//Expansión de nodos
		while((ruleID = next_ruleid( &iter )) >= 0) {

			if (!fwd_rule_valid_for_history(n.history,ruleID)) continue;
			
			new_hist = next_fwd_history(n.history,ruleID);

			apply_fwd_rule(ruleID, &current_state, &child);
			generated_states++;

			// Chequeamos si el nuevo hijo es un goal.
			if (is_goal(&child)) return n.cost + 1;
			
			h = heuristic(&child);
			
			if (h < UINT_MAX-1) {
				struct node nodoHijo;
				nodoHijo.priority = n.cost + get_fwd_rule_cost( ruleID ) + h;
				nodoHijo.s = child;
				nodoHijo.cost = n.cost + get_fwd_rule_cost( ruleID );
				nodoHijo.history = new_hist;
				aux = state_map_get(stateMap,&child);
				if (aux == NULL or nodoHijo.cost < *aux){
					state_map_add(stateMap,&child,nodoHijo.cost);
					q.push(nodoHijo);
				}
			}
		}
	}
	
	return -1;
}

//5 6 10 11 14 12 13 18 17 16 15 3 0 1 2 26 25 24 23 4 19 9 8 7 20 21 22 27

// 8 16 9 3 14 7 4 13 12 1 5 11 10 6 2 15
int heuristic(state_t *state){

	int heuristicValue = 0;
	int *aux;
	state_t abstract_transform;


	abstract_state(abs1, state, &abstract_transform);
	aux = state_map_get(grupo1, &abstract_transform);
	heuristicValue += *aux;

	assert(aux != NULL);
	abstract_state(abs2, state, &abstract_transform);
	aux = state_map_get(grupo2, &abstract_transform);

	heuristicValue += *aux;

	abstract_state(abs3, state, &abstract_transform);
	aux = state_map_get(grupo3, &abstract_transform);

	heuristicValue += *aux;

	return heuristicValue;

}
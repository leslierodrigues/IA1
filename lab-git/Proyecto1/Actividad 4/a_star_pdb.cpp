#include <iostream>
#include <ctime>
#include <cstdio>
#include <queue>
#include <map>
#include <climits>
#include <chrono>
using namespace std;

long long generated_states;

int a_star(state_t*);
int heuristic(state_t*);

state_t start;
string state_string;


void manejador_timeout( int signum ){

	cout << "A*, gap, pancake28,\"" << state_string << "\", na, " << heuristic(&start) <<" ,na, na, na" << endl;

	exit(0);
}


// Estructutura que se almacena en la cola de prioridades
struct node{
	int priority;
	state_t s;
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
	
//	cout << "Introduzca el estado del problema: " << endl;
	
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
try{
	clock_t begin = clock();
	auto start_time = chrono::high_resolution_clock::now();

	result = a_star(&start);

	auto end_time = chrono::high_resolution_clock::now();
	clock_t end = clock();

	long double elapsed_secs = chrono::duration_cast<std::chrono::duration<long double> >(end_time - start_time).count();
	long double gen_per_sec = (long double)(generated_states)/elapsed_secs;

//	cout << "algorithm, heuristic, domain, instance, cost, h0, generated, time, gen_per_sec " << endl;

	cout << "A*, gap, pancake28,\"" << state_string << "\", " << result << ", " << heuristic(&start);
	cout << ", " << generated_states << ", "  << elapsed_secs << ", ";
	cout << gen_per_sec << endl;
	}catch (const std::bad_alloc&){
	cout << " IDA*, gap, pancake28,\"" << state_string << "\", na, " << heuristic(&start);
	cout << ", na, na, na" << endl;
	exit(0);
	}
}

int a_star(state_t *start){

	state_t child, current_state;
	unsigned int h;
	int current_cost, history;
	int ruleID, new_hist;
	ruleid_iterator_t iter;
	int *aux;

	if (is_goal(start)) return 0;
	
	state_map_t *stateMap = new_state_map(); // Map con clave un estado y valor un entero 


	priority_queue<node> q; // Cola de prioridad

	state_map_add(stateMap,start,0);
	
	struct node n;
	n.priority = heuristic(start); // Se calula la prioridad
	n.history = init_history;
	n.s = *start;   // Se almacena el estado 
	
	q.push(n); // Se inserta en la cola
	
	while (!q.empty()){
		n = q.top(); //Se guarda el primer elemento de la cola
		q.pop(); // Se desencola 
		current_state = n.s; // Se almacena el estado desencolado
		current_cost = *state_map_get(stateMap,&n.s);
		init_fwd_iter(&iter,&current_state);
		//Expansión de nodos
		while((ruleID = next_ruleid( &iter )) >= 0) {

			if (!fwd_rule_valid_for_history(n.history,ruleID)) continue;
			
			new_hist = next_fwd_history(n.history,ruleID);

			apply_fwd_rule(ruleID, &current_state, &child);
			generated_states++;

			// Chequeamos si el nuevo hijo es un goal.
			if (is_goal(&child)) return current_cost + 1;
			
			h = heuristic(&child);
			
			struct node nodoHijo;
			nodoHijo.priority = current_cost + get_fwd_rule_cost( ruleID ) + h;
			nodoHijo.s = child;
			nodoHijo.history = new_hist;
			aux = state_map_get(stateMap,&child);

			// No se expanded los hijos a menos que tengan menor costo
			if (aux == NULL or ( current_cost+ get_fwd_rule_cost(ruleID) ) < *aux){
				state_map_add(stateMap,&child,current_cost+get_fwd_rule_cost( ruleID ));
				q.push(nodoHijo);
			}
		}
	}
	
	return -1;
}


// Heuristica
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
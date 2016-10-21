#include <iostream>
#include <ctime>
#include <cstdio>
#include <climits>
#include <utility>
#include <chrono>

using namespace std;

long long generated_states;


// Estructutura que se almacena en la cola de prioridades
struct node{
	state_t *state;
	unsigned int cost;
	unsigned int heuristic;
	unsigned int history;
};

state_map_t * grupo1, *grupo2, *grupo3;
abstraction_t *abs1, *abs2, *abs3;


state_t start;
string state_string;


void manejador_timeout( int signum ){

	cout << "A*, gap, pancake28,\"" << state_string << "\", na, " << heuristic(&start) <<" ,na, na, na" << endl;

	exit(signum);
}


unsigned int ida_star(state_t *);

pair<unsigned int,bool> bounded_a(node *, unsigned int);


int main(){
	
	state_t start; 
	string state_string; // Almacena el estado dado por el usuario
	int result; // Valor retornado por la función
	int goalID;
	
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
	state_string.pop_back();

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
	
	result = ida_star(&start);

	auto end_time = chrono::high_resolution_clock::now();
	clock_t end = clock();


	long double elapsed_secs = chrono::duration_cast<std::chrono::duration<long double> >(end_time - start_time).count();
	long double gen_per_sec = (long double)(generated_states)/elapsed_secs;




//	cout << "algorithm, heuristic, domain, instance, cost, h0, generated, time, gen_per_sec " << endl;

	cout << " IDA*, gap, pancake28,\"" << state_string << "\", " << result << ", " << heuristic(&start);
	cout << ", " << generated_states << ", "  << elapsed_secs << ", ";
	cout << gen_per_sec << endl;
	
	}
	catch(int e){

	cout << " IDA*, gap, pancake28,\"" << state_string << "\", na, " << heuristic(&start);
	cout << ", na, na, na" << endl;

	}

	return 0;
}


unsigned int ida_star(state_t *start){
	unsigned int cota;
	struct node nodo;
	pair<int,bool> result;


	nodo.state = start;
	nodo.cost=0;
	nodo.heuristic = heuristic(start);
	nodo.history = init_history;

	cota = nodo.heuristic + nodo.cost;

	while(true){
		result = bounded_a(&nodo, cota);
		if (result.second) return (result.first);
		cota = result.first;
	}
}

pair<unsigned int,bool> bounded_a(node *nodo, unsigned int cota){
	pair<unsigned int,bool> result;
	unsigned int estimado = nodo->cost + nodo->heuristic;

	if (estimado > cota){
		result.first = estimado;
		result.second = false;
		return result;
	}

	if (is_goal((nodo->state))) {
		result.first = nodo->cost;
		result.second = true;
		return result;
	}
	
	unsigned int min_estimado = UINT_MAX;

	int ruleID, new_hist;
	ruleid_iterator_t iter;

	struct node hijo;
	state_t hijo_estado;
	state_t *current_state = nodo->state;
	
	init_fwd_iter(&iter,current_state);

	while((ruleID = next_ruleid( &iter )) >= 0) {

		if (!fwd_rule_valid_for_history(nodo->history,ruleID)) continue;

		new_hist = next_fwd_history(nodo->history,ruleID);

		apply_fwd_rule(ruleID, current_state, &hijo_estado);
		generated_states++;
		hijo.history = new_hist;
		hijo.state = &hijo_estado;
		hijo.cost = nodo->cost + 1;
		hijo.heuristic = heuristic(&hijo_estado);

		result = bounded_a(&hijo,cota);
		if (result.second) return result;
		min_estimado = min_estimado < result.first ? min_estimado : result.first;
	}

	result.first = min_estimado;
	result.second = false;

	return result;
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
#include <iostream>
#include <ctime>
#include <cstdio>
#include <csignal>


using namespace std;

#define MAX_DEPTH 50

string state_string;

long long generated_states;
// manejador en caso de un timeout
void manejadorTimeout( int signum ){

	cout << "dfid ,11puzzle , \"" << state_string << "\", na, na, na, na" << endl;

	exit(signum);
}

int dfs(state_t*, int, int, int);
int iterative_deepening(state_t*);

int main(){
	signal(SIGTERM, manejadorTimeout); 
	state_t start;
	int result;

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

	if (state_string[state_string.size()-1] == '\n'){
		state_string.pop_back();
	}

	generated_states = 0;
	

	try{
		// medimos el tiempo con clock_t
		clock_t begin = clock();

		// Empezamos el algoritmo
		result = iterative_deepening(&start);


		clock_t end = clock();


		long double elapsed_secs = (long double)(end - begin) / CLOCKS_PER_SEC;

		long double gen_per_sec = (long double)(generated_states)/elapsed_secs;

		// Imprimimos Resultados
		cout << "dfid ,11puzzle , \"" << state_string << "\", " << result;
		cout << ", " << generated_states << ", " << elapsed_secs << ", ";
		cout << gen_per_sec << endl;
	}
	catch(int e){
		// En caso de una excepcion, solo imprimimos que no se puede.
		cout << "dfid, 11puzzle, \"" << state_string << "\", na, na, na, na" << endl;
		exit(0);
	}
}


int iterative_deepening(state_t *start){

	// Si el estado es el goal ya solo retornamos 0
	if (is_goal(start)) return 0;

	int bound = 0;
	int history = init_history;
	int path_cost;

	while (1){
		//Vamos incrementando la cota hasta que path_cost sea positivo
		// que es cuando terminamos.
		path_cost = dfs(start,0,bound,history);

		if (path_cost != -1) return path_cost;

		bound++;
	}
}


int dfs(state_t *current, int cost, int max_cost, int history){
	// Si nos pasamos de la cota retornamos.
	if (cost + 1 >= max_cost) return -1;

	int aux;
	int ruleID, new_hist;
	state_t child;
	ruleid_iterator_t iter;

	// Inicializamos las reglas.
	init_fwd_iter(&iter,current);
	while((ruleID = next_ruleid( &iter )) >= 0) {

		//Chequeamos con el automata de movimientos que sea valido
		if (!fwd_rule_valid_for_history(history,ruleID)) continue;

		if (cost + 1 >= max_cost) return -1;
		// Generamos la nueva historia y el hijo
		new_hist = next_fwd_history(history,ruleID);
		apply_fwd_rule(ruleID, current, &child);
		generated_states++;

		// Chequeamos si el nuevo hijo es un goal.
		if (is_goal(&child)) return cost+1;

		aux = dfs(&child,cost+1,max_cost,new_hist);

		if (aux != -1) return aux;
	}

	return -1;

}
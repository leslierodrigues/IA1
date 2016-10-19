#include <iostream>
#include <ctime>
#include <cstdio>
#include <csignal>

using namespace std;

#define MAX_DEPTH 50

long long generated_states;
string state_string;

void manejadorSenalesKill( int signum )
{
   
	cout << " dfid , 11puzzle , \"" << state_string << "\", ";
	cout << "NA, NA, NA, NA" << endl;

   exit(signum);  

}


int dfs(state_t*, int, int, int);
int iterative_deepening(state_t*);

int main(){
	signal(SIGINT, manejadorSenalesKill); 
	state_t start;
	//string state_string;
	int result;
	cout << "Introduzca el estado del problema: " << endl;

	cout << " algorithm, domain, instance, cost, generated, time, gen_per_sec " << endl;

	while (getline(cin,state_string) != 0){

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

	result = iterative_deepening(&start);

	clock_t end = clock();

	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	double gen_per_sec = double(generated_states)/elapsed_secs;


	cout << " dfid , 11puzzle , \"" << state_string << "\", " << result;
	cout << ", " << generated_states << ", " << elapsed_secs << ", ";
	cout << gen_per_sec << endl;

	}

}


int iterative_deepening(state_t *start){

	if (is_goal(start)) return 0;

	int bound = 0;
	int history = init_history;
	int path_cost;

	while (1){

		path_cost = dfs(start,0,bound,history);

		if (path_cost != -1) return path_cost;

		bound++;
	}
}


int dfs(state_t *current, int cost, int max_cost, int history){
	if (cost + 1 >= max_cost) return -1;

	int aux;
	int ruleID, new_hist;
	state_t child;
	ruleid_iterator_t iter;

	init_fwd_iter(&iter,current);
	while((ruleID = next_ruleid( &iter )) >= 0) {

		if (!fwd_rule_valid_for_history(history,ruleID)) continue;

		if (cost + 1 >= max_cost) return -1;
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
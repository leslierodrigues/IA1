#include <iostream>
#include <ctime>
#include <cstdio>
#include <chrono>
#include <windows.h>

// Cosas de tiempo temporales.


double PCFreq = 0.0;
__int64 CounterStart = 0;

using namespace std;

#define MAX_DEPTH 50

long long generated_states;
void manejadorSenalesKill( int signum )
{

 cout << " dfid , 11puzzle , \"" << state_string << "\", ";
 cout << "na, na, na, na" << endl;

   exit(signum);  

}

void StartCounter()
{
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
	cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart);

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}
double GetCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart-CounterStart)/PCFreq;
}

int dfs(state_t*, int, int, int);
int iterative_deepening(state_t*);

int main(){
	state_t start;
	string state_string;
	int result;
	signal(SIGINT, manejadorSenalesKill);
//	cout << "Introduzca el estado del problema: " << endl;

//	cout << " algorithm, domain, instance, cost, generated, time, gen_per_sec " << endl;

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
	

//	auto begin = chrono::high_resolution_clock::now();

	try{

	StartCounter();

	result = iterative_deepening(&start);

//	auto end = chrono::high_resolution_clock::now();

//	long double elapsed_secs = (long double)chrono::duration_cast<chrono::nanoseconds>(end-begin).count();

	long double elapsed_secs = GetCounter();

	double gen_per_sec = double(generated_states)/elapsed_secs;


	cout << " dfid , 11puzzle , \"" << state_string << "\", " << result;
	cout << ", " << generated_states << ", " << elapsed_secs << ", ";
	cout << gen_per_sec << endl;
	}
	catch(int e){
			cout << " dfid , 11puzzle , \"" << state_string << "\", na, na, na, na" << endl;
			exit(0);
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
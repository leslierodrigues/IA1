#include <iostream>
#include <string.h>

using namespace std;

#define MAX_DEPTH 50


int backwards_dfs(state_t *current, int cost, int max_cost, int history){

	if (cost == max_cost) return -1;

	int ruleID, new_hist;
	state_t child;
	ruleid_iterator_t iter;

	init_fwd_iter(&iter,current);
	while((ruleID = next_ruleid( &iter )) >= 0) {
		if (!fwd_rule_valid_for_history(history,ruleID)) continue;

		depth_size[depth]++;
		if (cost + 1 == max_cost) continue;

		new_hist = next_fwd_history(history,ruleID);

		apply_fwd_rule(ruleID, current, &child);

		dfs(&child,cost+1,max_cost,depth_size,new_hist);
	}

	return -1;

}




int main(){
	int wanted_depth;
	long long depth_sizes[MAX_DEPTH];
	state_t goal;
	int goalID;
	int history;

	cout << "Cual es la profundida deseada?" << endl;

	cin >> wanted_depth;

	// We obtain a goal state, shouldnt matter which one we choose.
	first_goal_state(&goal,&goalID);
	history = init_history;

	while()



	depth_sizes[0]++;
	backwards_dfs(&goal,0,wanted_depth,depth_sizes,history);




}
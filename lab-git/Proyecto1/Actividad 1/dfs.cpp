#include <iostream>
#include <string.h>

using namespace std;

#define MAX_DEPTH 50


void backwards_dfs(state_t *current, int depth, int max_depth, long long *depth_size,int history){

	if (depth == max_depth) return ;

	int ruleID, new_hist;
	state_t child;
	ruleid_iterator_t iter;

	init_bwd_iter(&iter,current);
	while((ruleID = next_ruleid( &iter )) >= 0) {
		if (!bwd_rule_valid_for_history(history,ruleID)) continue;

		depth_size[depth+1]++;
		if (depth + 1 == max_depth) continue;

		new_hist = next_bwd_history(history,ruleID);

		apply_bwd_rule(ruleID, current, &child);


		backwards_dfs(&child,depth+1,max_depth,depth_size,new_hist);
	}


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

	memset(depth_sizes,0,sizeof(depth_sizes));

	depth_sizes[0]++;
	backwards_dfs(&goal,0,wanted_depth,depth_sizes,history);

	cout << "Depth" << '\t' << "Moves" << endl;
	for (int i = 0 ; i <= wanted_depth; i++){

		cout << i << '\t' << depth_sizes[i] << endl;

	}




}
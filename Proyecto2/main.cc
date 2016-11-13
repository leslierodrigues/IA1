// Game of Othello -- Example of main
// Universidad Simon Bolivar, 2012.
// Author: Blai Bonet
// Last Revision: 1/11/16
// Modified by: Georvic Tur
//              Leslie Rodrigues
//              Erick Silva

#include <algorithm>
#include <climits>
#include <iostream>
#include <limits>
#include "othello_cut.h" // won't work correctly until .h is fixed!
#include "utils.h"

#include <unordered_map>

using namespace std;

// Max depth to search at, changing it to a lower value may not guarantee
//  a correct result.
#define MAX_DEPTH 40
// Max depth to store, since "shallow" states are the most often used
//  is it often convenient to stop saving any states that are too deep.
//  set this to MAX_DEPTH to disable.
#define DEPTH_TO_STORE 40

unsigned expanded = 0;
unsigned generated = 0;

// we'll use tt_threshold as a max number of entries of a color.
// so max number of entries in total will be 2*tt_threshold.
int tt_threshold = 10000000; // threshold to save entries in TT

// Transposition table
struct stored_info_t {
    int value_;
    int type_;
    int depth_; 
    enum { EXACT, LOWER, UPPER };
    stored_info_t(int value = -100, int type = LOWER, int depth = 0):
                         value_(value), type_(type), depth_(depth){ }
};

struct hash_function_t {
    size_t operator()(const state_t &state) const {
        return state.hash();
    }
};


class hash_table_t : public unordered_map<state_t, stored_info_t, hash_function_t> {
};


// We'll save white moves on position 0
//  and black moves on position 1.
hash_table_t TTable[2];
// We'll also maintain a vector of saved positions
// and indexes in order to be able to replace earlier states.
int tt_index[2];
vector<state_t> saved_states[2];


int minmax(state_t state, int depth, bool use_tt = false);
int maxmin(state_t state, int depth, bool use_tt = false);
int negamax(state_t state, int depth, int color, bool use_tt = false);
int negamax(state_t state, int depth, int alpha, int beta, int color, bool use_tt = false);
int scout(state_t state, int depth, int color, bool use_tt = false);
int negascout(state_t state, int depth, int alpha, int beta, int color, bool use_tt = false);
bool TEST(state_t state, int score, int depth, int color,int condition, bool use_tt = false);
void populate_valid_moves(state_t *state, vector<int> *valid_moves, int color);
void add_to_table(state_t state,int value, int color, int depth = MAX_DEPTH, int type = stored_info_t::EXACT);


int main(int argc, const char **argv) {
    state_t pv[128];
    int npv = 0;
    for( int i = 0; PV[i] != -1; ++i ) ++npv;

    int algorithm = 0;
    if( argc > 1 ) algorithm = atoi(argv[1]);
    bool use_tt = argc > 2;

    // Extract principal variation of the game
    state_t state;
    cout << "Extracting principal variation (PV) with " << npv << " plays ... " << flush;
    for( int i = 0; PV[i] != -1; ++i ) {
        bool player = i % 2 == 0; // black moves first!
        int pos = PV[i];
        pv[npv - i] = state;
        state = state.move(player, pos);
    }
    pv[0] = state;
    cout << "done!" << endl;

#if 0
    // print principal variation
    for( int i = 0; i <= npv; ++i )
        cout << pv[npv - i];
#endif

    // Print name of algorithm
    cout << "Algorithm: ";
    if( algorithm == 0 ) {
        cout << "Minmax-Maxmin";
    } else if( algorithm == 1 ) {
        cout << "Negamax (minmax version)";
    } else if( algorithm == 2 ) {
        cout << "Negamax (alpha-beta version)";
    } else if( algorithm == 3 ) {
        cout << "Scout";
    } else if( algorithm == 4 ) {
        cout << "Negascout";
    }
    cout << (use_tt ? " w/ transposition table" : "") << endl;

    // Run algorithm along PV (bacwards)
    cout << "Moving along PV:" << endl;
    for( int i = 0; i <= npv; ++i ) {
        //cout << pv[i];
        int value = 0;

        TTable[0].clear();
        TTable[1].clear();
        // We reserve a starting space as to avoid rehashing.
        TTable[0].reserve(tt_threshold);
        TTable[1].reserve(tt_threshold);
        // Initializing each vector.
        saved_states[0].resize(tt_threshold);
        saved_states[1].resize(tt_threshold);
        tt_index[0] = 0;
        tt_index[1] = 0;

        float start_time = Utils::read_time_in_seconds();
        expanded = 0;
        generated = 0;
        int color = i % 2 == 1 ? 1 : -1;

        try {
            if( algorithm == 0 ) {
                value = color * (color == 1 ? maxmin(pv[i], MAX_DEPTH, use_tt) : minmax(pv[i], MAX_DEPTH, use_tt));
            } else if( algorithm == 1 ) {
                value = negamax(pv[i], MAX_DEPTH, color, use_tt);
            } else if( algorithm == 2 ) {
                value = negamax(pv[i], MAX_DEPTH, -200, 200, color, use_tt);
            } else if( algorithm == 3 ) {
                value = color * scout(pv[i], MAX_DEPTH, color, use_tt);
            } else if( algorithm == 4 ) {
                value = negascout(pv[i], MAX_DEPTH, -200, 200, color, use_tt);
            }
        } catch( const bad_alloc &e ) {
 //           cout << "size TT[0]: size=" << TTable[0].size() << ", #buckets=" << TTable[0].bucket_count() << endl;
   //         cout << "size TT[1]: size=" << TTable[1].size() << ", #buckets=" << TTable[1].bucket_count() << endl;
            use_tt = false;
        }

        float elapsed_time = Utils::read_time_in_seconds() - start_time;

        cout << npv + 1 - i << ". " << (color == 1 ? "Black" : "White") << " moves: "
             << "value=" << color * value
             << ", #expanded=" << expanded
             << ", #generated=" << generated
             << ", seconds=" << elapsed_time
             << ", #generated/second=" << generated/elapsed_time
             << endl;

    }

    return 0;
}

/*

    Auxiliar function to populate a vector with all valid moves.

*/

void populate_valid_moves(state_t *state, vector<int> *valid_moves, int color){
    // Generating the moves 
    //  We test for each possible move (from 0 to 35) wether it's possible for
    //   the current color.
    for (int pos = 0; pos < DIM; pos++){
        if (state->is_white_move(pos) and color == -1) valid_moves->push_back(pos);
        if (state->is_black_move(pos) and color == 1) valid_moves->push_back(pos);
    }

    // If there are no valid moves for this player, we have to skip the turn.
    if (valid_moves->empty()){
        valid_moves->push_back(36); // The "Do nothing" move
    }

    // We shuffle the moves
    // Author's Note: shuffling seems to actually make the program 
    // take longer on 90% of the cases, as such it was not done.
    //    random_shuffle(valid_moves->begin(),valid_moves->end());
}

/*

    Auxiliar function that takes care of adding new elements to the table

*/

void add_to_table(state_t state,int value, int color, int depth, int type){
    int table_to_check = color == 1? 1: 0;
    int index;

    // If we are above the depth to store, just return without doing anything.
    if (MAX_DEPTH - depth >= DEPTH_TO_STORE ) return;

    // We initialize a stored_info_t variable with the wanted values.
    stored_info_t state_info;

    state_info.value_ = value;
    state_info.depth_ = depth;
    state_info.type_ = type;

    if (TTable[table_to_check].find(state) != TTable[table_to_check].end()){
        // if the state is already in the table we just have to reset the values.
        TTable[table_to_check][state] = state_info;
        return;
    }
    else{
        // If the state is not in the table already, we gotta check if there's anything
        // to replace.

        // we reset the index of the specific table if neccesary
        if (tt_index[table_to_check] == tt_threshold) tt_index[table_to_check] = 0;
        index = tt_index[table_to_check];

        // We dont need to check if the state is actually a real one
        //  as erasing will just return 0 otherwise.
        TTable[table_to_check].erase(saved_states[table_to_check][index]);

        // We add the state to the table and to the vector
        TTable[table_to_check][state] = state_info;
        saved_states[table_to_check][index] = state;

        tt_index[table_to_check]++;
    }

}

/*

    Minmax/Maxmin algorithms.

*/

int minmax(state_t state, int depth, bool use_tt){
    // If the state is terminal or we have reached the depth limit.
    //  just return the value.
    if (state.terminal() or depth == 0) return state.value();

    // We initialize the score at the lowest value and decrease the depth.
    int score = INT_MAX;
    depth--;


    // Generating the moves 
    vector<int> valid_moves;
    populate_valid_moves(&state,&valid_moves,-1);

    // Main loop. we generate the child nodes and try to explore them here.
    state_t child;
    for (int pos : valid_moves){
        child = state.white_move(pos);
        generated++;
        if (use_tt){
            // We look in black's table for the child
            if (TTable[1].find(child) != TTable[1].end()){
                score = min(score,TTable[1][child].value_);
            }
            else{
                score = min(score,maxmin(child,depth,use_tt));
                expanded++;
            }
        }
        else{
            score = min(score,maxmin(child,depth,use_tt));
            expanded++;
        }
    }

    if (use_tt){
        add_to_table(state,score,-1,depth);
    }

    return score;
}


int maxmin(state_t state, int depth, bool use_tt){
    // If we dont have any remaining depth or the state is terminal
    //  we just return the state's value
    if (state.terminal() or depth == 0) return state.value();

    int score = INT_MIN;
    depth--;
    expanded++;

    // Generating the moves 
    vector<int> valid_moves;
    populate_valid_moves(&state,&valid_moves,1);

    // Main loop. we generate the child nodes and try to explore them here.
    state_t child;
    for (int pos : valid_moves){
        child = state.black_move(pos);
        generated++;
        if (use_tt){        
            // We look in White's table for the child
            if (TTable[0].find(child) != TTable[0].end()){
                score = max(score,TTable[0][child].value_);
            }
            else{
                score = max(score,minmax(child,depth,use_tt));
            }            
        }
        else{
            score = max(score,minmax(child,depth,use_tt));
        }
    }
    if (use_tt){
        add_to_table(state,score,1,depth);
    }

    return score;
}

/*

    Negamax algorithm.

*/


int negamax(state_t state, int depth, int color, bool use_tt){

    // If we dont have any remaining depth or the state is terminal
    //  we just return the state's value (multiplied by the color for proper signs)
    if (state.terminal() or depth == 0) return color*state.value();

    int table_to_check = color == 1 ? 1: 0;
    int alpha = INT_MIN;
    depth--;

    // Generating the moves 
    vector<int> valid_moves;
    populate_valid_moves(&state,&valid_moves,color);

    // Main loop. we generate the child nodes and try to explore them here.
    state_t child;

    for (int pos : valid_moves){
        child = color == 1 ? state.black_move(pos): state.white_move(pos);
        generated++;
        if (use_tt){
            // We look in the opposite table for the child
            if (TTable[!table_to_check].find(child) != TTable[!table_to_check].end()){
                alpha = max(alpha,-TTable[!table_to_check][child].value_);
            }
            else{
                alpha = max(alpha,-negamax(child,depth,-color,use_tt));
                expanded++;
            }
        }
        else{
            alpha = max(alpha,-negamax(child,depth,-color,use_tt));
            expanded++;
        }
    }


    if (use_tt){
        add_to_table(state,alpha,-1,depth);
    }

    return alpha;
}

/*

    Negamax algorithm with alpha-beta pruning.

*/


int negamax(state_t state, int depth, int alpha, int beta, int color, bool use_tt){
    // For alpha beta pruning, we need to take a different approach to the
    //  transposition table.

    int table_to_check = color == 1 ? 1 : 0;
    // We save the original alpha for future use.
    int original_alpha = alpha;
    int value,type;
    stored_info_t state_info;


    if (use_tt){
        // We have to check if the state is in the table and if it's
        //  on a higher depth (is "stronger" than the current search).
        if (TTable[table_to_check].find(state) != TTable[table_to_check].end()){
            state_info = TTable[table_to_check][state];

            if (state_info.depth_ >= depth){
                type = state_info.type_;
                value = state_info.value_;
                // If the type of the node is EXACT, then we just return the value,
                //  if it's a lower bound, we use it to grow alpha if possible
                //  and if it's an upper bound, we'll use it to make beta smaller.
                if (type == stored_info_t::EXACT){
                    return value;
                }
                else if (type == stored_info_t::LOWER){
                    alpha = max(alpha,value);
                }
                else if (type == stored_info_t::UPPER){
                    beta = min(beta,value);
                }

                // if after making beta lower or alpha higher we reach
                //  alpha >= beta, we can just return the value.
                if (alpha >= beta){
                    return value;
                }
            }
       }
    }


    // If we dont have any remaining depth or the state is terminal
    //  we just return the state's value (multiplied by the color for proper signs)
    if (state.terminal() or depth == 0) return color*state.value();


    int val, score = INT_MIN;
    expanded++;

    // Generating the moves 
    vector<int> valid_moves;
    populate_valid_moves(&state,&valid_moves,color);

    // Main loop. we generate the child nodes and try to explore them here.
    state_t child;
    for (int pos : valid_moves){
        child = color == 1 ? state.black_move(pos): state.white_move(pos);
        generated++;
        val = -negamax(child,depth-1,-beta,-alpha,-color,use_tt);
        score = max(score,val);
        alpha = max(alpha,val);
        if (alpha >= beta){
            break;
        }
    }

    // If we use transposition tables, we have to store the value.
    if (use_tt){
        if (score <= original_alpha){
            add_to_table(state,score,color,depth,stored_info_t::UPPER);
        }
        else if (score >= beta){
            add_to_table(state,score,color,depth,stored_info_t::LOWER);
        }
        else{
            add_to_table(state,score,color,depth,stored_info_t::EXACT);
        }
    }

    return score;
}

/*

    Scout algorithm along with it's TEST algorithm.

*/ 

int scout(state_t state, int depth, int color, bool use_tt){
    // We check if we have an answer for this node already.
    int table_to_check = color == 1 ? 1 : 0;

    if (use_tt){
        if (TTable[table_to_check].find(state) != TTable[table_to_check].end()){
            return TTable[table_to_check][state].value_;
        }
    }

    // If we dont have any remaining depth or the state is terminal
    //  we just return the state's value.
    if (state.terminal() or depth == 0) return state.value();

    int score = 0;
    depth--;

    // Generating the moves 
    vector<int> valid_moves;
    populate_valid_moves(&state,&valid_moves,color);

    // Main loop. we generate the child nodes and try to explore them here.
    state_t child;
    bool is_first = true;

    for (int pos : valid_moves){
        child = color == 1 ? state.black_move(pos): state.white_move(pos);
        generated++;
        if (is_first){
            score = scout(child, depth, -color, use_tt);
            expanded++;
            is_first = false;
        }
        else{
            if ((color == 1 and TEST(child,score,depth,-color,0,use_tt)) or
                    (color == -1 and !TEST(child,score,depth,-color,1,use_tt))){
                score = scout(child, depth, -color, use_tt);
                expanded++;
            }
        }
    }

    if (use_tt){
        add_to_table(state,score,color,depth);
    }

    return score;
}

bool TEST(state_t state, int score, int depth, int color, int condition,bool use_tt){

    // We could use the transposition table here, but in practice
    //  it just makes the algorithm slower.

    // If we dont have any remaining depth or the state is terminal
    //  we just return the condition applied to the state's value
    //  and the initial one.
    if (state.terminal() or depth == 0){
        return condition == 1 ? state.value() >= score : state.value() > score;
    }   
    depth--;
    expanded++;

    // Generating the moves 
    vector<int> valid_moves;
    populate_valid_moves(&state,&valid_moves,color);


    // Main loop. we generate the child nodes and try to explore them here.
    state_t child;
    for (int pos : valid_moves){
        child = color == 1 ? state.black_move(pos): state.white_move(pos);
        generated++;
        if (color == 1 and TEST(child,score,depth,-color,condition,use_tt)){
            return true;
        }
        else if (color == -1 and !TEST(child,score,depth,-color,condition,use_tt)){
            return false;
        }
    }

    return color != 1;
}

/*

    Negascout algorithm.

*/

int negascout(state_t state, int depth, int alpha, int beta, int color, bool use_tt){
    // As negascout also uses alpha-beta pruning, we have to use the
    //  same approach on transposition tables.

    int table_to_check = color == 1 ? 1 : 0;
    int original_alpha = alpha;
    int type, value;
    stored_info_t state_info;

    if (use_tt){
        // We have to check if the state is in the table and if it's
        //  on a higher depth (is "stronger" than the current search).
        if (TTable[table_to_check].find(state) != TTable[table_to_check].end()){
            state_info = TTable[table_to_check][state];
            if (state_info.depth_ >= depth){
                type = state_info.type_;
                value = state_info.value_;

                // If the type of the node is EXACT, then we just return the value,
                //  if it's a lower bound, we use it to grow alpha if possible
                //  and if it's an upper bound, we'll use it to make beta smaller.
                if (type == stored_info_t::EXACT){
                    return value;
                }
                else if (type == stored_info_t::LOWER){
                    alpha = max(alpha,value);
                }
                else if (type == stored_info_t::UPPER){
                    beta = min(beta,value);
                }

                // if after making beta lower or alpha higher we reach
                //  alpha >= beta, we can just return the value.
                if (alpha >= beta){
                    return value;
                }
            }
        }
    }


    // If we dont have any remaining depth or the state is terminal
    //  we just return the state's value (multiplied by the color for proper signs)
    if (state.terminal() or depth == 0) return color*state.value();

    expanded++;

    int score = 0;
    bool is_first = true;

    // Generating the moves 
    vector<int> valid_moves;
    populate_valid_moves(&state,&valid_moves,color);

    // Main loop where we generate each child and explore them.
    state_t child;
    for (int pos : valid_moves){
        child = color == 1 ? state.black_move(pos): state.white_move(pos);
        generated++;

        if (is_first){
            score = -negascout(child, depth-1, -beta, -alpha, -color, use_tt);
            is_first = false;
        }
        else{
            score = -negascout(child, depth-1, -alpha - 1, -alpha, -color, use_tt);
            if (alpha < score and score < beta){
                score = -negascout(child,depth-1,-beta,-score, -color, use_tt);
            }
        }

        alpha = max(alpha,score);

        if ( alpha >= beta){
            break;
        }
    }

    // If we use the transposition table, we gotta save and properly clasify
    //  the state.
    if (use_tt){
        if (alpha <= original_alpha){
            add_to_table(state,alpha,color,depth,stored_info_t::UPPER);
        }
        else if (alpha >= beta){
            add_to_table(state,alpha,color,depth,stored_info_t::LOWER);
        }
        else{
            add_to_table(state,alpha,color,depth,stored_info_t::EXACT);
        }
    }


    return alpha;
}
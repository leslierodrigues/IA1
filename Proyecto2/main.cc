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
#include <queue>

using namespace std;

// Max depth to search at, changing it to a lower value may not guarantee
//  a correct result.
#define MAX_DEPTH 50

unsigned expanded = 0;
unsigned generated = 0;
int tt_saved = 0;
int tt_threshold = 32; // threshold to save entries in TT

// Transposition table
struct stored_info_t {
    int value_;
    int type_;
    int priority_;
    enum { EXACT, LOWER, UPPER };
    stored_info_t(int value = -100, int type = LOWER, int priority = 0):
                         value_(value), type_(type), priority_(priority){}
};

struct hash_function_t {
    size_t operator()(const state_t &state) const {
        return state.hash();
    }
};

class hash_table_t : public unordered_map<state_t, stored_info_t, hash_function_t> {
};

// We'll save white on 0 and black on 1.
hash_table_t TTable[2];


int minmax(state_t state, int depth, bool use_tt = false);
int maxmin(state_t state, int depth, bool use_tt = false);
int negamax(state_t state, int depth, int color, bool use_tt = false);
int negamax(state_t state, int depth, int alpha, int beta, int color, bool use_tt = false);
int scout(state_t state, int depth, int color, bool use_tt = false);
int negascout(state_t state, int depth, int alpha, int beta, int color, bool use_tt = false);
bool TEST(state_t state, int score, int depth, int color,int condition);

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
            cout << "size TT[0]: size=" << TTable[0].size() << ", #buckets=" << TTable[0].bucket_count() << endl;
            cout << "size TT[1]: size=" << TTable[1].size() << ", #buckets=" << TTable[1].bucket_count() << endl;
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

// minmax Algorithm
int minmax(state_t state, int depth, bool use_tt){
    // If the state is terminal or we have reached the depth limit.
    //  just return the value.
    if (depth == 0 or state.terminal()) return state.value();

    // We initialize the score at the lowest value and decrease the depth.
    int score = INT_MAX;
    depth--;


    // Generating the moves 
    vector<int> valid_moves;
    for (int move = 0; move < DIM; move++){
        if (state.is_white_move(move)) valid_moves.push_back(move);
    }

    // If there are no valid moves for this player, we have to skip the turn.
    if (valid_moves.empty()){
        valid_moves.push_back(36); // The "Do nothing" move
    }

    // We shuffle the moves
    random_shuffle(valid_moves.begin(),valid_moves.end());

    state_t child;
    for (int pos : valid_moves){
        child = state.white_move(pos);
        generated++;
        if (!use_tt){
            score = min(score,maxmin(child,depth,use_tt));
            expanded++;
        }
        else{
            // We look in black's table for the child
            if (TTable[1].find(child) != TTable[1].end()){
                score = min(score,TTable[1][child].value_);
            }
            else{
                score = min(score,maxmin(child,depth,use_tt));
                expanded++;
            }

        }
    }

    TTable[0][state] = score;

    return score;
}


int maxmin(state_t state, int depth, bool use_tt){
    if (depth == 0 or state.terminal()) return state.value();

    int score = INT_MIN;
    depth--;

    // Generating the moves 
    vector<int> valid_moves;
    for (int move = 0; move < DIM; move++){
        if (state.is_black_move(move)) valid_moves.push_back(move);
    }

    // If there are no valid moves for this player, we have to skip the turn.
    if (valid_moves.empty()){
        valid_moves.push_back(36); // The "Do nothing" move
    }

    // We shuffle the moves
    random_shuffle(valid_moves.begin(),valid_moves.end());

    state_t child;
    for (int pos : valid_moves){
        child = state.black_move(pos);
        generated++;
        if (!use_tt){        
            score = max(score,minmax(child,depth,use_tt));
            expanded++;
        }
        else{
            // We look in White's table for the child
            if (TTable[0].find(child) != TTable[0].end()){
                score = max(score,TTable[0][child].value_);
            }
            else{
                score = max(score,minmax(child,depth,use_tt));
                expanded++;
            }            
        }
    }

    TTable[1][state] = score;
    return score;
}


int negamax(state_t state, int depth, int color, bool use_tt){
    if (depth == 0 or state.terminal()) return color*state.value();

    int alpha = INT_MIN;
    depth--;

    // Generating the moves 
    vector<int> valid_moves;
    for (int move = 0; move < DIM; move++){
        if ((color == -1 and state.is_white_move(move)) or
                (color == 1 and state.is_black_move(move))){
            valid_moves.push_back(move);
        }
    }

    // If there are no valid moves for this player, we have to skip the turn.
    if (valid_moves.empty()){
        valid_moves.push_back(36); // The "Do nothing" move
    }

    // We shuffle the moves
    random_shuffle(valid_moves.begin(),valid_moves.end());

    state_t child;
    for (int pos : valid_moves){
        child = color == 1 ? state.black_move(pos): state.white_move(pos);
        generated++;
        alpha = max(alpha,-negamax(child,depth,-color,use_tt));
        expanded++;
    }

    TTable[color == 1 ? 1: 0][state] = alpha;
    return alpha;
}

int negamax(state_t state, int depth, int alpha, int beta, int color, bool use_tt){
    if (depth == 0 or state.terminal()) return color*state.value();

    int val,score = INT_MIN;
    depth--;

    // Generating the moves 
    vector<int> valid_moves;
    for (int move = 0; move < DIM; move++){
        if ((color == -1 and state.is_white_move(move)) or
                (color == 1 and state.is_black_move(move))){
            valid_moves.push_back(move);
        }
    }

    // If there are no valid moves for this player, we have to skip the turn.
    if (valid_moves.empty()){
        valid_moves.push_back(36); // The "Do nothing" move
    }

    // We shuffle the moves
    random_shuffle(valid_moves.begin(),valid_moves.end());

    state_t child;
    for (int pos : valid_moves){
        child = color == 1 ? state.black_move(pos): state.white_move(pos);
        generated++;

        val = -negamax(child,depth,-beta,-alpha,-color,use_tt);

        score = max(score,val);
        alpha = max(alpha,val);
        expanded++;

        if (alpha >= beta){
            break;
        }

    }

    return score;
}


int scout(state_t state, int depth, int color, bool use_tt){
    if (depth == 0 or state.terminal()) return state.value();

    int score = 0;
    depth--;

    // Generating the moves 
    vector<int> valid_moves;
    for (int move = 0; move < DIM; move++){
        if ((color == -1 and state.is_white_move(move)) or
                (color == 1 and state.is_black_move(move))){
            valid_moves.push_back(move);
        }
    }

    // If there are no valid moves for this player, we have to skip the turn.
    if (valid_moves.empty()){
        valid_moves.push_back(36); // The "Do nothing" move
    }

    // We shuffle the moves
    random_shuffle(valid_moves.begin(),valid_moves.end());

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
            if ((color == 1 and TEST(child,score,depth,-color,0)) or
                    (color == -1 and !TEST(child,score,depth,-color,1))){
                score = scout(child, depth, -color, use_tt);
                expanded++;
            }
        }
    }

    return score;
}

bool TEST(state_t state, int score, int depth, int color, int condition){
    if (depth == 0 or state.terminal()){
        return condition == 1 ? state.value() >= score : state.value() > score;
    }   
    depth--;

    // Generating the moves 
    vector<int> valid_moves;
    for (int move = 0; move < DIM; move++){
        if ((color == -1 and state.is_white_move(move)) or
                (color == 1 and state.is_black_move(move))){
            valid_moves.push_back(move);
        }
    }

    // If there are no valid moves for this player, we have to skip the turn.
    if (valid_moves.empty()){
        valid_moves.push_back(36); // The "Do nothing" move
    }

    // We shuffle the moves
    random_shuffle(valid_moves.begin(),valid_moves.end());


    state_t child;
    for (int pos : valid_moves){
        child = color == 1 ? state.black_move(pos): state.white_move(pos);        
        if (color == 1 and TEST(child,score,depth,-color,condition)){
            return true;
        }
        else if (color == -1 and !TEST(child,score,depth,-color,condition)){
            return false;
        }
    }

    return color != 1; // No es necesario, el juego termina.
}



int negascout(state_t state, int depth, int alpha, int beta, int color, bool use_tt){
    if (depth == 0 or state.terminal()) return color*state.value();

    int score = 0;
    bool is_first = true;
    depth--;

    // Generating the moves 
    vector<int> valid_moves;
    for (int move = 0; move < DIM; move++){
        if ((color == -1 and state.is_white_move(move)) or
                (color == 1 and state.is_black_move(move))){
            valid_moves.push_back(move);
        }
    }

    // If there are no valid moves for this player, we have to skip the turn.
    if (valid_moves.empty()){
        valid_moves.push_back(36); // The "Do nothing" move
    }

    // We shuffle the moves
    random_shuffle(valid_moves.begin(),valid_moves.end());

    state_t child;
    for (int pos : valid_moves){
        child = color == 1 ? state.black_move(pos): state.white_move(pos);
        generated++;

        if (is_first){
            score = -negascout(child, depth, -beta, -alpha, -color, use_tt);
            expanded++;
            is_first = false;
        }
        else{
            score = -negascout(child, depth, -alpha - 1, -alpha, -color, use_tt);
            if (alpha < score and score < beta){
                score = -negascout(child,depth,-beta,-score, -color, use_tt);
                expanded++;
            }
        }

        alpha = max(alpha,score);

        if ( alpha >= beta){
            break;
        }
    }

    return alpha;
}
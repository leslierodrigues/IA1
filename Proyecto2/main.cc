// Game of Othello -- Example of main
// Universidad Simon Bolivar, 2012.
// Author: Blai Bonet
// Last Revision: 1/11/16
// Modified by: 

#include <algorithm>
#include <climits>
#include <iostream>
#include <limits>
#include "othello_cut.h" // won't work correctly until .h is fixed!
#include "utils.h"

#include <unordered_map>

using namespace std;

#define MAX_DEPTH 15
#define BLACK 0
#define WHITE 1

unsigned expanded = 0;
unsigned generated = 0;
int tt_threshold = 32; // threshold to save entries in TT

// Transposition table
struct stored_info_t {
    int value_;
    int type_;
    enum { EXACT, LOWER, UPPER };
    stored_info_t(int value = -100, int type = LOWER) : value_(value), type_(type) { }
};

struct hash_function_t {
    size_t operator()(const state_t &state) const {
        return state.hash();
    }
};

class hash_table_t : public unordered_map<state_t, stored_info_t, hash_function_t> {
};

hash_table_t TTable[2];

int minmax(state_t state, int depth, bool use_tt = false);
int maxmin(state_t state, int depth, bool use_tt = false);
int negamax(state_t state, int depth, int color, bool use_tt = false);
int negamax(state_t state, int depth, int alpha, int beta, int color, bool use_tt = false);
int scout(state_t state, int depth, int color, bool use_tt = false);
int negascout(state_t state, int depth, int alpha, int beta, int color, bool use_tt = false);

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
                //value = negamax(pv[i], MAX_DEPTH, -200, 200, color, use_tt);
            } else if( algorithm == 3 ) {
                //value = scout(pv[i], MAX_DEPTH, color, use_tt);
            } else if( algorithm == 4 ) {
                //value = negascout(pv[i], MAX_DEPTH, -200, 200, color, use_tt);
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

int minmax(state_t state, int depth, bool use_tt){
    if (depth == 0 or state.terminal()) return state.value();

    int score = INT_MAX;
    depth--;

    vector<int> valid_moves;
    for (int move = 0; move < DIM; move++){
        if (state.is_white_move(move)) valid_moves.push_back(move);
    }

    if (valid_moves.empty()){
        valid_moves.push_back(36); // The "Do nothing" move
    }

    random_shuffle(valid_moves.begin(),valid_moves.end());

    state_t child;
    for (int pos : valid_moves){
        child = state.white_move(pos);
        generated++;
        score = min(score,maxmin(child,depth,use_tt));
        expanded++;
    }

    return score;
}


int maxmin(state_t state, int depth, bool use_tt){
    if (depth == 0 or state.terminal()) return state.value();

    int score = INT_MIN;
    depth--;

    vector<int> valid_moves;
    for (int move = 0; move < DIM; move++){
        if (state.is_black_move(move)) valid_moves.push_back(move);
    }

    if (valid_moves.empty()){
        valid_moves.push_back(36); // The "Do nothing" move
    }

    random_shuffle(valid_moves.begin(),valid_moves.end());

    state_t child;
    for (int pos : valid_moves){
        child = state.black_move(pos);
        generated++;
        score = max(score,minmax(child,depth,use_tt));
        expanded++;
    }

    return score;
}


int negamax(state_t state, int depth, int color, bool use_tt){
    if (depth == 0 or state.terminal()) return color*state.value();

    int alpha = INT_MIN;
    depth--;

    vector<int> valid_moves;
    for (int move = 0; move < DIM; move++){
        if ((color == -1 and state.is_white_move(move)) or
                (color == 1 and state.is_black_move(move))){
            valid_moves.push_back(move);
        }
    }

    if (valid_moves.empty()){
        valid_moves.push_back(36); // The "Do nothing" move
    }

    random_shuffle(valid_moves.begin(),valid_moves.end());

    state_t child;
    for (int pos : valid_moves){
        child = color == 1 ? state.black_move(pos): state.white_move(pos);
        generated++;
        alpha = max(alpha,-negamax(child,depth,-color,use_tt));
        expanded++;
    }

    return alpha;
}


int negamax(state_t state, int depth, int alpha, int beta, int color, bool use_tt);
int scout(state_t state, int depth, int color, bool use_tt);
int negascout(state_t state, int depth, int alpha, int beta, int color, bool use_tt);

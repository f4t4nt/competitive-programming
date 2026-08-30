#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// -----------------------------------------------------------------------------
//  Memoized win/loss game search
// -----------------------------------------------------------------------------
//  Supports:    wins(s, moves, mem), true iff the current player wins from
//               s: some move leads to a state the opponent loses from
//  Restrictions:
//              - no moves = loss (normal play; flip that base case for misere)
//              - moves(s) returns the states reachable in one move; states
//                must not repeat along a line of play (the game is a DAG)
//  Usage:  map<ll, bool> mem;
//          auto moves = [&](ll s) {
//              vector<ll> nxt;
//              for (ll d = 1; d <= 3 && d <= s; d++) nxt.push_back(s - d);
//              return nxt;
//          };
//          bool first_player_wins = wins(n, moves, mem);
// -----------------------------------------------------------------------------

template<typename State, typename Moves>
bool wins(State s, Moves &moves, map<State, bool> &mem) {
    auto it = mem.find(s);
    if (it != mem.end()) return it->second;
    bool w = false;
    for (auto &t : moves(s)) if (!wins(t, moves, mem)) { w = true; break; }
    return mem[s] = w;
}

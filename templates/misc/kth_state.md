vector<ll> get_kth_state(ll n, ll k) { // 1-indexed
    vector<ll> state(n);
    for (ll i = 0; i < n; i++) {
        for (auto &choice : valid_choices) {
            apply(choice);
            ll cnt = count_states();
            if (cnt >= k) break;
            k -= cnt;
            undo(choice);
        }
        if (no choice made) return no solution;
    }
    return state;
}

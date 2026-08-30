sort(all(x), [](ll a, ll b) {
    return a < b;
}); // equivalent to regular sort

sort(all(pts), [](pll a, pll b) {
    return a.f * b.s > a.s * b.f;
}); // sort by a.x / a.y (ascending)

bool cmp(ll a, ll b) { return a > b; } // descending
set<ll, decltype(&cmp)> s(cmp);

#include <bits/stdc++.h>
using namespace std;

template <class T1, class T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &p) {
  return os << '{' << p.first << ", " << p.second << '}';
}

template <class T, class = decay_t<decltype(*begin(declval<T>()))>,
          class = enable_if_t<!is_same<T, string>::value>>
ostream &operator<<(ostream &os, const T &c) {
  os << '[';
  for (auto it = c.begin(); it != c.end(); ++it)
    os << &", "[2 * (it == c.begin())] << *it;
  return os << ']';
}
#define _NTH_ARG(_1, _2, _3, _4, _5, _6, N, ...) N
#define _FE_0(_CALL, ...)
#define _FE_1(_CALL, x) _CALL(x)
#define _FE_2(_CALL, x, ...) _CALL(x) _FE_1(_CALL, __VA_ARGS__)
#define _FE_3(_CALL, x, ...) _CALL(x) _FE_2(_CALL, __VA_ARGS__)
#define _FE_4(_CALL, x, ...) _CALL(x) _FE_3(_CALL, __VA_ARGS__)
#define _FE_5(_CALL, x, ...) _CALL(x) _FE_4(_CALL, __VA_ARGS__)
#define FOR_EACH_MACRO(MACRO, ...)                                             \
  _NTH_ARG(dummy, ##__VA_ARGS__, _FE_5, _FE_4, _FE_3, _FE_2, _FE_1, _FE_0)     \
  (MACRO, ##__VA_ARGS__)
#define DBG_OUT(x) #x " = " << x << "; "
#define dbg(...)                                                              \
  cerr << "Line " << __LINE__ << ": " FOR_EACH_MACRO(DBG_OUT, __VA_ARGS__) << '\n'

typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define vsz(a) (int)a.size()
#define f first
#define s second

const ll mod = 1e9 + 7;
const ll INF = 1e18;

bool good(int N, ll S, vector<int>& lens, int mid){
  if (S <= 2){
    return mid <= S;
  }
  
  vector<int> mods(3);

  for(int i = 0; i<mid-2; i++){
    S -= lens[i] / 3;
    mods[lens[i]%3]++;
  }
  
  S-= 2;

  if(mods[1] > mods[2]){
    S -= mods[2] + (mods[1] - mods[2] + 1) /2;
  }else{
    S -= mods[2];
  }

  return S >= 0;
}

void run_testcase() {
  ll N, S; cin >> N >> S;
  vector<int> lens(N);
  for(ll i = 0; i<N; i++) cin >> lens[i];
  sort(lens.begin(), lens.end());

  int l = 0, r = N;

  while(l < r){
    int mid = (l + r + 1) / 2;
    if(good(N, S, lens, mid)){
      l = mid;
    }else{
      r = mid - 1;
    }
  }

  cout << l;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    
    int T = 1;
    // cin >> T;
    while(T--) {
        run_testcase();
    }
    return 0;
}
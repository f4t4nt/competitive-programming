//@timothyg

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
// const ll mod = 998244353;
const ll INF = 1e18; //~9*INF max

int xDir[4] = {1, -1, 0, 0};
int yDir[4] = {0, 0, -1, 1};
string dir = "RLUD";

void run_testcase(){
    int N, M; cin >> N >> M;

    pii S, E;

    vector<string> grid(N);
    for(int i = 0; i<N; i++) {
        cin >> grid[i];
        for(int j = 0; j<M; j++){
            if(grid[i][j] == 'R'){
                S.f = i, S.s = j;
            }

            if(grid[i][j] == 'E'){
                E.f = i, E.s = j;
            }
        }
    }

    string str; cin >> str;
    
    priority_queue<array<int, 4>, vector<array<int, 4>>, greater<array<int, 4>>> minQueue;
    map<int, set<pii>> vis;

    minQueue.push(array<int, 4>{0, S.f, S.s, 0});

    while(!minQueue.empty()){
        auto cur = minQueue.top(); minQueue.pop();
        int step = cur[0], y = cur[1], x = cur[2], k = cur[3];

        if(vis.count(k) && vis[k].count(pii(y, x))){
            continue;
        }
        vis[k].insert(pii(y, x));

        if(grid[y][x] == 'E'){
            cout << step;
            break;
        }

        if(k < str.length()){
            minQueue.push({step+1, y, x, k+1});
        }

        for(int i = 0; i<4; i++){
            int dY = yDir[i] + y, dX = xDir[i] + x;
            if(dY >= N || dY < 0 || dX >= M || dX < 0 || grid[dY][dX] == '#') continue;
            minQueue.push({step+1, dY, dX, k});
        }

        for(int i = 0; i<4; i++){
            int dY = yDir[i] + y, dX = xDir[i] + x;

            if(k < str.length() && str[k] == dir[i]){
                if(dY >= N || dY < 0 || dX >= M || dX < 0 || grid[dY][dX] == '#') {
                    minQueue.push({step, y, x, k+1});
                }else{
                    minQueue.push({step, dY, dX, k+1});
                }
            }
        }
    }

    cout << '\n';
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    
    int T = 1;
    // cin >> T;
    while(T--){
        run_testcase();
    }
    return 0;
}
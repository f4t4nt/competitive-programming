#include <iostream>
#include <vector>
#include <algorithm>
#define pb push_back
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;



// returns g = gcd(a, b); finds x, y such that d = ax + by
ll extended_euclid(ll a, ll b, ll &x, ll &y)
{
    ll xx = y = 0; ll yy = x = 1;
    while (b)
    {
        int q = a / b; 
        int t = b; b = a%b; a = t;
        t = xx; xx = x - q*xx; x = t;
        t = yy; yy = y - q*yy; y = t;
    }
    return a;
}

// Chinese remainder theorem (special case): find z such that // z % m1 = r1, z % m2 = r2. Here, z is unique modulo M = lcm(m1, m2). // Return (z, M). On failure, M = -1.

pll crtsimple(ll m1, ll r1, ll m2, ll r2)
{
    ll s, t;
    ll g = extended_euclid(m1, m2, s, t);
    if (r1%g != r2%g)
        return pll (0, -1);
    return pll (((s*r2*m1 + t*r1*m2)%(m1*m2)+(m1*m2))%(m1*m2) / g, m1*m2 / g);
}

// finds all solutions to ax = b (mod n)
pll modular_linear_equation_solver(ll a, ll b, ll n)
{
    ll x, y; vector<ll> ret;
    ll g = extended_euclid(a, n, x, y);
    if (!(b%g))
    {
        x = ((x*(b / g))%n+n)%n;
        return pll (x%(n/g), n/g);
        //for (int i = 0; i < g; i++)
            //ret.push_back(mod(x + i*(n / g), n));
    }
    return pll (0, -1);
}

// Chinese remainder theorem: find z such that // z % m[i] = r[i] for all i. Note that the solution is // unique modulo M = lcm_i (m[i]). Return (z, M). On // failure, M = -1. Note that we do not require the a[i]’s // to be relatively prime.
pll chinese_remainder_theorem(const vector<ll> &m, vector<ll> &r)
{ pll ret = pll (r[0], m[0]);
    for (int i = 1; i < m.size(); i++)
    {
        ret = crtsimple(ret.second, ret.first, m[i], r[i]);
        if (ret.second == -1) break;
    }
    return ret;
}

ll n, nx, ny, nz;
struct planet
{
    ll x, y, z, vx, vy, vz, m;
    
    planet(ll x, ll y, ll z, ll vx, ll vy, ll vz, ll m) :
    x(x), y(y), z(z), vx(vx), vy(vy), vz(vz), m(m){}
    
};

vector<planet> sim[1001];
bool planetsort(planet a, planet b)
{
    if (a.x!=b.x)
        return a.x<b.x;
    if (a.y!=b.y)
        return a.y<b.y;
    return a.z<b.z;
}
bool planetsort2(planet a, planet b)
{
    if (a.m!=b.m)
        return a.m>b.m;
    if (a.x!=b.x)
        return a.x<b.x;
    if (a.y!=b.y)
        return a.y<b.y;
    return a.z<b.z;
}

bool equalpos(planet a, planet b)
{
    return (a.x==b.x && a.y==b.y && a.z==b.z);
}


int main()
{
    cin >> n >> nx >> ny >> nz;
    ll x, y, z, vx, vy, vz, m;
    ll cur=0;
    for (int i=0; i<n; i++)
    {
        cin >> m >> x >> y >> z >> vx >> vy >> vz;
        //sim[0].pb({x, y, z, vx, vy, vz, m});
        sim[cur].pb(planet(x, y, z, vx, vy, vz, m));
    }
    ll numplanets=n;
    bool equal=true;
    while (equal)
    {
        ll mintime=1000000001;
        equal=false;
        for (int i=0; i<numplanets; i++)
            for (int j=0; j<i; j++)
            {
                pll p1, p2, p3;
                p1=modular_linear_equation_solver(((sim[cur][i].vx-sim[cur][j].vx)%nx+nx)%nx, (-sim[cur][i].x+sim[cur][j].x+nx)%nx, nx);
                p2=modular_linear_equation_solver(((sim[cur][i].vy-sim[cur][j].vy)%ny+ny)%ny, (-sim[cur][i].y+sim[cur][j].y+ny)%ny, ny);
                //cout <<sim[cur][i].vy-sim[cur][j].vy+ny << " " <<  (sim[cur][i].y-sim[cur][j].y+ny)%ny << " " << ny << endl;
                p3=modular_linear_equation_solver(((sim[cur][i].vz-sim[cur][j].vz)%nz+nz)%nz, (-sim[cur][i].z+sim[cur][j].z+nz)%nz, nz);
                /*cout << p1.first << " " << p1.second << endl;
                cout << p2.first << " " << p2.second << endl;
                cout << p3.first << " " << p3.second << endl;
                return 0;*/
                if (p1.second==-1 || p2.second==-1 || p3.second==-1)
                    continue;
                vector<ll> v1; v1.pb(p1.second); v1.pb(p2.second); v1.pb(p3.second);
                vector<ll> v2; v2.pb(p1.first); v2.pb(p2.first); v2.pb(p3.first);
                pll pans=chinese_remainder_theorem(v1, v2);
                if (pans.second!=-1)
                    mintime=min(mintime, pans.first);
            }
        if (mintime<1000000001)
        {
            equal=true;
            cur++;
            for (int j=0; j<numplanets; j++)
            {
                sim[cur+1].pb(planet(((sim[cur-1][j].x+sim[cur-1][j].vx*mintime)%nx+nx)%nx, ((sim[cur-1][j].y+sim[cur-1][j].vy*mintime)%ny+ny)%ny, ((sim[cur-1][j].z+sim[cur-1][j].vz*mintime)%nz+nz)%nz, sim[cur-1][j].vx, sim[cur-1][j].vy, sim[cur-1][j].vz, sim[cur-1][j].m));
                //cout << sim[cur+1][j].x << " " << sim[cur+1][j].y << " " << sim[cur+1][j].z << endl;
            }
            //return 0;
            //cout << "Hi1" << endl;
            sort(sim[cur+1].begin(), sim[cur+1].end(), planetsort);
            sim[cur].clear();
            ll lpntr=0;
            ll rpntr=0;
            //cout << "Hi2" << endl;
            while (lpntr<numplanets)
            {
                ll curmass=0;
                ll curvx=0;
                ll curvy=0;
                ll curvz=0;
                //cout << "Hi3" << endl;
                while (rpntr<numplanets && equalpos(sim[cur+1][lpntr], sim[cur+1][rpntr]))
                {
                    curmass+=sim[cur+1][rpntr].m;
                    curvx+=sim[cur+1][rpntr].vx;
                    curvy+=sim[cur+1][rpntr].vy;
                    curvz+=sim[cur+1][rpntr].vz;
                    rpntr++;
                }
                //cout << "hi4" << endl;
                planet p=sim[cur+1][lpntr];
                //cout << p.x << " " << p.y << " " << p.z << endl;
                sim[cur].pb(planet(p.x, p.y, p.z, curvx/(rpntr-lpntr), curvy/(rpntr-lpntr), curvz/(rpntr-lpntr), curmass));
                lpntr=rpntr;
            }
            numplanets=sim[cur].size();
            //cout << cur << endl;
            //cout << numplanets << endl;
            //return 0;
        }
    }
    //cout << cur << endl;
    sort(sim[cur].begin(), sim[cur].end(), planetsort2);
    cout << numplanets << endl;
    for (int i=0; i<numplanets; i++)
    {
        planet p=sim[cur][i];
        cout << "P" << i << ": " << p.m << " " << p.x << " " << p.y << " " << p.z << " " << p.vx << " " << p.vy << " " << p.vz << endl;
    }
    
}
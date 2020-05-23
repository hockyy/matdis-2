/*
Author : Hocky Yudhiono
5/23/2020 8:48:30 AM

1. You can sort the query if offline!
2. Don't bring the dp remaining state when dfsing on DP on Tree.
3. Try to reverse (Think from the back) if you stuck.
4. Be careful when submitting Div. 2 D-F, dont waste it on stupid WAs.
5. Try to reduce a problem
*/

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <iomanip>
#include <cstdio>
#include <limits>
#include <string>
#include <vector>
#include <cmath>
#include <deque>
#include <queue>
#include <stack>
#include <map>
#include <set>
using namespace std;

typedef long long LL;
typedef long long ll;
typedef long double LD;
typedef vector<int> vi;
typedef pair<LL,LL> PLL;
typedef pair<LL,int> PLI;
typedef pair<int,int> PII;
typedef pair<int,int> pii;
typedef vector<vector<LL>> VVL;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define popf pop_front
#define pf push_front
#define popb pop_back
#define mp make_pair
#define pb push_back
#define remove erase
#define fi first
#define se second

//If the time limit is strict, try not to use long double

//Remember to undefine if the problem is interactive
#define endl '\n'
#define DEBUG(X) cout << ">>> DEBUG(" << __LINE__ << ") " << #X << " = " << (X) << endl

const double EPS = 1e-9;
const int INFMEM = 63;
const int INF = 1061109567;
const LL LINF = 4557430888798830399LL;
const double DINF = numeric_limits<double>::infinity();
const LL MOD = 1000000007;
const int dx[8] = {0,0,1,-1,1,-1,1,-1};
const int dy[8] = {1,-1,0,0,1,-1,-1,1};
// Do dir^1 to get reverse direction
const char dch[4] = {'R','L','D','U'};
// const string ds[8] = {"E","W","S","N","SE","NW","SW","NE"};
const double PI = 3.141592653589793;

inline void open(string a){
    freopen((a+".in").c_str(),"r",stdin);
    freopen((a+".out").c_str(),"w",stdout);
}

inline void fasterios(){
    //Do not use if interactive
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
}

#include <unordered_map>
#include <unordered_set>

template <class T>
struct dictionary {
    std::map<T, size_t> dict;
    std::vector<T> idict;
    size_t id(T s) { 
        if (!dict.count(s)) {
            dict[s] = idict.size();
            idict.push_back(s);
        }
        return dict[s];
    }
    T value(size_t id) {
        return idict[id];
    }
    size_t size() const {
        return dict.size();
    }
};

template <class T>
struct Graph {
    int n; dictionary<T> *dic;
    vector<multiset<int>> edge;
    bool isDirected;
    Graph(int N, dictionary<T> *tmpDic, bool isDir = 0) : n(N), edge(N), dic(tmpDic), isDirected(isDir) {}
    void add_edge(int u, int v){
        edge[u].insert(v); if(!isDirected) edge[v].insert(u);
    }
    void hielholzer(vector <multiset<int>> &tmpEdge, LL pos, vector <int> &path){
        while(tmpEdge[pos].size()){
            LL nx = *tmpEdge[pos].begin();
            tmpEdge[pos].erase(tmpEdge[pos].begin());
            if(!isDirected) tmpEdge[nx].erase(tmpEdge[nx].find(pos));
            hielholzer(tmpEdge, nx, path);
        }
        path.pb(pos);
    }
    bool getEulerPath(){
        int st = -1, ed = -1;
        if(isDirected){
            vi indeg(n), outdeg(n);
            for(int i = 0;i < n;i++){
                outdeg[i] = sz(edge[i]);
                for(auto nx : edge[i]){
                    indeg[nx]++;
                }
            }
            int stCnt = 0;
            int edCnt = 0;
            for(int i = 0;i < n;i++){
                if(indeg[i] == outdeg[i]) continue;
                if(indeg[i] < outdeg[i]) stCnt++, st = i;
                else edCnt++, ed = i;
            }
            if(stCnt == edCnt && stCnt == 0){
                st = 0; ed = 0;
                cout << "Euler circuit founded instead" << endl;
            }else if(stCnt == 1 && edCnt == 1 && indeg[st]+1 == outdeg[st] && indeg[ed] == outdeg[ed]+1){
                cout << "Euler path founded with start " << st << " and ed " << ed << endl;
            }else{
                cout << "Euler path not possible" << endl;
                return 0;
            }
        }else{
            st = 0;
            int oddCnt = 0;
            for(int i = 0;i < n;i++){
                oddCnt += sz(edge[i])%2;
                if(oddCnt == 1) st = i;
            }
            if(oddCnt == 0){
                cout << "Euler circuit founded instead" << endl;
            }else if(oddCnt > 2){
                cout << "Euler path not possible" << endl;
                return 0;
            }
        }
        vector <int> path;
        vector <multiset<int>> tmpEdge = edge;
        cout << "Euler path:";
        hielholzer(tmpEdge, st, path);
        reverse(path.begin(),path.end());
        for(auto x : path) cout << " " << dic->value(x);
        cout << endl;
        return 1;
    }
    bool getEulerCircuit(){
        int st = -1;
        if(isDirected){
            vi indeg(n), outdeg(n);
            for(int i = 0;i < n;i++){
                outdeg[i] = sz(edge[i]);
                for(auto nx : edge[i]){
                    indeg[nx]++;
                }
            }
            for(int i = 0;i < n;i++){
                if(indeg[i] == outdeg[i]) continue;
                cout << "Euler circuit not possible" << endl;
                return 0;
            }
        }else{
            for(int i = 0;i < n;i++){
                if(sz(edge[i])%2){
                    cout << "Euler circuit not possible" << endl;
                    return 0;
                }
            }
        }
        st = 0;
        cout << "Euler circuit founded" << endl;
        vector <int> path;
        vector <multiset<int>> tmpEdge = edge;
        cout << "Euler circuit:";
        hielholzer(tmpEdge, st, path);
        reverse(path.begin(),path.end());
        for(auto x : path) cout << " " << dic->value(x);
        cout << endl;
        return 1;
    }
    void getHamiltonianPath(){
    }
};

int main(){
    bool isDir;
    int m; cin >> m >> isDir;
    vector <PII> edges;
    dictionary<string> dic;
    for(int i = 1;i <= m;i++){
        string u,v; cin >> u >> v;
        edges.push_back({dic.id(u), dic.id(v)});
    }
    Graph<string> g(sz(dic), &dic, isDir);
    for(auto e : edges) g.add_edge(e.fi, e.se);
    g.getEulerPath();
    g.getEulerCircuit();
    // g.getHamiltonianPath();
    // g.getHamiltonianCircuit();
    return 0;
}

/**
Input:
20 0
a d
d b
b e
e c
c h
h m
m j
j l
l i
i k
k f
f a
d f
f i
d g
g i
e g
g j
j h
e h
Output:
Euler circuit founded instead
Euler path: a d b e c h e g d f i l j h m j g i k f a
Euler circuit founded
Euler circuit: a d b e c h e g d f i l j h m j g i k f a

Input:
5 1
c d
d b
b c
c a
a b
Output:
Euler path founded with start 0 and ed 2
Euler path: c d b c a b
Euler circuit not possible

Input:
8 1
f a
a g
b g
c b
g c
g e
e d
d f
Output:
Euler circuit founded instead
Euler path: f a g c b g e d f
Euler circuit founded
Euler circuit: f a g c b g e d f

 */
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
    Graph(int N, dictionary<T> *tmpDic) : n(N), edge(N), dic(tmpDic) {}
    void add_edge(int u, int v, bool isDirected = 0){
        edge[u].insert(v); if(!isDirected) edge[v].insert(u);
    }
    void hielholzer(vector <multiset<int>> &tmpEdge, LL pos, vector <int> &path){
        while(tmpEdge[pos].size()){
            LL nx = *edge[pos].begin();
            tmpEdge[pos].erase(tmpEdge[pos].begin());
            tmpEdge[nx].erase(tmpEdge[nx].find(pos));
            hielholzer(tmpEdge, nx, path);
        }
        path.pb(pos);
    }
    void getEulerPath(){
        int oddCnt = 0; int st = 0;
        for(int i = 0;i < n;i++){
            oddCnt += sz(edge[i])%2;
            if(oddCnt == 1) st = i;
        }
        if(oddCnt > 2){
            cout << "Euler path not possible" << endl;
            return;
        }
        vector <int> path;
        vector <multiset<int>> tmpEdge = edge;
        hielholzer(tmpEdge, st, path);
        for(auto x : path) cout << dic->value(x) << " ";
        cout << endl;
    }
    void getEulerCircuit(){
        int oddCnt = 0; int st = 0;
        for(int i = 0;i < n;i++){
            oddCnt += sz(edge[i])%2;
            if(oddCnt == 1) st = i;
        }
        if(oddCnt){
            cout << "Euler circuit not possible" << endl;
            return;
        }
        vector <int> path;
        vector <multiset<int>> tmpEdge = edge;
        hielholzer(tmpEdge, st, path);
        for(auto x : path) cout << dic->value(x) << " ";
        cout << endl;
    }
};

int main(){

    int m; cin >> m;
    vector <PII> edges;
    dictionary<string> dic;
    for(int i = 1;i <= m;i++){
        string u,v; cin >> u >> v;
        edges.push_back({dic.id(u), dic.id(v)});
    }
    Graph<string> g(sz(dic), &dic);
    for(auto e : edges) g.add_edge(e.fi, e.se);
    g.getEulerPath();
    g.getEulerCircuit();
    return 0;
}
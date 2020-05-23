/*
Author : Hocky Yudhiono
5/23/2020 8:48:30 AM
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef vector<int> vi;
typedef pair<int,int> PII;

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
    bool dpHamiltonianPath(vector <bitset<20>> &memo, vector <bitset<20>> &vis, int mask, int pos){
        if(vis[mask][pos]) return memo[mask][pos];
        vis[mask][pos] = 1;
        if(mask == (1<<n)-1){ memo[mask].set(pos); return 1; }
        if(mask == 0){
            for(int i = 0;i < n;i++){
                if(dpHamiltonianPath(memo, vis, (mask|(1<<i)), i)){
                    memo[mask].set(pos);
                    return 1;
                }
            }
        }
        for(int i = 0;i < n;i++){
            if((mask&(1<<i))) continue;
            if(!edge[pos].count(i)) continue;
            if(dpHamiltonianPath(memo, vis, (mask|(1<<i)), i)){
                memo[mask].set(pos);
                return 1;
            }
        }
        return 0;
    }

    void printHamiltonianPath(vector <bitset<20>> &memo, vector <bitset<20>> &vis, int mask, int pos){
        if(mask != 0) cout << " " << dic->value(pos);
        if(mask == (1<<n)-1) return;
        if(mask == 0){
            for(int i = 0;i < n;i++){
                if(dpHamiltonianPath(memo, vis, (mask|(1<<i)), i)){
                    printHamiltonianPath(memo, vis, (mask|(1<<i)), i);
                    return;
                }
            }
        }
        for(int i = 0;i < n;i++){
            if((mask&(1<<i))) continue;
            if(!edge[pos].count(i)) continue;
            if(dpHamiltonianPath(memo, vis, (mask|(1<<i)), i)){
                printHamiltonianPath(memo, vis, (mask|(1<<i)), i);
                return;
            }
        }
    }

    bool getHamiltonianPath(){
        if(n > 23){
            cout << "Too big :/" << endl;
            return 0;
        }
        vector <bitset<20>> memo(1LL<<n);
        vector <bitset<20>> vis(1LL<<n);
        if(!dpHamiltonianPath(memo, vis, 0, 0)){
            cout << "Hamiltonian Path not possible" << endl;
            return 0;
        }
        cout << "Hamiltonian path:";
        printHamiltonianPath(memo, vis, 0, 0);
        return 1;
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
    g.getHamiltonianPath();
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
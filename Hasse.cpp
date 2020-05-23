/*
Author : Hocky Yudhiono
4/26/2020 1:44:57 PM

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
typedef long double LD;
typedef unsigned long long ULL;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
//If the time limit is strict, try not to use long double

#define popf pop_front
#define pf push_front
#define popb pop_back
#define mp make_pair
#define pb push_back
#define remove erase
#define fi first
#define se second

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

typedef long long VT;


const LL MAXN = 1000;
LL compIdx = 0;
set <LL> edge[MAXN+5];
set <LL> oriEdge[MAXN+5];
map <VT,LL> comp;
bool done[MAXN+5];
VT revcomp[MAXN+5];
LL outDegree[MAXN+5];
set <LL> revEdge[MAXN+5];

LL rubah(VT pos){
    if(comp.count(pos)) return comp[pos];
    revcomp[compIdx] = pos;
    return comp[pos] = compIdx++;
}

void makeEdge(VT a, VT b){
    // No self loop bro
    LL aIdx = rubah(a);
    LL bIdx = rubah(b);
    oriEdge[aIdx].insert(bIdx);
    if(a == b) return;
    edge[aIdx].insert(bIdx);
    revEdge[bIdx].insert(aIdx);
    outDegree[bIdx]++;
}

bool isEdge(VT a, VT b){
    return oriEdge[rubah(a)].count(rubah(b));
}

// Declare main set here
vector <VT> A = {2,4,6,9,12,18,27,36,48,60,72};
vector <VT> level[MAXN+5];
LL distLevel[MAXN+5];

void relax(LL a){
    done[a] = 1;
    level[distLevel[a]].pb(revcomp[a]);
    for(LL nx : edge[a]){
        --outDegree[nx];
        distLevel[nx] = max(distLevel[nx],distLevel[a]+1);
        if(outDegree[nx] == 0) relax(nx);
    }
}

pair<LL, vector <VT> > getLowerBound(vector <VT> B){
    vector <VT> lowerBound;
    for(VT a : A){
        bool isLowerBound = 1;
        for(VT b : B){
            if(!isEdge(a,b)){
                isLowerBound = 0;
                break;
            }
        }
        if(isLowerBound) lowerBound.pb(a);
    }
    cout << (!lowerBound.empty() ? "The lower bound of set B is " : "The set has no lower bound");
    for(int i = 0;i < lowerBound.size();i++) cout << lowerBound[i] << " \n"[i == lowerBound.size()-1];
    LL glb = -1;
    for(VT a : lowerBound){
        bool isGreatest = 1;
        for(VT b : lowerBound){
            if(!isEdge(b,a)){
                isGreatest = 0;
                break;
            }
        }
        if(isGreatest){
            glb = rubah(a);
        }
    }
    return {glb,lowerBound};
}

pair<LL, vector <VT> > getUpperBound(vector <VT> B){
    vector <VT> upperBound;
    for(VT a : A){
        bool isUpperBound = 1;
        for(VT b : B){
            if(!isEdge(b,a)){
                isUpperBound = 0;
                break;
            }
        }
        if(isUpperBound) upperBound.pb(a);
    }
    LL lub = -1;
    for(VT a : upperBound){
        bool isLeast = 1;
        for(VT b : upperBound){
            if(!isEdge(a,b)){
                isLeast = 0;
                break;
            }
        }
        if(isLeast){
            lub = rubah(a);
        }
    }
    return {lub,upperBound};
}


int main(){
    //Construct edges here
    sort(A.begin(),A.end());
    LL n = A.size();
    for(VT a : A){
        for(VT b : A){
            if(b%a == 0) makeEdge(a,b);
        }
    }

    //Construct Level Hasse Diagram here
    for(int aIdx = 0;aIdx < n;aIdx++){
        if(done[aIdx]) continue;
        if(outDegree[aIdx] == 0){
            distLevel[aIdx] = 1;
            relax(aIdx);
        }
    }

    //Construct the Edges for Hasse Diagram here
    for(int aIdx = 0;aIdx < n;aIdx++){
        for(auto nx : edge[aIdx]){
            for(auto pre : revEdge[nx]){
                if(edge[pre].count(aIdx)){
                    edge[pre].erase(nx);
                }
            }
        }
    }
    for(VT a : A){
        cout << "---------------------------------" << endl;
        LL aIdx = rubah(a);
        cout << a << " is level " << distLevel[aIdx] << endl;
        cout << a << " has " << (edge[aIdx].empty() ? "no outcoming edge." : "edge: ") << endl;
        for(auto nx : edge[aIdx]){
            cout << a << " -> " << revcomp[nx] << endl;
        }
    }
    cout << "---------------------------------" << endl;

    for(int i = 1;;i++){
        if(level[i].empty()) break;
        cout << "Level " << i << " has :";
        for(auto cur : level[i]) cout << " " << cur;
        cout << endl;
    }
    vector <VT> maximalElements;
    vector <VT> minimalElements;
    cout << "---------------------------------" << endl;
    cout << "Maximal element is ";
    for(int aIdx = 0;aIdx < n;aIdx++){
        if(edge[aIdx].empty()){
            maximalElements.pb(revcomp[aIdx]);
        }
    }
    for(int i = 0;i < maximalElements.size();i++) cout << maximalElements[i] << " \n"[i == maximalElements.size()-1];
    cout << "---------------------------------" << endl;
    cout << "Minimal element is ";
    for(int aIdx = 0;aIdx < n;aIdx++){
        if(revEdge[aIdx].empty()){
            minimalElements.pb(revcomp[aIdx]);
        }
    }
    for(int i = 0;i < minimalElements.size();i++) cout << minimalElements[i] << " \n"[i == minimalElements.size()-1];
    cout << "---------------------------------" << endl;
    cout << (maximalElements.size() == 1 ? "The greatest element is " : "The relation has no greatest element");
    if(maximalElements.size() == 1) cout << maximalElements[0];
    cout << endl;
    cout << "---------------------------------" << endl;
    cout << (minimalElements.size() == 1 ? "The least element is " : "The relation has no least element");
    if(minimalElements.size() == 1) cout << minimalElements[0];
    cout << endl;
    cout << "---------------------------------" << endl;
    pair<LL, vector <VT> > tmplb = getLowerBound({4,6,12});
    LL glb = tmplb.fi;
    vector <VT> lowerBound = tmplb.se;
    cout << (!lowerBound.empty() ? "The lower bound of set B is " : "The set has no lower bound");
    for(int i = 0;i < lowerBound.size();i++) cout << lowerBound[i] << " \n"[i == lowerBound.size()-1];
    cout << (glb != -1 ? "The greatest lower bound of set B is " : "The set has no greatest lower bound");
    if(glb != -1) cout << revcomp[glb];
    cout << endl;
    cout << "---------------------------------" << endl;
    pair<LL, vector <VT> > tmpub = getUpperBound({4,6,12});
    LL lub = tmpub.fi;
    vector <VT> upperBound = tmpub.se;
    cout << (!upperBound.empty() ? "The upper bound of set B is " : "The set has no upper bound");
    for(int i = 0;i < upperBound.size();i++) cout << upperBound[i] << " \n"[i == upperBound.size()-1];
    cout << (lub != -1 ? "The least upper bound of set B is " : "The set has no least upper bound");
    if(lub != -1) cout << revcomp[lub];
    cout << endl;
    cout << "---------------------------------" << endl;
    cout << "Is this poset a lattice? ";
    if(minimalElements.size() == 1 && maximalElements.size() == 1) cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;
}
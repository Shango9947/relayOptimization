#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace std;
using namespace __gnu_pbds;
 
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#define io ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
 
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vector<int>> vii;
typedef vector<pair<int, int>> vpii;
typedef vector<vector<ll>> vll;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef pair<pdd, int> ptemp;
typedef pair<ll, ll> pll;
typedef pair<int, vector<int>> pivi;
typedef map<int, int> mii;
typedef map<ll, ll> mll;
typedef map<int , vi> mivi;
#define rep(i,a,b) for(i=a;i<=b;++i)
#define rev(i,a,b) for(i=a;i>=b;--i)
#define all(x)  x.begin(),x.end()
#define google(x) cout << "Case #" << x << ": ";
#define mp make_pair
#define pb push_back
#define pob pop_back
#define pf push_front
#define pof pop_front
// #define MAX_N 200006
// #define modulo 1000000007
// #define modulo 163577857 
#define modulo 998244353 
#define PI 3.14159265358979323846264338327
#define ordered_set(type) tree<type, null_type, less<type>, rb_tree_tag, tree_order_statistics_node_update> 
// order_of_key: The number of items in a set that are strictly smaller than k
// find_by_order: It returns an iterator to the ith largest element
ll inf = 1e9+7;
// const int maxn = (1<<20);
template<class T> ostream& operator<<(ostream &os, vector<T> V){
	os << "[ ";
	for(auto v  : V) os << v << " ";
	return os << " ]";
}
template<class T> ostream& operator<<(ostream &os, set<T> V){
	os << "[ ";
	for(auto v  : V) os << v << " ";
	return os << " ]";
}
template<class T , class R > ostream& operator<<(ostream &os, map<T , R> V){
	os << "[ ";
	for(auto v  : V) os << "(" << v.first << ":" << v.second << ")";
	return os << " ]";
}
template<class T , class R > ostream& operator<<(ostream &os, pair<T , R> V){
	return os << "(" << V.first << "," << V.second << ")";
}
 
#define cerr cout
#define TRACE
#ifdef TRACE
    #define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
    template <typename Arg1>
    void __f(const char* name, Arg1&& arg1){
        cerr << name << " : " << arg1 << endl;
    }
    template <typename Arg1, typename... Args>
    void __f(const char* names, Arg1&& arg1, Args&&... args){
        const char* comma = strchr(names + 1, ',');
        cerr.write(names, comma - names) << " : " << arg1<<" | ";
        __f(comma+1, args...);
    }
    clock_t clk=clock();
    #define checktime() cout<<"\nTime Elapsed : "<<float(clock()-clk)/CLOCKS_PER_SEC<<endl
#else
    #define trace(...);
    #define checktime();
#endif
 
int i, j;

const int maxn = 1e5; int n, m;

void show(deque<pii> que) {
    int a = que.size();
    while(a--) {
        pii fro = que.front(); que.pop_front(); que.push_back(fro);
        cout << '{' << fro.first << " " << fro.second << "} "; 
    }
    cout << "\n";
}

//undirected and directed graphs
//0 is in node, 1 is out node
//pair in directed denotes in/out as 0/1 as second element
vector<int> graph1[maxn]; set<pii> graph2[maxn][2];

//path vectors
vector<int> p1, p2; 

void find(set<int> start, int end) {
    //initialisation of source nodes and distance of various nodes!
    deque<pii> que; int dis[maxn][2]; 
    for(int i=0;i<n;i++) dis[i][0] = 2*maxn, dis[i][1] = 2*maxn;
    for(auto p : start) que.pb({p, 1}), dis[p][1] = 0, dis[p][0] = -1;
    
    // show(que); // debug
    
    //basic BFS
    while(!que.empty()) {
        pii fro = que.front(); que.pop_front();
        for(auto p : graph2[fro.first][fro.second]) {

            if(dis[p.first][p.second] != 2*maxn) continue;
            dis[p.first][p.second] = dis[fro.first][fro.second] + 1; 
            que.push_back(p);

        }
        if(dis[end][0] != 2*maxn) break;
    }

    // for(int i=0;i<n;i++) trace(i, dis[i][0], dis[i][1]); // debug

    //take final node.
    vector<pii> vec = {{end, 0}};

    //iterate in reverse manner upto a source node
    while(start.find(vec.back().first) == start.end()) {
        int curr = vec.back().second; int oth = !curr;
        if(dis[vec.back().first][oth] == dis[vec.back().first][curr] - 1) {
            vec.pb({vec.back().first, oth}); continue; 
        } 
        for(auto p : graph1[vec.back().first]) {
            if(dis[p][oth] == dis[vec.back().first][curr] - 1) { vec.pb({p, oth}); break; }
        }
    }

    // trace(vec); //debug

    //remove front edges and add reverse edges as compensation
    for(int i=1;i<vec.size();i++) {
        int a1 = vec[i].first; int b1 = vec[i-1].first; int a2 = vec[i].second; int b2 = vec[i-1].second;
        // {b1, b2} <- {a1, a2}
        graph2[a1][a2].erase({b1, b2}); graph2[b1][b2].insert({a1, a2});
        // trace(vec[i], vec[i-1]); // debug
    }

    /********************************************************************************/

    for(int i=0;i<n;i++) dis[i][0] = 2*maxn, dis[i][1] = 2*maxn;
    que.clear();

    for(auto p : start) que.pb({p, 1}), dis[p][1] = 0, dis[p][0] = -1;

    while(!que.empty()) {
        pii fro = que.front(); que.pop_front();
        for(auto p : graph2[fro.first][fro.second]) {

            if(dis[p.first][p.second] != 2*maxn) continue;
            dis[p.first][p.second] = dis[fro.first][fro.second] + 1; 
            que.push_back(p);

        }
        // show(que); // debug
        if(dis[end][0] != 2*maxn) break;
    }

    // for(int i=0;i<n;i++) trace(i, dis[i][0], dis[i][1]); // debug

    vector<pii> vec1 = {{end, 0}};

    while(start.find(vec1.back().first) == start.end()) {
        // {curr, oth} == {0, 1} or {1, 0}
        int curr = vec1.back().second; int oth = !curr;
        if(dis[vec1.back().first][oth] == dis[vec1.back().first][curr] - 1) {
            vec1.pb({vec1.back().first, oth}); continue; 
        } 
        for(auto p : graph1[vec1.back().first]) {
            if(dis[p][oth] == dis[vec1.back().first][curr] - 1) { vec1.pb({p, oth}); break; }
        }
    }

    // trace(vec1); //debug

    vector<int> path_graph[n+1]; 

    for(int i=vec.size()-1;i>=1;i--) {
        if(vec[i].second == 1) {
            path_graph[vec[i].first].push_back(vec[i-1].first);
        }
    }

    for(int i=vec1.size()-1;i>=1;i--) {
        if(vec1[i].second == 1) {
            path_graph[vec1[i].first].push_back(vec1[i-1].first);
        }
        else if(vec1[i].second == 0 && vec1[i].first != vec1[i-1].first) {
            path_graph[vec1[i-1].first].erase(find(all(path_graph[vec1[i-1].first]), vec1[i].first));
        }
    }

    int st = vec[vec.size() - 1].first; p1.push_back(st); 

    while(p1[p1.size() - 1] != end) {
        int lst = p1[p1.size() - 1];
        p1.push_back(path_graph[lst][0]); 
        path_graph[lst].erase(path_graph[lst].begin());
    }

    st = vec1[vec1.size() - 1].first; p2.push_back(st);

    while(p2[p2.size() - 1] != end) {
        int lst = p2[p2.size() - 1];
        p2.push_back(path_graph[lst][0]); 
        path_graph[lst].erase(path_graph[lst].begin());
    }

    trace(p1, p2);
}


int main() {
    io; 
    int t = 1;
    // cin >> t;
    while(t--) {
        
        cin >> n >> m; 
        for(int i=0;i<m;i++) {
            int a, b; cin >> a >> b; a--; b--;
            graph1[a].push_back(b); graph1[b].push_back(a);
            graph2[a][0].insert({a, 1}); graph2[a][1].insert({b, 0});
            graph2[b][0].insert({b, 1}); graph2[b][1].insert({a, 0});

        }
        // debug
        // for(int i=0;i<n;i++) trace(i, graph1[i]);
        // for(int i=0;i<n;i++) trace(i, graph2[i][0], graph2[i][1]);
        int q; cin >> q; 
        while(q--) {
            int st, en; cin >> st >> en; st--; en--;
            set<int> start = {st};
            find(start, en);
        }

    }
}


/*

TestCase :- 

TC - 1

10 13
1 2
1 10
1 3
2 3
10 9
3 4
3 8
9 8
4 5
8 6
8 7
7 6
5 6
1
1 6

TC - 2

12 14
1 2
1 5 
1 10
2 3
5 7
10 11
3 4
7 8
11 12
4 6 
8 9
12 6
9 6
5 4
1
1 11


*/

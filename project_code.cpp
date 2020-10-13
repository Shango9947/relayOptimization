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

int i, j, k;

int total_node, total_relay, total_sink, r_jam, r_relay; 

struct node {
    int index, type, x, y;
    // type = {0, 1, 2} = {base, relay, sink}

    bool operator < (node p) {
        return index < p.index;
    }
};

vector<node> Nodes; vector<pii> position; 
vector<node> Relay; vector<node> Sink; struct node Base; 
// 0 -> in, 1-> out
vector<vi> adjacent_list; vector<vpii> disjoint_adjacent_list[2]; 

void paramter_input() {
    cin >> total_node >> total_relay >> total_sink >> r_jam >> r_relay;
    // trace(total_node, total_relay, total_sink, r_jam, r_relay);
}

void input() {
    Nodes.resize(total_node); position.resize(total_node); adjacent_list.resize(total_node);

    for(int i=0;i<total_node;i++) {
        int x, y; cin >> x >> y;

        int type = 0;
        if(i > 0 && i <= total_relay) type = 1; 
        else if(i > total_relay) type = 2; 

        Nodes[i] = {i, type, x, y};
        position[i] = {x, y};
        if(type == 0) Base = {i, type, x, y};
        else if(type == 1) Relay.push_back({i, type, x, y});
        else Sink.push_back({i, type, x, y});
    }

}

int distance(int i, int j) {
    return (pow(position[i].first - position[j].first, 2) + pow(position[i].second - position[j].second, 2));
}

bool connection(int i, int j, int r) {
    if(distance(i, j) <= r*r) return true;
    return false; 
}

void build_graph() {

    disjoint_adjacent_list[0].resize(total_node); disjoint_adjacent_list[1].resize(total_node);

    for(int i=0;i<total_node;i++) {

        disjoint_adjacent_list[0][i].push_back({1, i}); 
        
        for(int j=i+1;j<total_node;j++) {

            if(connection(i, j, r_relay)) {

                adjacent_list[i].push_back(j), adjacent_list[j].push_back(i);
                disjoint_adjacent_list[1][i].push_back({0, j}); 
                disjoint_adjacent_list[1][j].push_back({0, i});

            }

        }

    }

    // trace(adjacent_list);
    // trace(disjoint_adjacent_list[0]);
    // trace(disjoint_adjacent_list[1]);
}

bool consist(set<int> &s, int i) {
    if(s.find(i) != s.end()) return true;
    return false;
}

void show(deque<pii> que) {
    int a = que.size();
    while(a--) {
        pii fro = que.front(); que.pop_front(); que.push_back(fro);
        cout << '{' << fro.first << " " << fro.second << "} "; 
    }
    cout << "\n";
}

pair<vi, vi> findNodeDisjointPaths(set<int> start, int end) {
    
    deque<pii> que; int dis[2][total_node]; 
    for(int i=0;i<total_node;i++) dis[0][i] = 2e5, dis[1][i] = 2e5;
    for(auto p : start) que.pb({1, p}), dis[1][p] = 0, dis[0][p] = -1;

    while(!que.empty()) {
        pii fro = que.front(); que.pop_front();
        for(auto p : disjoint_adjacent_list[fro.first][fro.second]) {

            if(dis[p.first][p.second] != 2e5) continue;
            dis[p.first][p.second] = dis[fro.first][fro.second] + 1; 
            que.push_back(p);

        }
        if(dis[0][end] != 2e5) break;
    }

    if(dis[0][end] == 2e5) return {{}, {}};

    vector<pii> vec = {{0, end}};

    while(true) {
        pii prev_node = vec.back(); //[type, node_number]
        if(consist(start, prev_node.second)) break;

        int type = prev_node.first; int other_type = type^1;
        int node_number = prev_node.second; 

        if(dis[other_type][node_number] == dis[type][node_number] - 1) {
            vec.pb({other_type, node_number}); continue; 
        } 

        for(auto p : adjacent_list[node_number]) {
            if(dis[other_type][p] == dis[type][node_number] - 1) { vec.pb({other_type, p}); break; }
        }
    }

    map<pii, set<pii>> remove, add; 

    for(int i=1;i<vec.size();i++) {
        int a1 = vec[i].first; int b1 = vec[i-1].first; int a2 = vec[i].second; int b2 = vec[i-1].second;
        remove[{a1, a2}].insert({b1, b2}); add[{b1, b2}].insert({a1, a2});
    }

    // trace(vec);
    // trace(remove, add);

    que.clear();
    for(int i=0;i<total_node;i++) dis[0][i] = 2e5, dis[1][i] = 2e5;

    for(auto p : start) que.pb({1, p}), dis[1][p] = 0, dis[0][p] = -1;

    while(!que.empty()) {
        pii fro = que.front(); que.pop_front();
        for(auto p : disjoint_adjacent_list[fro.first][fro.second]) {
            if(remove[fro].find(p) != remove[fro].end()) continue; 
            if(dis[p.first][p.second] != 2e5) continue;
            dis[p.first][p.second] = dis[fro.first][fro.second] + 1; 
            que.push_back(p);
        }
        for(auto p : add[fro]) {
            if(dis[p.first][p.second] != 2e5) continue;
            dis[p.first][p.second] = dis[fro.first][fro.second] + 1; 
            que.push_back(p);
        } 
        // show(que);
        if(dis[0][end] != 2e5) break;
    }

    if(dis[0][end] == 2e5) return {{}, {}};

    vector<pii> vec1 = {{0, end}};

    while(true) {
        pii prev_node = vec1.back(); //[type, node_number]
        if(consist(start, prev_node.second)) break;

        int type = prev_node.first; int other_type = type^1;
        int node_number = prev_node.second; 

        if(dis[other_type][node_number] == dis[type][node_number] - 1) {
            vec1.pb({other_type, node_number}); continue; 
        } 

        for(auto p : adjacent_list[node_number]) {
            if(dis[other_type][p] == dis[type][node_number] - 1) { vec1.pb({other_type, p}); break; }
        }
    }

    // trace(vec1);
    
    vector<int> path_graph[total_node]; vi p1, p2;

    for(int i=vec.size()-1;i>=1;i--) {
        if(vec[i].first == 1) {
            path_graph[vec[i].second].push_back(vec[i-1].second);
        }
    }

    for(int i=vec1.size()-1;i>=1;i--) {
        if(vec1[i].first == 1) {
            path_graph[vec1[i].second].push_back(vec1[i-1].second);
        }
        else if(vec1[i].first == 0 && vec1[i].second != vec1[i-1].second) {
            path_graph[vec1[i-1].second].erase(find(all(path_graph[vec1[i-1].second]), vec1[i].second));
        }
    }

    int st = vec[vec.size() - 1].second; p1.push_back(st); 

    while(p1[p1.size() - 1] != end) {
        int lst = p1[p1.size() - 1];
        p1.push_back(path_graph[lst][0]); 
        path_graph[lst].erase(path_graph[lst].begin());
    }

    st = vec1[vec1.size() - 1].second; p2.push_back(st);

    while(p2[p2.size() - 1] != end) {
        int lst = p2[p2.size() - 1];
        p2.push_back(path_graph[lst][0]); 
        path_graph[lst].erase(path_graph[lst].begin());
    }

    // trace(p1, p2);

    return {p1, p2};

}

int main() {
    
    // input -> total_node, total_relay, total_sink, r_jam, r_relay
    // base
    // relay
    // sink

    paramter_input();
    input();
    build_graph();
    pair<vi, vi> paths = findNodeDisjointPaths({0}, 9);

}


/*

10 9 1 4 4
0 0 
1 1
4 0
4 4
8 4
6 0
1 -3
5 -3
7 -1
8 0

TC - 2
10 9 1 2 4
0 0 
1 1
3 1
4 4
8 4
6 0
1 -3
5 -3
8 0


*/
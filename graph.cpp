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
typedef set<int> si;
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
#define F first
#define S second
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

int total_node, total_relay, total_sink; double  r_jam, r_relay, safe_radius; 

struct node {
    int index, type; double x, y;
    // type = {0, 1, 2} = {base, relay, sink}

    bool operator < (node p) {
        return index < p.index;
    }
};

struct Edge {
    double x1, x2, y1, y2; 
};

vector<node> Nodes; vector<pdd> position; 
vector<node> Relay; vector<node> Sink; struct node Base; 
// 0 -> in, 1-> out
vector<vi> adjacent_list; vector<vpii> disjoint_adjacent_list[2]; 

/*********************************** Defined Varibales *************************************/

void paramter_input() {
    cin >> total_node >> total_relay >> total_sink >> r_jam >> r_relay >> safe_radius;
    // trace(total_node, total_relay, total_sink, r_jam, r_relay, safe_radius);
}

void input() {
    Nodes.resize(total_node); position.resize(total_node); adjacent_list.resize(total_node);

    for(int i=0;i<total_node;i++) {
        double x, y; cin >> x >> y;

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

/*********************************** Take Input Code *************************************/

double distance(int i, int j) {
    return sqrt((pow(position[i].first - position[j].first, 2) + pow(position[i].second - position[j].second, 2)));
}

double distance(int i, pdd p2) {
    return sqrt((pow(position[i].first - p2.first, 2) + pow(position[i].second - p2.second, 2)));
}

double distance(pdd p1, pdd p2) {
    return sqrt((pow(p1.first - p2.first, 2) + pow(p2.second - p1.second, 2)));
}

bool connection(int i, int j, double r) {
    if(distance(i, j) <= r) return true;
    return false; 
}

vector<Edge> v;

void build_graph() {
    for(int i=0;i<total_node;i++) {
        for(int j=i+1;j<total_node;j++) {
            if(connection(i, j, r_relay)) {
                v.pb({position[i].first, position[j].first, position[i].second, position[j].second});
            }
        }
    }

    // trace(adjacent_list); trace(disjoint_adjacent_list[0]); trace(disjoint_adjacent_list[1]);
}


/*********************************** Find node disjoint path and supporting funtion *************************************/

int main() {
    
    // input -> total_node, total_relay, total_sink, r_jam, r_relay
    // base
    // relay
    // sink

    paramter_input();
    input();
    build_graph();

    // x = [0 0 NaN 1 1 NaN 2 3];
    // y = [1 2 NaN 3 4 NaN 6 7];
    // plot(x, y, '--');    %no marker!
    int n = v.size();
    cout << "x = [";

    for(int i=0;i<v.size()-1;i++) {
        cout << v[i].x1 << " " << v[i].x2 << " NaN ";
    }
    cout << v[n-1].x1 << " " << v[n-1].x2 << "];\n";
    cout << "y = [";
    for(int i=0;i<v.size()-1;i++) {
        cout << v[i].y1 << " " << v[i].y2 << " NaN ";
    }
    cout << v[n-1].y1 << " " << v[n-1].y2 << "];\n";

    cout << "plot(x, y, 'LineWidth', 3);    %no marker!\n";

    cout << "hold on\n";

    cout << "x1 = [" << position[0].F;
    for(int i=1;i<total_node;i++) {
        cout << " " << position[i].F;
    }
    cout << "];\n";
    cout << "y1 = [" << position[0].S;
    for(int i=1;i<total_node;i++) {
        cout << " " << position[i].S;
    }
    cout << "];\n";
    // cout << "labels = 0:" << total_node-1 << ";\n";

    cout << "labels = [";
    for(int i=0;i<total_node-1;i++) {
        cout << "'" <<  i << "'" << ';';
    }
    cout << "'" << total_node-1 << "'" << "]\n";

    cout << "plot(x1, y1, 'r.', 'MarkerSize', 25, 'LineStyle', 'none');\n";
    cout << "text(x1,y1,labels,'VerticalAlignment','bottom','HorizontalAlignment','right', 'FontSize', 15);\n";
}


/*

10 8 1 4 4
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
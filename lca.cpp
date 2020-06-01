#define _CRT_SECURE_NO_DEPRECATE
#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include<bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
//using namespace __gnu_pbds; 
using namespace std;
#define int long long int
#define SYNC std::ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL);
#define FRE freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
typedef long double ld;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
typedef vector<int> vi;
typedef vector<ii>   vii;
//typedef tree<int, null_type, less<int>, rb_tree_tag, 
//             tree_order_statistics_node_update> 
//    data_set;
#define rep(i,l,r)   for(int i=(l);i<(r);i++)
#define deb(x)     cout << (#x) << " is " << (x) << endl
#define dbg(x)     cout << x << ' '
#define here cout << " Hey baitch!!\n";
#define  pb push_back
#define  F  first
#define  S  second
#define all(v) (v).begin(),(v).end()
#define sz(a) (int)((a).size())
#define sq(x) ((x)*(x))
const int MOD = 1e9+7;
const int MOD1 = 998244353;
const int N = 2e5+5;
const int INF = 1000111000111000111LL;
const ld PI = 3.1415926535898;
int n,lg;
vector<int> g[N];
int timer = 0;
vector<int> tin,tout,depth;
vector<vector<int>> up;
void dfs(int node, int par) 
{
	tin[node] = ++timer;
	up[node][0] = par;
	for(int i = 1; i <= lg; i++) {
		up[node][i] = up[up[node][i-1]][i-1];
	}
	for(auto to : g[node]) {
		if(to != par)
			depth[to] = depth[node] + 1,	
			dfs(to,node);
			
	}
	tout[node] = ++timer;
	return;
}
bool is_ancestor(int u, int v) {
	return tin[u] <= tin[v] && tout[u] >= tout[v];
}
int lca(int u, int v) {
	if(is_ancestor(u,v))	return u;
	if(is_ancestor(v,u))	return v;
	for(int i = lg; i >= 0; i--) {
		if(!is_ancestor(up[u][i],v)) {
			u = up[u][i];
		}
	}
	return up[u][0];
}
int dist(int u, int v) {
	int anc = lca(u,v);
	return depth[u] + depth[v] - 2*depth[anc];
}
void pre_process(int root) {
	tin.resize(n);
	tout.resize(n);
	depth.resize(n);
	timer = 0;
	lg = ceil(log2(n));
	up.assign(n, vector<int>(lg+1));
	depth[root] = 0;
	dfs(root,root);
}
int32_t main()
{
	SYNC
	cin >> n;
	for(int i = 0; i < n-1; i++) {
		int u,v; cin >> u >> v;
		u--,v--;
		g[u].pb(v);
		g[v].pb(u);
	} 
	pre_process(0);
	int q; cin >> q;
	while(q--)
	{
		
	}
    return 0;
}
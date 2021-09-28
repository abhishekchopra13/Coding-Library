#define _CRT_SECURE_NO_DEPRECATE
#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include "bits/stdc++.h"
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
//using namespace __gnu_pbds;
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
//    ost;
#define rep(i,l,r)   for (int i = (l); i < (r); i++)
#define here cout << " Hey!!\n";
#define  pb push_back
#define  F  first
#define  S  second
#define all(v) (v).begin(),(v).end()
#define sz(a) (int)((a).size())
#define sq(x) ((x)*(x))
template <typename T>
void etch(T V) {
    for (auto x : V)    cout << x << ' ' ;
    cout << '\n';
}
vector<string> vec_splitter(string s) {
    s += ',';
    vector<string> res;
    while(!s.empty()) {
        res.push_back(s.substr(0, s.find(',')));
        s = s.substr(s.find(',') + 1);
    }
    return res;
}
void debug_out(
        vector<string> __attribute__ ((unused)) args,
        __attribute__ ((unused)) int idx,
        __attribute__ ((unused)) int LINE_NUM) { cerr << endl; }
template <typename Head, typename... Tail>
void debug_out(vector<string> args, int idx, int LINE_NUM, Head H, Tail... T) {
    if(idx > 0) cerr << ", "; else cerr << "Line(" << LINE_NUM << ") ";
    stringstream ss; ss << H;
    cerr << args[idx] << " = " << ss.str();
    debug_out(args, idx + 1, LINE_NUM, T...);
}
#ifndef ONLINE_JUDGE
#define debug(...) debug_out(vec_splitter(#__VA_ARGS__), 0, __LINE__, __VA_ARGS__)
#else
#define debug(...) 42
#endif
const int MOD = 1e9+7;
const int MOD1 = 998244353;
const int N = 1e5+5;
const int INF = 1000111000111000111LL;
const ld EPS = 1e-12;
const ld PI = 3.141592653589793116;

int col[N], sz[N], ans[N], freq[N];
bool big[N];
map<int, int>* cnt[N];
vector<int> g[N];

void getsz(int v, int p){
    sz[v] = 1;  // every vertex has itself in its subtree
    for(auto u : g[v])
        if(u != p){
            getsz(u, v);
            sz[v] += sz[u]; // add size of child u to its parent(v)
        }
}

void dfs(int v, int p = -1){
    int mx_sz = -1, bigChild = -1;
    for (auto u : g[v]) {
        if (u != p && sz[u] > mx_sz) {
            mx_sz = sz[u];
            bigChild = u;
        }
        if (u != p)
            dfs(u, v);
    }
    int max_freq = 0;
    if (bigChild != -1) {
        cnt[v] = cnt[bigChild];
        max_freq = freq[bigChild];
    } else {
        cnt[v] = new map<int, int> ();
    }
    (*cnt[v])[col[v]]++;
    for (auto u : g[v]) {
        if (u == p or u == bigChild)
            continue;
        for (auto x : *cnt[u]) {
            (*cnt[v])[x.first] += x.second;
            max_freq = max(max_freq, (*cnt[v])[x.first]);
        }
    }
    max_freq = max(max_freq, (*cnt[v])[col[v]]);
    if (bigChild != -1 && max_freq == freq[bigChild]) {
        ans[v] = ans[bigChild];
    }
    set<int> taken;
    for (auto u : g[v]) {
        if (u == p or u == bigChild)
            continue;
        for (auto x : *cnt[u]) {
            if ((*cnt[v])[x.first] == max_freq) 
                taken.insert(x.first);
        }
    }
    ans[v] += accumulate(taken.begin(), taken.end(), 0LL);
    if ((*cnt[v])[col[v]] == max_freq && !taken.count(col[v])) {
        ans[v] += col[v];
    }
    freq[v] = max_freq;
}
// Problem Link: https://codeforces.com/contest/600/problem/E
// Tutorial: https://codeforces.com/blog/entry/44351
int32_t main()
{
    SYNC
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> col[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    getsz(0 /*root*/, 0);
    dfs(0);
    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }
    return 0;
}
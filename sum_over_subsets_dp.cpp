// https://codeforces.com/blog/entry/45223
#define _CRT_SECURE_NO_DEPRECATE
#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include "bits/stdc++.h"
using namespace std;
#define int long long
#define SYNC std::ios_base::sync_with_stdio(0); cout.tie(nullptr);
#define FRE freopen("input.txt","r",stdin);freopen("output.txt","w",stdout)

void __print(int x) {cerr << x;}
void __print(int32_t x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}

template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...) 42
#endif

const int MOD = 1e9 + 7;
const int MOD1 = 998244353;
const int INF = 1000111000111000111LL;
const long double EPS = 1e-12;
const long double PI = 3.141592653589793116;

const int K = 22;
const int N = (1LL<<K);

int complement1(int x) {
    return N - x - 1;
}

bool a[N];
int32_t dp[N];

int32_t main() {
    SYNC
    int n; cin >> n;
    vector<int32_t> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        a[v[i]] = 1;
    }
    memset(dp, -1, sizeof dp);
    for (int i = 0; i < N; i++) {
        if (a[i])
            dp[i] = i;
    }
    for (int i = 0; i < K; i++) {
        for (int mask = 0; mask < (1LL<<K); mask++) {
            if (mask & (1LL<<i)) {
                dp[mask] = max(dp[mask], dp[mask ^ (1LL<<i)]);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        int ca = complement1(v[i]);
        cout << dp[ca] << ' ';
    }
    return 0;
}
/*
//iterative version
for(int mask = 0; mask < (1<<N); ++mask){
    dp[mask][-1] = A[mask]; //handle base case separately (leaf states)
    for(int i = 0;i < N; ++i){
        if(mask & (1<<i))
            dp[mask][i] = dp[mask][i-1] + dp[mask^(1<<i)][i-1];
        else
            dp[mask][i] = dp[mask][i-1];
    }
    F[mask] = dp[mask][N-1];
}

//memory optimized, super easy to code.
for(int i = 0; i<(1<<N); ++i)
    F[i] = A[i];
for(int i = 0;i < N; ++i) for(int mask = 0; mask < (1<<N); ++mask){
    if(mask & (1<<i))
        F[mask] += F[mask^(1<<i)];
}
*/
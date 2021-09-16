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
const int N = 3e6+5;
const int INF = 1000111000111000111LL;
const ld EPS = 1e-12;
const ld PI = 3.141592653589793116;

int modular_exp(int base, int exp, int mod = MOD) 
{
    int ans =1;
    while(exp)
    {
        if(exp % 2)   ans = ans%mod*base%mod;
        base = (base%mod*base%mod)%mod;
        exp /= 2;
        ans %= mod;
    }
    return ans;
}
int inv_mod(int base,int mod) {
    return modular_exp(base,mod-2,mod);
}

void add(int &a, int b) {
    a += b;
    (a >= MOD) && (a -= MOD);
}

int dp[N][31];
int fact[N];

void pre_compute() {
    fact[0] = 1;
    for(int i = 1; i < N; i++) {
        fact[i] = (i * fact[i-1]) % MOD;
    }
}

int lagrange(vector<int> &f, int n) {
    int k = (int)f.size();
    vector<int> prefNum(k), suffNum(k + 1, 1);
    prefNum[0] = n;
    for (int i = 1; i < k; i++) {
        prefNum[i] = (prefNum[i - 1] * (n - i)) % MOD;
    }
    suffNum[k - 1] = (n - (k - 1));
    for (int i = k - 2; i >= 0; i--) {
        suffNum[i] = ((n - i) * suffNum[i + 1]) % MOD;
    }
    int res = 0;
    for (int i = 0; i < k; i++) {
        int num = 1;
        if (i)
            num = prefNum[i - 1];
        num *= suffNum[i + 1];
        num %= MOD;
        if (num < 0)
            num += MOD;
        int den = (fact[k - 1 - i] * fact[i]) % MOD;
        if ((k - 1 - i) % 2)
            den = MOD - den;
        den %= MOD;
        int coeff = (num * inv_mod(den, MOD)) % MOD;
        add(res, (f[i] * coeff)%MOD);
    }
    return res;
}

int32_t main()
{
    SYNC
    // https://codeforces.com/blog/entry/82953
    pre_compute();
    int n, m, k; cin >> n >> m >> k;
    n %= MOD;
    for (int i = 0; i <= k + m; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == 0) {
                dp[i][j] = 0;
            } else if (j == 0) {
                dp[i][j] = modular_exp(i, k);
            } else {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                dp[i][j] %= MOD;
            }
        }
    }
    // rep(i,0,5) {
    //     rep(j,0,5) {
    //         cout << dp[i][j] << ' ';
    //     } cout << '\n';
    // }
    vector<int> f;
    for (int i = 0; i <= k + m; i++) {
        f.push_back(dp[i][m]);
    }
    // etch(f);
    cout << lagrange(f, n);
    return 0;
}
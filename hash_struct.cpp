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
const int MOD = 1e9+207;
const int MOD1 = 998244353;
const int N = 1e3+5;
const int INF = 1000111000111000111LL;
const ld EPS = 1e-12;
const ld PI = 3.141592653589793116;

const int mod_hash = 1e9+207;
const int p = 31;
const int p1 = 29;
const int mod_hash1 = 1e9+7;

int modular_exp(int base,int exp,int mod)
{
    int ans =1;
    while(exp)
    {
        if(exp%2)   ans = ans%mod*base%mod;
        base = (base%mod*base%mod)%mod;
        exp/=2;
        ans%=mod;
    }
    return ans;
}
int inverse_modulo(int base,int mod)
{
    return modular_exp(base,mod-2,mod);
}
int p_inv[N];
int p_inv1[N];
int dp[N][N][3];


struct str_hash
{
    string s;
    vector<int> pre;
    vector<int> pre1;
    str_hash(string s) {
        this->s = s;
        compute_hash();
        //etch(pre);
    }
    void compute_hash()
    {
        int hash_val = 0, hash_val1 = 0;
        int p_pow = 1;
        vector<int> pre_compute, pre_compute1;
        for(auto c : s) {
            hash_val = (hash_val + (c-'A'+1)*p_pow) % mod_hash;
            p_pow = (p_pow * p) % mod_hash;
            pre_compute.push_back(hash_val);
        }
        p_pow = 1;
        for(auto c : s) {
            hash_val1 = (hash_val1 + (c-'A'+1)*p_pow) % mod_hash1;
            p_pow = (p_pow * p1) % mod_hash1;
            pre_compute1.push_back(hash_val1);
        }
        this->pre = pre_compute;
        this->pre1 = pre_compute1;
    }
    pair<int, int> get_hash(int l, int r)
    {
        if(l==0)    return {pre[r], pre1[r]};
        int res = (pre[r] - pre[l-1]+mod_hash)%mod_hash;
        res *= p_inv[l];
        int res1 = (pre1[r] - pre1[l-1]+mod_hash1)%mod_hash1;
        res1 *= p_inv1[l];
        return {res % mod_hash, res1 % mod_hash1};
    }
};

void solve()
{
    string s, t;
    cin >> s >> t;
    reverse(all(t));
    str_hash v1(s), v2(t);
    memset(dp, 0, sizeof dp);
    int n = sz(s), m = sz(t);
    int ans = 0;
    for (int j = 0; j < m; j++) {
        if (t[j] == s[0]) {
            dp[0][j][2] = dp[0][j][1] = dp[0][j][0] = 1;
            ans = 1;
        }
    }
    for (int i = 0; i < n; i++) {
        if (s[i] == t[0]) {
            dp[i][0][2] = dp[i][0][1] = dp[i][0][0] = 1;
            ans = 1;
        }
    }
    // cout << s << '\n' << t << '\n';
    // if (v1.get_hash(0, 1) == v2.get_hash(1,2)) {
    //     here;
    // }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            dp[i][j][1] = max(dp[i-1][j][1], dp[i][j-1][1]);
            ans = max(ans, dp[i][j][1]);
            if (s[i] != t[j])   continue;
            int lo = 1, hi = min(i+1, j+1);
            while (lo < hi) {
                int len = (lo + hi + 1)/2;
                if (v1.get_hash(i-len+1, i) == v2.get_hash(j-len+1, j)) {
                    lo = len;
                } else {
                    hi = len - 1;
                }
            }
            dp[i][j][1] = max(dp[i][j][1], lo);
            dp[i][j][2] = lo;
            if (i-lo >= 0 && j-lo >= 0) {
                dp[i][j][2] += dp[i-lo][j-lo][1];
            }
            ans = max({ans, dp[i][j][1], dp[i][j][2], lo});
        }
    }
    cout << 2*ans << '\n';
}

int32_t main()
{
    SYNC
    int inv = inverse_modulo(p,mod_hash);
    p_inv[0] = 1;
    for(int i = 1; i < N; i++) p_inv[i] = (inv * p_inv[i-1])%mod_hash;

    int inv1 = inverse_modulo(p1,mod_hash1);
    p_inv1[0] = 1;
    for(int i = 1; i < N; i++) p_inv1[i] = (inv1 * p_inv1[i-1])%mod_hash1; 
    
    int T; cin >> T;
    while(T--)
    {
        solve();
    }
    return 0;
}
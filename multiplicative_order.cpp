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
int MOD = 1e9+7;
const int MOD1 = 998244353;
const int N = 1e6+125;
const int INF = 1000111000111000111LL;
const ld EPS = 1e-12;
const ld PI = 3.141592653589793116;

std::vector <int> prime;
bool is_composite[N];

void sieve (int n) {
    std::fill (is_composite, is_composite + n, false);
    for (int i = 2; i < n; ++i) {
        if (!is_composite[i]) prime.push_back (i);
        for (int j = 0; j < prime.size () && i * prime[j] < n; ++j) {
            is_composite[i * prime[j]] = true;
            if (i % prime[j] == 0) break;
        }
    }
}

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

int multiplicative_order(int a, int Q) {
    for (auto p : prime) {
        if (modular_exp(a, p, Q) == 1) return p;
    }
    return 1;
}

int inv_mod(int base,int mod)
{
    return modular_exp(base,mod-2,mod);
}
int fact[N];
void pre_compute()
{
    fact[0] = 1;
    for(int i = 1;i < N;i++)
    {
        fact[i] = i*fact[i-1];
        fact[i]%=MOD;
    }
}
int nCr(int n, int r)
{
    if(r>=n or r==0)
        return 1;
    return ( (fact[n]%MOD * inv_mod(fact[r],MOD)%MOD) * inv_mod(fact[n-r],MOD))%MOD;
}

void add(int &a, int b) {
    a += b;
    if (a >= MOD)
        a -= MOD;
}

int32_t main()
{
    SYNC
    sieve(N);
    int n, m, a, Q;
    cin >> n >> m >> a >> Q;
    vi v(n);
    MOD = multiplicative_order(a, Q);
    pre_compute();
    v[n-1] = a % Q;
    int r = 1, cum = 1;
    // debug(fact[0], fact[1], fact[2]);
    // cout << nCr(2, 1) << endl;
    // return 0;
    for (int i = n - 2; i >= 0; i--) {
        if (n - i <= m) {
            add(cum, nCr(m, r++));
            v[i] = modular_exp(a, cum, Q);
        } else {
            int exp = modular_exp(2, m, MOD);
            v[i] = modular_exp(a, exp, Q);
        }
    }
    etch(v);
    return 0;
}
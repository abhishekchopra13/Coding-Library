/* Press F to pay respects */
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

// Combnitorics Snippet, Call precompute()
int fact[N], ifact[N];
int modular_exp(int base, int exp, int mod = MOD) 
{
    int ans = 1;
    while (exp) {
        if(exp % 2)   ans = ans % mod * base % mod;
        base = (base % mod * base % mod) % mod;
        exp /= 2; ans %= mod;
    }
    return ans;
}
int inv_mod(int base, int mod = MOD) {
    return modular_exp(base, mod - 2, mod);
}
void add(int &a, int b) {
    a += b;
    if (a >= MOD)
        a -= MOD;
}
void mul(int &a, int b) {
    a *= b;
    a %= MOD;
}

void pre_compute() {
    fact[0] = 1;
    for(int i = 1; i < N; i++) {
        fact[i] = (i * fact[i-1]) % MOD;
    }
    ifact[N - 1] = inv_mod(fact[N - 1], MOD);
    for (int i = N - 2; i >= 0; i--) {
        ifact[i] = ((i + 1) * ifact[i + 1]) % MOD;
    }
}
int nCr(int n, int r) {
    if (r > n or r < 0)
        return 0;
    if(r == n or r == 0)
        return 1;
    return ( (fact[n] % MOD * ifact[r] % MOD) * ifact[n - r] ) % MOD;
}


int32_t main()
{
	SYNC
	pre_compute();
    cout << nCr(5, 3);
    return 0;
}

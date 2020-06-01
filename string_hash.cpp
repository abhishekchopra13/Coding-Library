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
const int mod_hash = 110437474552301887;
const int p = 31;
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
vector<int> pre;
int p_inv[N];
vector<int> compute_hash(string &s)
{
	int hash_val = 0;
	int p_pow = 1;
	vector<int> pre_compute;
	for(auto c : s) {
		hash_val = (hash_val + (c-'a'+1)*p_pow) % mod_hash;
		p_pow = (p_pow * p) % mod_hash;
		pre_compute.push_back(hash_val);
	}
	return pre_compute;
}
int get_hash(int l, int r)
{
	if(l==0)	return pre[r];
	int res = (pre[r] - pre[l-1]+mod_hash)%mod_hash;
	res *= p_inv[l];
	return res % mod_hash;
}
void solve()
{
	string s; cin >> s;
	pre = compute_hash(s);
	int n = sz(s);
	// for(auto it : pre)	deb(it);
	// cout << get_hash(0,1) << ' ' << get_hash(2,3) << '\n';
	int ans = 0;
	for(int i = 1; i <= n-3; i+=2)
	{
		int h1 = get_hash(0, (i-1)/2);
		int h2 = get_hash((i+1)/2, i);
		int h3 = get_hash(i+1,(n+i-1)/2);
		int h4 = get_hash((n+i+1)/2,n-1);
		if(h1 == h2 && h3 == h4)	ans++;
	}
	cout << ans << '\n';
}
int32_t main()
{
	SYNC
	int inv = inverse_modulo(p,mod_hash);
	p_inv[0] = 1;
	for(int i = 1; i < N; i++) p_inv[i] = (inv * p_inv[i-1])%mod_hash; 
	int T; cin >> T;
	while(T--)
	{
		solve();
	}
    return 0;
}
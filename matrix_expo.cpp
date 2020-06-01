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
typedef vector< vi > vvi;
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
vvi multiply(vvi a, vvi b, int mod = MOD)
{
	int n = sz(a);
	vvi res;
	res.resize(n);
	for(int i = 0; i < n; i++)
	{	
		res[i].resize(n);
		for(int j = 0; j < n; j++)
		{
			int cnt = 0;
			for(int k = 0; k < n; k++)
			{
				cnt += a[i][k]*b[k][j];
				cnt %= mod;
			}
			res[i][j] = cnt;
		}
	}
	return res;
}
int32_t main()
{
	SYNC
	int n,f1,f2,f3,c;
	cin >> n >> f1 >> f2 >> f3 >> c;
	vvi fib,res;
	f1 *= c; f1 %= MOD;
	f2 *= modular_exp(c,2,MOD); f2 %= MOD;
	f3 *= modular_exp(c,3,MOD); f3 %= MOD;
	res.resize(3);
	fib.resize(3);
	res[0] = res[1] = res[2] = {0,0,0};
	res[0][0] = res[1][1] = res[2][2] = 1;
	fib[0] = {1,1,1}, fib[1] = {1,0,0}, fib[2] = {0,1,0};
	int ans = 1;
	int exp = n-3;
	while(exp)
	{
		if(exp%2)
			res = multiply(res,fib,MOD-1);
		fib = multiply(fib,fib,MOD-1);
		exp/=2;
	}
	ans *= modular_exp(f3,res[0][0],MOD);ans %= MOD;
	ans *= modular_exp(f2,res[0][1],MOD);ans %= MOD;
	ans *= modular_exp(f1,res[0][2],MOD);ans %= MOD;
	ans *= inverse_modulo(modular_exp(c,n,MOD),MOD);
	ans %= MOD;
	cout << ans;
 
    return 0;
}
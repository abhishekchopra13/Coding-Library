#define _CRT_SECURE_NO_DEPRECATE
#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include<bits/stdc++.h>
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
//    data_set;
#define rep(i,l,r)   for(int i=(l);i<(r);i++)
#define deb(x)     cout << (#x) << " = " << (x) << endl
#define here cout << " Hey!!\n";
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
const ld EPS = 1e-12;
const ld PI = 3.141592653589793116;

struct dsu
{
	vector<int> a, bulk;
	int components;
	dsu(int n)
	{
		a.resize(n+1);
		bulk.resize(n+1,1);
		this->components = n;
		for(int i = 0; i <= n; i++) {
			a[i] = i;
		}
	};
	int root(int i)
	{
	    while(a[i]!=i)
	    {
	        i = a[i];
	        a[i]= a[a[i]];
	    }
	    return i;
	}
	void merge(int x,int y)
	{
		if(root(x) != root(y))	
			components--;
		else
			return;
	    if(bulk[root(x)]>=bulk[root(y)])
	    {
	    	bulk[root(x)]+=bulk[root(y)];
	    	a[root(y)] = a[root(x)];
	    }else
	    {
	    	bulk[root(y)]+=bulk[root(x)];
	    	a[root(x)] = a[root(y)];
	    }
	}
};

int testcase()
{
	int n,q; cin >> n >> q;
	dsu cow(n);
	set< ii > vis;
	while(q--)
	{
		int l,r;
		cin >> l >> r;
		while(l < r && cow.components > 1)
		{
			if(vis.count({l,r}))
				break;
			cow.merge(l,r);
			vis.insert({l,r});
			l++,r--;
		}
		cout << cow.components << '\n';
	}
	return 0;
}

int32_t main()
{
	SYNC
	int T; T = 1;
	while(T--)
	{
		testcase();
	}
	return 0;
}
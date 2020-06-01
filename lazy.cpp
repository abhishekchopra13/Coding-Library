/* Press F to pay respects */
#define _CRT_SECURE_NO_DEPRECATE
#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include<bits/stdc++.h>
#include<sstream>
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

struct seg_tree 
{

    vector<int> bit;
    vector<int> a;
    vector<int> lazy;
    int n;
    seg_tree(int n) {
    	this-> n = n;
    	bit.assign(4*n+5,0);
    	lazy.assign(4*n+5,0);
    }
    seg_tree(vector<int> a) : seg_tree(a.size())
    {
    	this-> a = a;
    	build(0,0,(int)a.size()-1);
    }
	int merge(int x, int y) {
		// Function to return 
		return min(x,y);
	}
	void build(int node, int start, int end)
	{
		if(start == end)
		{
			bit[node] = a[start];
			return;
		}
		int lch = 2*node+1;		//Left Child
		int rch = 2*node+2;		//Right Child
		int mid = (start+end)/2;
		build(lch,start,mid);
		build(rch,mid+1,end);
		bit[node] = merge(bit[lch],bit[rch]);
		return;	
	}
	// Adding on segtree and query for max/min
	void push(int v) {
	    bit[v*2+1] += lazy[v];
	    lazy[v*2+1] += lazy[v];
	    bit[v*2+2] += lazy[v];
	    lazy[v*2+2] += lazy[v];
	    lazy[v] = 0;
	}

	void update(int v, int tl, int tr, int l, int r, int addend) {
	    if (l > r) 
	        return;
	    if (l == tl && tr == r) {
	        bit[v] += addend;
	        lazy[v] += addend;
	    } else {
	        push(v);
	        int tm = (tl + tr) / 2;
	        update(v*2+1, tl, tm, l, min(r, tm), addend);
	        update(v*2+2, tm+1, tr, max(l, tm+1), r, addend);
	        bit[v] = merge(bit[v*2+1], bit[v*2+2]);
	    }
	}

	int query(int v, int tl, int tr, int l, int r) {
	    if (l > r)
	        return INF;
	    if (l <= tl && tr <= r)
	        return bit[v];
	    push(v);
	    int tm = (tl + tr) / 2;
	    return merge(query(v*2+1, tl, tm, l, min(r, tm)), 
	               query(v*2+2, tm+1, tr, max(l, tm+1), r));
	}

};

int32_t main()
{
	SYNC
	int n; cin >> n;
	vi v(n);
	for(auto &it : v)	cin >> it;
	seg_tree sg(v);
	int Q; cin >> Q;
	cin.ignore();
	while(Q--)
	{
		string s;
		getline(cin,s);
		stringstream ss(s);
		int l,r,val;
		ss >> l >> r;
		if(ss >> val)
		{
			if(r >= l)
				sg.update(0,0,n-1,l,r,val);
			else
				sg.update(0,0,n-1,l,n-1,val),sg.update(0,0,n-1,0,r,val);
		}else
		{
			if(r >= l)
				cout << sg.query(0,0,n-1,l,r) << '\n';
			else
				cout << min(sg.query(0,0,n-1,l,n-1),sg.query(0,0,n-1,0,r)) << '\n';
		}
	}
    return 0;
}
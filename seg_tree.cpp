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
int n;
int a[N];
int tree[4*N];
int merge(int x, int y)
{
	//Function to return comparison
	min(x,y);
}
void build(int node, int start, int end)
{
	if(start == end)
	{
		tree[node] = a[start];
		return;
	}
	int lch = 2*node+1;		//Left Child
	int rch = 2*node+2;		//Right Child
	int mid = (start+end)/2;
	build(lch,start,mid);
	build(rch,mid+1,end);
	tree[node] = merge(tree[lch],tree[rch]);
	return;	
}
int query(int node,int start,int end, int l, int r)
{
	if(l>end or r<start or start>end)
		return INF;
	if(l<=start and r>=end)
	{
		return tree[node];
	}
	int lch = 2*node+1;		//Left Child
	int rch = 2*node+2;		//Right Child
	int mid = (start+end)/2;
	return merge(query(lch,start,mid,l,r),query(rch,mid+1,end,l,r));
}
void update(int node,int start , int end , int pos)
{	
	if(start==end)
	{
		tree[node] = start;
		return;
	}
	int mid = (start + end)/ 2;
	int lch = 2*node + 1;
	int rch = 2*node + 2;
	if(pos<=mid)
	{
		update(lch,start,mid,pos);
	}else
	{
		update(rch,mid+1,end,pos);
	}
	tree[node] = merge(tree[lch],tree[rch]);
}
int32_t main()
{
	SYNC
	
    return 0;
}
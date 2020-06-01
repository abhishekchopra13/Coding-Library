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
int n, block = 555;
int cnt[(int)2e6+1],ans;
vi a;
struct pt 
{	
	int l;
	int r;
	int id;
};
bool comp(pt x, pt y)
{
	if(x.l/block != y.l/block)	return x.l/block < y.l/block;
	return x.r < y.r; 
}
int cur_l,cur_r;
void add(int pos)
{
	cnt[a[pos]]++;
	if(cnt[a[pos]]==1)	ans++;
}
void del(int pos)
{
	cnt[a[pos]]--;
	if(cnt[a[pos]] == 0)	ans--;
}
int32_t main()
{
	SYNC
	cin >> n;
	block = sqrt(n);
	a.resize(n);
	rep(i,0,n)	cin >> a[i];
	vector<pt> v;
	int Q; cin >> Q;
	v.resize(Q);
	rep(i,0,Q) {
		cin >> v[i].l >> v[i].r;
		v[i].l--, v[i].r--;
		v[i].id = i;
 	}
 	sort(all(v),comp);
 	ans = cur_l = cur_r = 0;
 	vi res(Q);
 	for(int i = 0; i < Q; i++)
 	{
 		int L = v[i].l , R = v[i].r;
 		while(cur_l < L) {
			del(cur_l);
			cur_l++;
		}
		while(cur_l > L) {
			add(cur_l-1);
			cur_l--;
		}
		while(cur_r <= R) {
			add(cur_r);
			cur_r++;
		}
		while(cur_r > R+1) {
			del(cur_r-1);
			cur_r--;
		}
		res[v[i].id] = ans;
 	}
 	for(auto it : res)	cout << it << '\n';
    return 0;
}
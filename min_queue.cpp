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
void add_element(deque<int>&q, int val)
{
	while(!q.empty() && q.back() > val)	
		q.pop_back();
	q.push_back(val);
}
void remove_element(deque<int>&q, int val)
{
	if(!q.empty() && q.front() == val)	
		q.pop_front();
}
int min_element(deque<int>&q)
{
	return q.front();
}
int32_t main()
{
	SYNC
	int n,m,a,b; cin >> n >> m >> a >> b;
	int g0,x,y,z; cin >> g0 >> x >> y >> z;
	int h[n][m];
	h[0][0] = g0;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			if(i+j == 0)	continue;
			h[i][j] = (g0*x+y)%z;
			g0 = h[i][j];
		}
	}
	// rep(i,0,n) {
	// 	rep(j,0,m)
	// 		cout << h[i][j] << ' ';	
	// 	cout << '\n';
	// }
	// cout << '\n';
	int mn[n][m];
	memset(mn,0,sizeof mn);
	for(int j = 0; j < m; j++)
	{
		deque<int> q;
		for(int i = 0; i < a; i++)	add_element(q,h[i][j]);
		mn[a-1][j] = min_element(q);
		for(int i = a; i < n; i++) 
			add_element(q,h[i][j]), remove_element(q,h[i-a][j]), mn[i][j] = min_element(q);
	}
	// rep(i,0,n) {
	// 	rep(j,0,m)
	// 		cout << mn[i][j] << ' ';	
	// 	cout << '\n';
	// }
	int ans = 0;
	for(int i = a-1; i < n; i++) {
		deque<int> q;
		for(int j = 0; j < b; j++) 
			add_element(q,mn[i][j]);
		ans += min_element(q);
		for(int j = b; j < m; j++) 
			add_element(q,mn[i][j]), remove_element(q,mn[i][j-b]), ans += min_element(q);
	}
	cout << ans;
    return 0;
}
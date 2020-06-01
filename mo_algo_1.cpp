#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define SYNC std::ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL);
#define FRE freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
typedef vector<int> vi;
#define  pb push_back
#define all(v) (v).begin(),(v).end()
#define sz(a) (int)((a).size())
#define sq(x) ((x)*(x))
const int N = 2e5+5;
int n, block = 555;
int cnt[(int)2e6+1],ans;
int a[N];
struct pt 
{	
	int l;
	int r;
	int id;
};
bool comp(pt &x, pt &y)
{
	// Sorting via sqrt decomposition
	if(x.l/block != y.l/block)	return x.l/block < y.l/block;
	return x.r < y.r; 
}
int cur_l,cur_r;
void add(int pos)
{
	cnt[a[pos]]++;
	// Condition for change in answer 
	ans += (sq(cnt[a[pos]])-sq(cnt[a[pos]]-1))*(a[pos]);
}
void del(int pos)
{
	cnt[a[pos]]--;
	// Condition for change in answer 
	ans += (sq(cnt[a[pos]])-sq(cnt[a[pos]]+1))*(a[pos]);
}
int32_t main()
{
	SYNC
	cin >> n;
	int Q; cin >> Q;
	block = sqrt(n);
	for(int i = 0; i < n; i++)	cin >> a[i];
	vector<pt> v;
	v.resize(Q);
	for(int i = 0; i < Q; i++) {
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
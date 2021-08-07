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
const int MOD = 1e9+7;
const int MOD1 = 998244353;
const int N = 2e5+5;
const int INF = 1000111000111000111LL;
const ld EPS = 1e-12;
const ld PI = 3.141592653589793116;

int lg[N];

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int &x : a)
        cin >> x;
    vector<int> v(n - 1);
    for (int i = 0; i < n - 1; i++)
        v[i] = abs(a[i + 1] - a[i]);
    int len = 1;
    n = n - 1;

    int K = lg[n];

    int st[n][K + 1];

    for (int i = 0; i < n; i++)
        st[i][0] = v[i];

    for (int j = 1; j <= K; j++)
        for (int i = 0; i + (1LL << j) <= n; i++)
            st[i][j] = __gcd(st[i][j-1], st[i + (1LL << (j - 1))][j - 1]);

    for (int i = 0; i < n; i++) {
        int lo = i, hi = n - 1;
        if (v[i] == 1)  continue;
        while (lo < hi) {
            int mid = (lo + hi + 1) / 2;
            int lgb = lg[mid - i + 1];
            if (__gcd(st[i][lgb], st[mid - (1LL<<lgb) + 1][lgb]) > 1) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        len = max(len, lo - i + 2);
    }
    cout << len << '\n';
}

int32_t main()
{
    SYNC
    lg[1] = 0;
    for (int i = 2; i < N; i++)
        lg[i] = lg[i/2] + 1;
    int T; cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
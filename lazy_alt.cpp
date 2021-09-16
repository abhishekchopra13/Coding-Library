// I have no clue if this shit is called segment tree!
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

struct seg_tree 
{

    vector< pair<int, int> > bit, lazy;
    vector<int> a;
    int n;
    seg_tree(int n) {
        this-> n = n;
        bit.assign(4*n+5,{-1, -1});
        lazy.assign(4*n+5,{-1, -1}); 
    }
    seg_tree(vector<int> a) : seg_tree(a.size())
    {
        this-> a = a;
    }
    pair<int, int> merge(pair<int, int> x, pair<int, int> y) {
        // Function to return 
        if (x.F >= y.F)
            return x;
        return y;
    }

    void push(int v) {
        bit[v*2+1] = merge(bit[v*2+1], lazy[v]);
        lazy[v*2+1] = merge(lazy[v*2+1], lazy[v]);
        bit[v*2+2] = merge(bit[v*2+2], lazy[v]);
        lazy[v*2+2] = merge(lazy[v*2+2], lazy[v]);
    }

    void update(int v, int tl, int tr, int l, int r, int val, int id) {
        if (l > r or tl > tr or l > tr or r < tl)
            return;
        if (l <= tl && r >= tr) {
            if (bit[v].F < val) {
                bit[v] = {val, id};
            }
            if (lazy[v].F < val) {
                lazy[v] = {val, id};
            }
            return;
        }
        push(v);
        int tm = (tl + tr) / 2;
        update(2*v+1, tl, tm, l, r, val, id);
        update(2*v+2, tm+1, tr, l, r, val, id);
        bit[v] = merge(bit[2*v+1], bit[2*v+2]);
    }

    pair<int, int> query(int v, int tl, int tr, int l, int r) {

        if (l > r or tl > tr or l > tr or r < tl) {
            return {0, -1};
        }
        if (l <= tl && r >= tr) {
            return bit[v];
        }
        push(v);
        int tm = (tl + tr) / 2;
        return merge(query(2*v+1, tl, tm, l, r), query(2*v+2,tm+1, tr, l, r));
    }

};

struct pt
{
    int l, r;
};


int32_t main()
{
    SYNC
    int n, m; cin >> n >> m;

    vector<pt> v(m);
    vector<pt> a[n];
    set<int> st;
    for (auto &x : v) {
        int idx;
        cin >> idx >> x.l >> x.r;
        a[idx - 1].pb(x);
        st.insert(x.l);
        st.insert(x.r);
    }

    map<int, int> nv;
    int idx = 0;
    for (auto x : st)
        nv[x] = idx++;

    for (int i = 0; i < n; i++) {
        for (auto &x : a[i]) {
            x.l = nv[x.l];
            x.r = nv[x.r];
        }
    }

    int k = idx; // segtree size
    vector<int> vseg(k, 0);
    seg_tree sg(vseg);

    int ans = n;

    vector<int> par(n, -1);
    int pos = -1;
    for (int i = 0; i < n; i++) {
        int len = 1;
        for (auto &x : a[i]) {
            pair<int, int> qr =  sg.query(0, 0, k - 1, x.l, x.r);
            if (qr.F + 1 > len) {
                len = qr.F + 1;
                par[i] = qr.S;
            }
        }
        if (n - len < ans) {
            ans = n - len;
            pos = i;
        }
        // debug(i + 1, len, par[i]);
        for (auto &x : a[i]) {
            sg.update(0, 0, k - 1, x.l, x.r, len, i);
        }
    }
    vector<int> rem(n, 1);
    while (pos != -1) {
        rem[pos] = 0;
        pos = par[pos];
    }
    cout << ans << '\n';

    for (int i = 0; i < n; i++) {
        if (rem[i])
            cout << i + 1 << ' ';// I have no clue if this shit is called segment tree!
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

struct seg_tree 
{

    vector< pair<int, int> > bit, lazy;
    vector<int> a;
    int n;
    seg_tree(int n) {
        this-> n = n;
        bit.assign(4*n+5,{-1, -1});
        lazy.assign(4*n+5,{-1, -1}); 
    }
    seg_tree(vector<int> a) : seg_tree(a.size())
    {
        this-> a = a;
    }
    pair<int, int> merge(pair<int, int> x, pair<int, int> y) {
        // Function to return 
        if (x.F >= y.F)
            return x;
        return y;
    }

    void push(int v) {
        bit[v*2+1] = merge(bit[v*2+1], lazy[v]);
        lazy[v*2+1] = merge(lazy[v*2+1], lazy[v]);
        bit[v*2+2] = merge(bit[v*2+2], lazy[v]);
        lazy[v*2+2] = merge(lazy[v*2+2], lazy[v]);
    }

    void update(int v, int tl, int tr, int l, int r, int val, int id) {
        if (l > r or tl > tr or l > tr or r < tl)
            return;
        if (l <= tl && r >= tr) {
            if (bit[v].F < val) {
                bit[v] = {val, id};
            }
            if (lazy[v].F < val) {
                lazy[v] = {val, id};
            }
            return;
        }
        push(v);
        int tm = (tl + tr) / 2;
        update(2*v+1, tl, tm, l, r, val, id);
        update(2*v+2, tm+1, tr, l, r, val, id);
        bit[v] = merge(bit[2*v+1], bit[2*v+2]);
    }

    pair<int, int> query(int v, int tl, int tr, int l, int r) {

        if (l > r or tl > tr or l > tr or r < tl) {
            return {0, -1};
        }
        if (l <= tl && r >= tr) {
            return bit[v];
        }
        push(v);
        int tm = (tl + tr) / 2;
        return merge(query(2*v+1, tl, tm, l, r), query(2*v+2,tm+1, tr, l, r));
    }

};

struct pt
{
    int l, r;
};


int32_t main()
{
    SYNC
    int n, m; cin >> n >> m;

    vector<pt> v(m);
    vector<pt> a[n];
    set<int> st;
    for (auto &x : v) {
        int idx;
        cin >> idx >> x.l >> x.r;
        a[idx - 1].pb(x);
        st.insert(x.l);
        st.insert(x.r);
    }

    map<int, int> nv;
    int idx = 0;
    for (auto x : st)
        nv[x] = idx++;

    for (int i = 0; i < n; i++) {
        for (auto &x : a[i]) {
            x.l = nv[x.l];
            x.r = nv[x.r];
        }
    }

    int k = idx; // segtree size
    vector<int> vseg(k, 0);
    seg_tree sg(vseg);

    int ans = n;

    vector<int> par(n, -1);
    int pos = -1;
    for (int i = 0; i < n; i++) {
        int len = 1;
        for (auto &x : a[i]) {
            pair<int, int> qr =  sg.query(0, 0, k - 1, x.l, x.r);
            if (qr.F + 1 > len) {
                len = qr.F + 1;
                par[i] = qr.S;
            }
        }
        if (n - len < ans) {
            ans = n - len;
            pos = i;
        }
        // debug(i + 1, len, par[i]);
        for (auto &x : a[i]) {
            sg.update(0, 0, k - 1, x.l, x.r, len, i);
        }
    }
    vector<int> rem(n, 1);
    while (pos != -1) {
        rem[pos] = 0;
        pos = par[pos];
    }
    cout << ans << '\n';

    for (int i = 0; i < n; i++) {
        if (rem[i])
            cout << i + 1 << ' ';
    }

    return 0;
}
    }

    return 0;
}
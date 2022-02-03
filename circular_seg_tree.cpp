#define _CRT_SECURE_NO_DEPRECATE
#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include "bits/stdc++.h"
using namespace std;
#define int long long
#define SYNC std::ios_base::sync_with_stdio(0); cout.tie(nullptr);
#define FRE freopen("input.txt","r",stdin);freopen("output.txt","w",stdout)

void __print(int x) {cerr << x;}
void __print(int32_t x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}

template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...) 42
#endif

const int MOD = 1e9 + 7;
const int MOD1 = 998244353;
const int N = 2e5 + 5;
const int INF = 2e9;
const long double EPS = 1e-12;
const long double PI = 3.141592653589793116;

struct seg_tree 
{

    vector<pair<int, int>> bit;
    vector<int> a;
    vector<int> lazy;
    int n;
    seg_tree(int n) {
        this-> n = n;
        bit.assign(4*n+5,{0, 0});
        lazy.assign(4*n+5,0);
    }
    seg_tree(vector<int> a) : seg_tree(a.size())
    {
        this-> a = a;
        build(0,0,(int)a.size()-1);
    }
    pair<int, int> merge(pair<int, int> x, pair<int, int> y) {
        // Function to return 
        if (x.first <= y.first) {
            return x;
        } else {
            return y;
        }
    }
    void build(int node, int start, int end)
    {
        if(start == end)
        {
            bit[node] = {a[start], start};
            return;
        }
        int lch = 2*node+1;     //Left Child
        int rch = 2*node+2;     //Right Child
        int mid = (start+end)/2;
        build(lch,start,mid);
        build(rch,mid+1,end);
        bit[node] = merge(bit[lch],bit[rch]);
        return; 
    }
    // Adding on segtree and query for max/min
    void push(int v) {
        bit[v*2+1].first += lazy[v];
        lazy[v*2+1] += lazy[v];
        bit[v*2+2].first += lazy[v];
        lazy[v*2+2] += lazy[v];
        lazy[v] = 0;
    }

    void update(int v, int tl, int tr, int l, int r, int addend) {
        if (l > r) 
            return;
        if (l == tl && tr == r) {
            bit[v].first += addend;
            lazy[v] += addend;
        } else {
            push(v);
            int tm = (tl + tr) / 2;
            update(v*2+1, tl, tm, l, min(r, tm), addend);
            update(v*2+2, tm+1, tr, max(l, tm+1), r, addend);
            bit[v] = merge(bit[v*2+1], bit[v*2+2]);
        }
    }

    pair<int, int> query(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return {INF, INF};
        if (l <= tl && tr <= r)
            return bit[v];
        push(v);
        int tm = (tl + tr) / 2;
        return merge(query(v*2+1, tl, tm, l, min(r, tm)), 
                   query(v*2+2, tm+1, tr, max(l, tm+1), r));
    }

    pair<int, int> circularQuery(int l, int r) {
        l = (l + n) % n;
        r = (r + n) % n;
        if (l <= r) {
            return query(0, 0, n - 1, l, r);
        } else {
            return merge(query(0, 0, n - 1, 0, r), query(0, 0, n - 1, l, n - 1));
        }
    }

    void circularUpdate(int l, int r, int addend) {
        l = (l + n) % n;
        r = (r + n) % n;
        if (l <= r) {
            update(0, 0, n - 1, l, r, addend);
        } else {
            update(0, 0, n - 1, 0, r, addend);
            update(0, 0, n - 1, l, n - 1, addend);
        }
    }

};


void solve_test() {
    int n, k; cin >> n >> k;
    vector<int> a(n), v(n, 0), tmp;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> p(n, -1);
    seg_tree sg(a), sg1(a);
    pair<int, int> qr;
    for (int val = 1; val <= n; val++) {
        // find the zero
        while (true) {
            qr = sg1.circularQuery(0, n - 1);
            if (qr.first != 0)  break;
            sg1.circularUpdate(qr.second, qr.second, INF);
            sg.circularUpdate(qr.second + 1, qr.second + k, 1);
        }
        qr = sg.query(0, 0, n - 1, 0, n - 1);
        if (qr.first > 0) {
            cout << "-1\n";
            return;
        }
        int pos = qr.second;
        p[pos] = val;
        sg1.update(0, 0, n - 1, pos, pos, INF);
        sg.update(0, 0, n - 1, pos, pos, INF);
        sg1.circularUpdate(pos - k, pos - 1, -1);
        sg.circularUpdate(pos - k, pos - 1, -1);
        sg.circularUpdate(pos + 1, pos + k, -1);
    }
    for (auto it : p) {
        cout << it << ' ';
    } cout << '\n';
}

int32_t main() {
    SYNC
    int T; cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        solve_test();
    }
    return 0;
}
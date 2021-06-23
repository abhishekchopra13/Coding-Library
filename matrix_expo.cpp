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
// const int MOD = 1e9+7;
const int MOD = 998244353;
const int N = 2e5+5;
const int INF = 1000111000111000111LL;
const ld EPS = 1e-12;
const ld PI = 3.141592653589793116;

typedef vector< vi > vvi;
int modular_exp(int base, int exp, int mod)
{
    int ans = 1;
    while(exp) {
        if(exp%2)   ans = ans%mod * base%mod;
        base = (base%mod * base%mod)%mod;
        exp >>= 1;
        ans %= mod;
    }
    return ans;
}
int inverse_modulo(int base, int mod)
{
    return modular_exp(base, mod - 2, mod);
}
vvi multiply(vvi a, vvi b, int mod = MOD)
{
    int n = (int)a.size();
    vvi res;
    res.resize(n);
    for(int i = 0; i < n; i++) {   
        res[i].assign(n, 0);
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < n; k++) {
                res[i][j] += a[i][k] * b[k][j];
                res[i][j] %= mod;
            }
        }
    }
    return res;
}

vvi matPow(vvi a, int exp) {
    int n = (int)a.size();
    vvi res;
    res.assign(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        res[i][i] = 1;
    while (exp) {
        if (exp % 2)
            res = multiply(res, a, MOD);
        a = multiply(a, a, MOD);
        exp >>= 1;
    }
    return res;
}

void add(int &a, int b) {
    a += b;
    if (a >= MOD)
        a -= MOD;
}

int H, W; 

bool can(int mask) {
    int pos = 0;
    while (pos < H) {
        if ((((1LL<<pos)&mask) == 0) && (((1LL<<(pos + 1))&mask) or pos + 1 == H)) {
            return false;
        } else if ((((1LL<<pos)&mask) == 0) && (((1LL<<(pos + 1))&mask) == 0)) {
            pos += 2;
            continue;
        }
        pos++;
    }
    return true;
}

int fill_H(int mask) {
    int cnt = 0;
    for (int i = 0; i < (1LL<<H); i++) {
        if (i & mask)   continue;
        if (can(i | mask))
            cnt++;
    }
    return cnt;
}

int ways(int iMask, int fMask) {
    if (iMask&fMask) 
        return 0;
    return fill_H(fMask | iMask);
}

int32_t main()
{
    SYNC
    cin >> H >> W;
    vector<vector<int>> v((1LL<<H), vector<int>(1LL<<H, 0));
    for (int i = 0; i < (1LL<<H); i++) {
        for (int j = 0; j < (1LL<<H); j++) {
            v[i][j] = ways(i, j);
        }
    }
    int exp = W - 1;
    if (exp == 0) {
        int ans = 0;
        for (int i = 0; i < (1LL<<H); i++) {
            if (can(i))
                ans++;
        }
        return cout << ans, 0;
    }
    vvi res = matPow(v, exp);
    int ans = 0;
    for (int i = 0; i < (1LL<<H); i++) {
        add(ans, (res[i][0] * fill_H(i))%MOD);
    }
    cout << ans;
    return 0;
}
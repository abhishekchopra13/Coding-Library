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

const int N = 2e5+5;
const int INF = 1000111000111000111LL;
const ld EPS = 1e-12;
const ld PI = 3.141592653589793116;

const int mod = 7*(1LL<<20) + 1; // Mod for ntt
const int root_pw = 1 << 20; // The size of root_pw should be greater than size of polynomial use bigger root in case
int root, root_1; // The tricky part of NTT calculate these offline on your PC beforehand using generator function
int _inv[mod]; // If mod is small precompute this for faster shit you can comment the inverse and pre_cal function if not required

int inverse(int n, int m = mod) {
    return _inv[n];
}

void pre_cal() {
    _inv[1] = 1;
    for (int i = 2; i < mod; i++) {
        _inv[i] = (mod - (mod/i) * _inv[mod%i] % mod) % mod;
    }
}

int modular_exp(int base,int exp,int mod)
{
    int ans =1;
    while(exp)
    {
        if(exp%2)   ans = ans%mod*base%mod;
        base = (base%mod*base%mod)%mod;
        exp/=2;
        ans%=mod;
    }
    return ans;
}
int inv_mod(int base, int mod)
{
    return modular_exp(base,mod-2,mod);
} 
// This is the coolest function use this to calculate the nth root of unity offline and assign values
// of root and root_1 (root inverse modulo mod)
int generator (int p) {
    for (int i = 2; i < p; i++) {
        if (modular_exp(i, root_pw, mod) == 1) {
            root = i;
            root_1 = inv_mod(i, mod);
            return i;
        }
    }
    return -1;
}
// Lame ntt stuff
void ntt(vector<int> & a, bool invert) {
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        int wlen = invert ? root_1 : root;
        for (int i = len; i < root_pw; i <<= 1)
            wlen = (int)(1LL * wlen * wlen % mod);

        for (int i = 0; i < n; i += len) {
            int w = 1;
            for (int j = 0; j < len / 2; j++) {
                int u = a[i+j], v = (int)(1LL * a[i+j+len/2] * w % mod);
                a[i+j] = u + v < mod ? u + v : u + v - mod;
                a[i+j+len/2] = u - v >= 0 ? u - v : u - v + mod;
                w = (int)(1LL * w * wlen % mod);
            }
        }
    }
    if (invert) {
        int n_1 = inv_mod(n, mod);
        for (int & x : a)
            x = (int)(1LL * x * n_1 % mod);
    }
}
// Multiply two poly get poly
vector<int> multiply(vector<int> const& a, vector<int> const& b) {
    vector<int> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) 
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    ntt(fa, false);
    ntt(fb, false);
    for (int i = 0; i < n; i++) {
        fa[i] *= fb[i];
        fa[i] %= mod;
    }
    ntt(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++)
        result[i] = fa[i] % mod;
    return result;
}
// A polynomial raised to the power exp, set a limit on size of polynomial to stay in bounds
vector<int> power_poly(vector<int> a, int exp, int size_lim = 5e5+1) {
    vector<int> res = {1};
    while (exp) {
        if (exp & 1LL) res = multiply(res, a);
        a = multiply(a, a);
        while ((int)a.size() > size_lim)    a.pop_back();
        while ((int)res.size() > size_lim)  res.pop_back();
        exp >>= 1;
    }
    return res;
}
// Any precomputation use this :p
void precompute_all() {
    pre_cal();
    generator(mod);
    // The following values are set by generator it will take 1 min at max even for modulo of the order 1e9
    root = 5, root_1 = inv_mod(5, mod); // Ran generator offline (*..*)
}

int32_t main()
{
    SYNC
    precompute_all();
    
    return 0;
}
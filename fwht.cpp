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

const int MOD = 30011;
const int MOD1 = 998244353;
const int N = 2e5 + 5;
const int INF = 1000111000111000111LL;
const long double EPS = 1e-12;
const long double PI = 3.141592653589793116;

int modular_exp(int base, int exp, int mod = MOD) 
{
    int ans = 1;
    while (exp) {
        if(exp % 2)   ans = ans % mod * base % mod;
        base = (base % mod * base % mod) % mod;
        exp /= 2; ans %= mod;
    }
    return ans;
}
int inv_mod(int base, int mod = MOD) {
    return modular_exp(base, mod - 2, mod);
}
void add(int &a, int b) {
    a += b;
    if (a >= MOD)
        a -= MOD;
}
void mul(int &a, int b) {
    a *= b;
    a %= MOD;
}

int inv2 = inv_mod(2);
#define M (1 << 16)
#define OR 0
#define AND 1
#define XOR 2
struct FWHT{
  int P1[M], P2[M];
  void wt(int *a, int n, int flag = XOR) {
    if (n == 0) return;
    int m = n / 2;
    wt(a, m, flag); wt(a + m, m, flag);
    for (int i = 0; i < m; i++){
      int x = a[i], y = a[i + m];
      if (flag == OR) a[i] = x, a[i + m] = (x + y) % MOD;
      if (flag == AND) a[i] = (x + y) % MOD, a[i + m] = y;
      if (flag == XOR) a[i] = (x + y) % MOD, a[i + m] = (x - y + MOD) % MOD;
    }
  }
  void iwt(int* a, int n, int flag = XOR) {
    if (n == 0) return;
    int m = n / 2;
    iwt(a, m, flag); iwt(a + m, m, flag);
    for (int i = 0; i < m; i++){
      int x = a[i], y = a[i + m];
      if (flag == OR) a[i] = x, a[i + m] = (y - x + MOD) % MOD;
      if (flag == AND) a[i] = (x - y + MOD) % MOD, a[i + m] = y;
      if (flag == XOR) a[i] = 1LL * (x + y) * inv2 % MOD, a[i + m] = 1LL * (x - y + MOD) * inv2 % MOD; // replace inv2 by >>1 if not required
    }
  }
 vector<int> multiply(int n, vector<int> A, vector<int> B, int flag = XOR) {
    assert(__builtin_popcount(n) == 1);
    A.resize(n); B.resize(n);
    for (int i = 0; i < n; i++) P1[i] = A[i];
    for (int i = 0; i < n; i++) P2[i] = B[i];
    wt(P1, n, flag); wt(P2, n, flag);
    for (int i = 0; i < n; i++) P1[i] = 1LL * P1[i] * P2[i] % MOD;
    iwt(P1, n, flag);
    return vector<int> (P1, P1 + n);
  }
  vector<int> pow(int n, vector<int> A, long long k, int flag = XOR) {
    assert(__builtin_popcount(n) == 1);
    A.resize(n);
    for (int i = 0; i < n; i++) P1[i] = A[i];
    wt(P1, n, flag);
    for(int i = 0; i < n; i++) P1[i] = modular_exp(P1[i], k);
    iwt(P1, n, flag);
    return vector<int> (P1, P1 + n);
  }
};

int32_t main() {
    SYNC
    FWHT t;
    int n, k; cin >> n >> k;
    vector<int> a(k + 1, 1);
    vector<int> res = t.pow(M, a, n, XOR);
    int ans = 0;
    for (int i = 1; i < M; i++) {
        add(ans, res[i]);
    }
    cout << ans;
    return 0;
}
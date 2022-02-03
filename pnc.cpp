const int MOD = 1e9+7;
const int N = 2e5+5;

// Combnitorics Snippet, Call precompute()
int fact[N], ifact[N];
int mod_exp(int base, int exp, int mod = MOD) 
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
    return mod_exp(base, mod - 2, mod);
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

void pre_compute() {
    fact[0] = 1;
    for(int i = 1; i < N; i++) {
        fact[i] = (i * fact[i-1]) % MOD;
    }
    ifact[N - 1] = inv_mod(fact[N - 1], MOD);
    for (int i = N - 2; i >= 0; i--) {
        ifact[i] = ((i + 1) * ifact[i + 1]) % MOD;
    }
}
int nCr(int n, int r) {
    if (r > n or r < 0)
        return 0;
    if(r == n or r == 0)
        return 1;
    return ( (fact[n] % MOD * ifact[r] % MOD) * ifact[n - r] ) % MOD;
}

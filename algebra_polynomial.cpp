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
const int N = 1e5 + 5;
const int INF = 1000111000111000111LL;
const long double EPS = 1e-12;
const long double PI = 3.141592653589793116;

namespace algebra {
    const int maxn = 1 << 21;
    const int magic = 0; // threshold for sizes to run the naive algo
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); 

    template<typename T>
    T bpow(T x, size_t n) {
        return n ? n % 2 ? x * bpow(x, n - 1) : bpow(x * x, n / 2) : T(1);
    }

    template<int m>
    struct modular {
        
        // https://en.wikipedia.org/wiki/Berlekamp-Rabin_algorithm
        // solves x^2 = y (mod m) assuming m is prime in O(log m).
        // returns nullopt if no sol.
        // optional<modular> sqrt() const {
        //     static modular y;
        //     y = *this;
        //     if(r == 0) {
        //         return 0;
        //     } else if(bpow(y, (m - 1) / 2) != modular(1)) {
        //         return nullopt;
        //     } else {
        //         while(true) {
        //             modular z = rng();
        //             if(z * z == *this) {
        //                 return z;
        //             }
        //             struct lin {
        //                 modular a, b;
        //                 lin(modular a, modular b): a(a), b(b) {}
        //                 lin(modular a): a(a), b(0) {}
        //                 lin operator * (const lin& t) {
        //                     return {
        //                         a * t.a + b * t.b * y,
        //                         a * t.b + b * t.a
        //                     };
        //                 }
        //             } x(z, 1); // z + x
        //             x = bpow(x, (m - 1) / 2);
        //             if(x.b != modular(0)) {
        //                 return x.b.inv();
        //             }
        //         }
        //     }
        // }
        
        int64_t r;
        modular() : r(0) {}
        modular(int64_t rr) : r(rr) {if(abs(r) >= m) r %= m; if(r < 0) r += m;}
        modular inv() const {return bpow(*this, m - 2);}
        modular operator - () const {return r ? m - r : 0;}
        modular operator * (const modular &t) const {return r * t.r % m;}
        modular operator / (const modular &t) const {return *this * t.inv();}
        modular operator += (const modular &t) {r += t.r; if(r >= m) r -= m; return *this;}
        modular operator -= (const modular &t) {r -= t.r; if(r < 0) r += m; return *this;}
        modular operator + (const modular &t) const {return modular(*this) += t;}
        modular operator - (const modular &t) const {return modular(*this) -= t;}
        modular operator *= (const modular &t) {return *this = *this * t;}
        modular operator /= (const modular &t) {return *this = *this / t;}
        
        bool operator == (const modular &t) const {return r == t.r;}
        bool operator != (const modular &t) const {return r != t.r;}
        
        operator int() const {return r;}
        int64_t rem() const {return 2 * r > m ? r - m : r;}
    };
    
    template<int T>
    istream& operator >> (istream &in, modular<T> &x) {
        return in >> x.r;
    }
    
    template<typename T>
    T fact(int n) {
        static T F[maxn];
        return F[n] ? F[n] : F[n] = n ? fact<T>(n - 1) * T(n) : T(1);
    }
    
    template<typename T>
    T rfact(int n) {
        static T RF[maxn];
        return RF[n] ? RF[n] : RF[n] = T(1) / fact<T>(n);
    }

    namespace fft {
        typedef double ftype;
        typedef complex<ftype> point;

        point w[maxn];
        const ftype pi = acos(-1);
        bool initiated = 0;
        void init() {
            if(!initiated) {
                for(int i = 1; i < maxn; i *= 2) {
                    for(int j = 0; j < i; j++) {
                        w[i + j] = polar(ftype(1), pi * j / i);
                    }
                }
                initiated = 1;
            }
        }
        
        void fft(auto *in, point *out, int n, int k = 1) {
            if(n == 1) {
                *out = *in;
            } else {
                n /= 2;
                fft(in, out, n, 2 * k);
                fft(in + k, out + n, n, 2 * k);
                for(int i = 0; i < n; i++) {
                    auto t = out[i + n] * w[i + n];
                    out[i + n] = out[i] - t;
                    out[i] += t;
                }
            }
        }
        
        void mul_slow(vector<auto> &a, const vector<auto> &b) {
            if(a.empty() || b.empty()) {
                a.clear();
            } else {
                a.resize(a.size() + b.size() - 1);
                for(int k = a.size() - 1; k >= 0; k--) {
                    a[k] *= b[0];
                    for(int j = 1; j < min(k + 1, (int)b.size()); j++) {
                        a[k] += a[k - j] * b[j];
                    }
                }
            }
        }
        
        template<typename T>
        void mul(vector<T> &a, vector<T> b) {
            if(min(a.size(), b.size()) < magic) {
                mul_slow(a, b);
                return;
            }
            init();
            static const T split = 1 << 15;
            size_t n = a.size() + b.size() - 1;
            while(__builtin_popcount(n) != 1) {
                n++;
            }
            a.resize(n);
            b.resize(n);
            static point A[maxn], B[maxn];
            static point C[maxn], D[maxn];
            for(size_t i = 0; i < n; i++) {
                A[i] = point(a[i].rem() % split, a[i].rem() / split);
                B[i] = point(b[i].rem() % split, b[i].rem() / split);
            }
            fft(A, C, n); fft(B, D, n);
            for(size_t i = 0; i < n; i++) {
                A[i] = C[i] * (D[i] + conj(D[(n - i) % n]));
                B[i] = C[i] * (D[i] - conj(D[(n - i) % n]));
            }
            fft(A, C, n); fft(B, D, n);
            reverse(C + 1, C + n);
            reverse(D + 1, D + n);
            int t = 2 * n;
            for(size_t i = 0; i < n; i++) {
                T A0 = llround(real(C[i]) / t);
                T A1 = llround(imag(C[i]) / t + imag(D[i]) / t);
                T A2 = llround(real(D[i]) / t);
                a[i] = A0 + A1 * split - A2 * split * split;
            }
        }
    }

    template<typename T>
    struct poly {
        vector<T> a;
        
        void normalize() { // get rid of leading zeroes
            while(!a.empty() && a.back() == T(0)) {
                a.pop_back();
            }
        }
        
        poly(){}
        poly(T a0) : a{a0}{normalize();}
        poly(const vector<T> &t) : a(t){normalize();}
        
        poly operator -() const {
            auto t = *this;
            for(auto &it: t.a) {
                it = -it;
            }
            return t;
        }
        
        poly operator += (const poly &t) {
            a.resize(max(a.size(), t.a.size()));
            for(size_t i = 0; i < t.a.size(); i++) {
                a[i] += t.a[i];
            }
            normalize();
            return *this;
        }
        
        poly operator -= (const poly &t) {
            a.resize(max(a.size(), t.a.size()));
            for(size_t i = 0; i < t.a.size(); i++) {
                a[i] -= t.a[i];
            }
            normalize();
            return *this;
        }
        poly operator + (const poly &t) const {return poly(*this) += t;}
        poly operator - (const poly &t) const {return poly(*this) -= t;}
        
        poly mod_xk(size_t k) const { // get first k coefficients
            return vector<T>(begin(a), begin(a) + min(k, a.size()));
        }
        
        poly mul_xk(size_t k) const { // multiply by x^k
            auto res = a;
            res.insert(begin(res), k, 0);
            return res;
        }
        
        poly div_xk(size_t k) const { // drop first k coefficients
            return vector<T>(begin(a) + min(k, a.size()), end(a));
        }
        
        poly substr(size_t l, size_t r) const { // return mod_xk(r).div_xk(l)
            return vector<T>(
                begin(a) + min(l, a.size()),
                begin(a) + min(r, a.size())
            );
        }
        
        poly inv(size_t n) const { // get inverse series mod x^n
            assert((*this)[0] != T(0));
            poly ans = T(1) / a[0];
            size_t a = 1;
            while(a < n) {
                poly C = (ans * mod_xk(2 * a)).substr(a, 2 * a);
                ans -= (ans * C).mod_xk(a).mul_xk(a);
                a *= 2;
            }
            return ans.mod_xk(n);
        }
        
        poly operator *= (const poly &t) {fft::mul(a, t.a); normalize(); return *this;}
        poly operator * (const poly &t) const {return poly(*this) *= t;}
        
        poly reverse(size_t n) const { // computes x^n A(x^{-1})
            auto res = a;
            res.resize(max(n, res.size()));
            return vector<T>(res.rbegin(), res.rbegin() + n);
        }
        
        poly reverse() const {
            return reverse(deg() + 1);
        }
        
        pair<poly, poly> divmod_slow(const poly &b) const { // when divisor or quotient is small
            vector<T> A(a);
            vector<T> res;
            while(A.size() >= b.a.size()) {
                res.push_back(A.back() / b.a.back());
                if(res.back() != T(0)) {
                    for(size_t i = 0; i < b.a.size(); i++) {
                        A[A.size() - i - 1] -= res.back() * b.a[b.a.size() - i - 1];
                    }
                }
                A.pop_back();
            }
            std::reverse(begin(res), end(res));
            return {res, A};
        }
        
        pair<poly, poly> divmod(const poly &b) const { // returns quotiend and remainder of a mod b
            assert(!b.is_zero());
            if(deg() < b.deg()) {
                return {poly{0}, *this};
            }
            int d = deg() - b.deg();
            if(min(d, b.deg()) < magic) {
                return divmod_slow(b);
            }
            poly D = (reverse().mod_xk(d + 1) * b.reverse().inv(d + 1)).mod_xk(d + 1).reverse(d + 1);
            return {D, *this - D * b};
        }
        
        poly operator / (const poly &t) const {return divmod(t).first;}
        poly operator % (const poly &t) const {return divmod(t).second;}
        poly operator /= (const poly &t) {return *this = divmod(t).first;}
        poly operator %= (const poly &t) {return *this = divmod(t).second;}
        poly operator *= (const T &x) {
            for(auto &it: a) {
                it *= x;
            }
            normalize();
            return *this;
        }
        poly operator /= (const T &x) {
            for(auto &it: a) {
                it /= x;
            }
            normalize();
            return *this;
        }
        poly operator * (const T &x) const {return poly(*this) *= x;}
        poly operator / (const T &x) const {return poly(*this) /= x;}
        
        poly conj() const { // A(x) -> A(-x)
            auto res = *this;
            for(int i = 1; i <= deg(); i += 2) {
                res[i] = -res[i];
            }
            return res;
        }
        
        void print(int n) const {
            for(int i = 0; i < n; i++) {
                cout << (*this)[i] << ' ';
            }
            cout << "\n";
        }
        
        void print() const {
            print(deg() + 1);
        }
        
        T eval(T x) const { // evaluates in single point x
            T res(0);
            for(int i = deg(); i >= 0; i--) {
                res *= x;
                res += a[i];
            }
            return res;
        }
        
        T lead() const { // leading coefficient
            assert(!is_zero());
            return a.back();
        }
        
        int deg() const { // degree, -1 for P(x) = 0
            return (int)a.size() - 1;
        }
        
        bool is_zero() const {
            return a.empty();
        }
        
        T operator [](int idx) const {
            return idx < 0 || idx > deg() ? T(0) : a[idx];
        }
        
        T& coef(size_t idx) { // mutable reference at coefficient
            return a[idx];
        }
        
        bool operator == (const poly &t) const {return a == t.a;}
        bool operator != (const poly &t) const {return a != t.a;}
        
        poly deriv() { // calculate derivative
            vector<T> res(deg());
            for(int i = 1; i <= deg(); i++) {
                res[i - 1] = T(i) * a[i];
            }
            return res;
        }
        
        poly integr() { // calculate integral with C = 0
            vector<T> res(deg() + 2);
            for(int i = 0; i <= deg(); i++) {
                res[i + 1] = a[i] / T(i + 1);
            }
            return res;
        }
        
        size_t trailing_xk() const { // Let p(x) = x^k * t(x), return k
            if(is_zero()) {
                return -1;
            }
            int res = 0;
            while(a[res] == T(0)) {
                res++;
            }
            return res;
        }
        
        poly log(size_t n) { // calculate log p(x) mod x^n
            assert(a[0] == T(1));
            return (deriv().mod_xk(n) * inv(n)).integr().mod_xk(n);
        }
        
        poly exp(size_t n) { // calculate exp p(x) mod x^n
            if(is_zero()) {
                return T(1);
            }
            assert(a[0] == T(0));
            poly ans = T(1);
            size_t a = 1;
            while(a < n) {
                poly C = ans.log(2 * a).div_xk(a) - substr(a, 2 * a);
                ans -= (ans * C).mod_xk(a).mul_xk(a);
                a *= 2;
            }
            return ans.mod_xk(n);
        }
        
        poly pow_slow(int64_t k, size_t n) { // if k is small
            return k ? k % 2 ? (*this * pow_slow(k - 1, n)).mod_xk(n) : (*this * *this).mod_xk(n).pow_slow(k / 2, n) : T(1);
        }
        
        poly pow(int64_t k, size_t n) { // calculate p^k(n) mod x^n
            if(is_zero()) {
                return *this;
            }
            if(k < magic) {
                return pow_slow(k, n);
            }
            int i = trailing_xk();
            if(i > 0) {
                return i * k >= n ? poly(0) : div_xk(i).pow(k, n - i * k).mul_xk(i * k);
            }
            T j = a[i];
            poly t = *this / j;
            return bpow(j, k) * (t.log(n) * T(k)).exp(n).mod_xk(n);
        }
        
        // returns nullopt if undefined
        // optional<poly> sqrt(size_t n) const {
        //     if(is_zero()) {
        //         return *this;
        //     }
        //     int i = trailing_xk();
        //     if(i % 2) {
        //         return nullopt;
        //     } else if(i > 0) {
        //         auto ans = div_xk(i).sqrt(n - i / 2);
        //         return ans ? ans->mul_xk(i / 2) : ans;
        //     }
        //     auto st = (*this)[0].sqrt();
        //     if(st) {
        //         poly ans = *st;
        //         size_t a = 1;
        //         while(a < n) {
        //             a *= 2;
        //             ans -= (ans - mod_xk(a) * ans.inv(a)).mod_xk(a) / 2;
        //         }
        //         return ans.mod_xk(n);
        //     }
        //     return nullopt;
        // }
        
        poly mulx(T a) { // component-wise multiplication with a^k
            T cur = 1;
            poly res(*this);
            for(int i = 0; i <= deg(); i++) {
                res.coef(i) *= cur;
                cur *= a;
            }
            return res;
        }
        
        poly mulx_sq(T a) { // component-wise multiplication with a^{k^2}
            T cur = a;
            T total = 1;
            T aa = a * a;
            poly res(*this);
            for(int i = 0; i <= deg(); i++) {
                res.coef(i) *= total;
                total *= cur;
                cur *= aa;
            }
            return res;
        }
        
        vector<T> chirpz_even(T z, int n) { // P(1), P(z^2), P(z^4), ..., P(z^2(n-1))
            int m = deg();
            if(is_zero()) {
                return vector<T>(n, 0);
            }
            vector<T> vv(m + n);
            T zi = T(1) / z;
            T zz = zi * zi;
            T cur = zi;
            T total = 1;
            for(int i = 0; i <= max(n - 1, m); i++) {
                if(i <= m) {vv[m - i] = total;}
                if(i < n) {vv[m + i] = total;}
                total *= cur;
                cur *= zz;
            }
            poly w = (mulx_sq(z) * vv).substr(m, m + n).mulx_sq(z);
            vector<T> res(n);
            for(int i = 0; i < n; i++) {
                res[i] = w[i];
            }
            return res;
        }
        
        vector<T> chirpz(T z, int n) { // P(1), P(z), P(z^2), ..., P(z^(n-1))
            auto even = chirpz_even(z, (n + 1) / 2);
            auto odd = mulx(z).chirpz_even(z, n / 2);
            vector<T> ans(n);
            for(int i = 0; i < n / 2; i++) {
                ans[2 * i] = even[i];
                ans[2 * i + 1] = odd[i];
            }
            if(n % 2 == 1) {
                ans[n - 1] = even.back();
            }
            return ans;
        }
        
        vector<T> eval(vector<poly> &tree, int v, auto l, auto r) { // auxiliary evaluation function
            if(r - l == 1) {
                return {eval(*l)};
            } else {
                auto m = l + (r - l) / 2;
                auto A = (*this % tree[2 * v]).eval(tree, 2 * v, l, m);
                auto B = (*this % tree[2 * v + 1]).eval(tree, 2 * v + 1, m, r);
                A.insert(end(A), begin(B), end(B));
                return A;
            }
        }
        
        vector<T> eval(vector<T> x) { // evaluate polynomial in (x1, ..., xn)
            int n = x.size();
            if(is_zero()) {
                return vector<T>(n, T(0));
            }
            vector<poly> tree(4 * n);
            build(tree, 1, begin(x), end(x));
            return eval(tree, 1, begin(x), end(x));
        }
        
        poly inter(vector<poly> &tree, int v, auto l, auto r, auto ly, auto ry) { // auxiliary interpolation function
            if(r - l == 1) {
                return {*ly / a[0]};
            } else {
                auto m = l + (r - l) / 2;
                auto my = ly + (ry - ly) / 2;
                auto A = (*this % tree[2 * v]).inter(tree, 2 * v, l, m, ly, my);
                auto B = (*this % tree[2 * v + 1]).inter(tree, 2 * v + 1, m, r, my, ry);
                return A * tree[2 * v + 1] + B * tree[2 * v];
            }
        }
        
        static auto resultant(poly a, poly b) { // computes resultant of a and b
            if(b.is_zero()) {
                return 0;
            } else if(b.deg() == 0) {
                return bpow(b.lead(), a.deg());
            } else {
                int pw = a.deg();
                a %= b;
                pw -= a.deg();
                auto mul = bpow(b.lead(), pw) * T((b.deg() & a.deg() & 1) ? -1 : 1);
                auto ans = resultant(b, a);
                return ans * mul;
            }
        }
        
        static poly kmul(auto L, auto R) { // computes (x-a1)(x-a2)...(x-an) without building tree
            if(R - L == 1) {
                return vector<T>{-*L, 1};
            } else {
                auto M = L + (R - L) / 2;
                return kmul(L, M) * kmul(M, R);
            }
        }
        
        static poly build(vector<poly> &res, int v, auto L, auto R) { // builds evaluation tree for (x-a1)(x-a2)...(x-an)
            if(R - L == 1) {
                return res[v] = vector<T>{-*L, 1};
            } else {
                auto M = L + (R - L) / 2;
                return res[v] = build(res, 2 * v, L, M) * build(res, 2 * v + 1, M, R);
            }
        }
        
        static auto inter(vector<T> x, vector<T> y) { // interpolates minimum polynomial from (xi, yi) pairs
            int n = x.size();
            vector<poly> tree(4 * n);
            return build(tree, 1, begin(x), end(x)).deriv().inter(tree, 1, begin(x), end(x), begin(y), end(y));
        }
        
        
        static poly xk(size_t n) { // P(x) = x^n
            return poly(T(1)).mul_xk(n);
        }
        
        static poly ones(size_t n) { // P(x) = 1 + x + ... + x^{n-1} 
            return vector<T>(n, 1);
        }
        
        static poly expx(size_t n) { // P(x) = e^x (mod x^n)
            return ones(n).to_ogf();
        }
        
        // [x^k] (a corr b) = sum_{i+j=k} ai*b{m-j} 
        //                  = sum_{i-j=k-m} ai*bj
        static poly corr(poly a, poly b) { // cross-correlation
            return a * b.reverse();
        }
        
        poly to_egf() const { // ak *= k!
            auto res = *this;
            for(int i = 0; i <= deg(); i++) {
                res.coef(i) *= fact<T>(i);
            }
            return res;
        }
        
        poly to_ogf() const { // ak /= k!
            auto res = *this;
            for(int i = 0; i <= deg(); i++) {
                res.coef(i) *= rfact<T>(i);
            }
            return res;
        }
        
        poly shift(T a) const { // P(x + a)
            return (to_egf().reverse() * expx(deg() + 1).mulx(a)).mod_xk(deg() + 1) .reverse().to_ogf();
        }
    };
    
    static auto operator * (const auto& a, const poly<auto>& b) {
        return b * a;
    }
};

using namespace algebra;

const int mod = 663224321;
typedef modular<mod> base;
typedef poly<base> polyn;

int32_t main() {
    SYNC
    vector<modular<mod>> a(N, 1);
    for (int i = 1; i < N; i++) {
        a[i] = bpow(modular<mod>(i), i - 1);
    }
    poly<base> ans = (poly<base>(1) - (poly<base>({0, 1}) * poly<base>(a)));
    ans = ans.inv(N);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        cout << ans[n] << '\n';
    }
    return 0;
}
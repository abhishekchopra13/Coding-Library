#include "bits/stdc++.h"
using namespace std;
#define int long long
#define SYNC std::ios_base::sync_with_stdio(0);cin.tie(nullptr);cout.tie(nullptr);
#define FRE freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
typedef long double ld;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
typedef vector<int> vi;
typedef vector<ii>   vii;

#define rep(i,l,r)   for (int i = (l); i < (r); i++)
#define here cout << " Hey!!\n";
#define  pb push_back
#define  F  first
#define  S  second
#define all(v) (v).begin(),(v).end()
#define sz(a) (int)((a).size())
#define sq(x) ((x)*(x))

const int N = 1e5+5;
int n, k;
int v[N];

struct node
{   
    int freq;
    node* nxt[2];
    node()
    {
        nxt[0] = nxt[1] = nullptr;
        freq = 0;
    }
};
node* root;

void insert(int x) {
    node* cur = root;
    for (int i = 30; i >= 0; i--) {
        cur->freq = cur->freq + 1;
        int now = (x >> i)&1;
        if (cur->nxt[now] == nullptr) {
            cur->nxt[now] = new node;
        }
        cur = cur->nxt[now];
    }
    cur->freq++;
}

void del(int x) {
    node* cur = root;
    for (int i = 30; i >= 0; i--) {
        cur->freq = cur->freq - 1;
        int now = (x >> i)&1;
        if (cur->nxt[now] == nullptr) {
            cur->nxt[now] = new node;
        }
        cur = cur->nxt[now];
    }
    if (cur->freq)
        cur->freq--;
} 

int get_cnt(int val) {
    node* cur = root;
    long long res = 0;
    for (int i = 0; i < n; i++) {
        cur = root;
        for (int j = 30; j >= 0; j--) {
            if (cur == nullptr or cur->freq == 0)    break;
            int b_now = ((v[i]>>j)&1), val_now = ((val>>j)&1);
            if (cur->nxt[b_now] != nullptr && val_now) {
                res += (cur->nxt[b_now])->freq;
            }
            cur = cur->nxt[b_now ^ val_now];
        }
    }
    return (res - n) / 2;
}

void solve() {
    cin >> n >> k;
    rep(i,0,n) {
        cin >> v[i];
        insert(v[i]);
    } 
    int lo = 0, hi = (1LL<<31) - 1;
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (get_cnt(mid) < k)
            lo = mid;
        else
            hi = mid - 1;
    }
    cout << lo << '\n';
    rep(i,0,n)
        del(v[i]);
}

int32_t main()
{
    SYNC
    root = new node;
    int T; cin >> T;
    while(T--) {
        solve();
    }
    return 0;
}
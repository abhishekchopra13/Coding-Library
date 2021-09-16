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

struct trie {
    trie* fail = 0;
    trie* next[26] = {};
    bool last = 0;
    vector<int> id;
    char ch;
};

trie* root = new trie;

int insert(string str, int ind) {
    trie* curr = root;
    for (auto ch : str) {
        int c = ch - 'a';
        if(!curr->next[c])
            curr->next[c] = new trie;
        curr = curr->next[c];
        curr->ch = ch;
    }
    if (!curr->last)
        curr->id.push_back(ind);
    curr->last = 1;
    return curr->id[0];
}

trie* go(trie* curr, char ch) {
    int c = ch - 'a';
    while(curr && !curr->next[c]) {
        curr = curr->fail;
    }
    if(curr)
        return curr->next[c];
    return root;
}

void push_links() {
    queue<trie*> Q;

    for(int i = 0; i < 26; i++) {
        if(root->next[i]) {
            Q.push(root->next[i]);
            root->next[i]->fail = root;
        }
    }
    while(Q.size()) {
        trie* u = Q.front();
        Q.pop();
        for(int i = 0; i < 26; i++) {
            if(u->next[i]) {
                trie* v = u->next[i];
                v->fail = go(u->fail,'a' + i);
                Q.push(v);
                for(int ind : v->fail->id) {
                    v->id.push_back(ind);
                }
            }
        }
    }
}

int32_t main()
{
    // Link: https://cses.fi/problemset/task/2102/
    SYNC
    string s; cin >> s;
    int Q; cin >> Q;
    vector<int> ans(Q, 0), pos(Q);
    vector<string> pat(Q);
    for (int i = 0; i < Q; i++) {
        cin >> pat[i];
        pos[i] = insert(pat[i], i);
    }
    push_links();
    trie* cur = root;
    for (auto ch : s) {
        cur = go(cur, ch);
        for (int pos_ans : cur->id) {
            ans[pos_ans] = 1;
        }
    }
    for (int i = 0; i < Q; i++) {
        if (ans[pos[i]]) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}

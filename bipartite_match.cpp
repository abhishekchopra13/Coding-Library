struct bipartite_match{
    vector<vector<int>> G;
    vector<int> L, R, Viz;
    void init(int n, int m)
    {
        G.clear(), L.clear(), R.clear(), Viz.clear();
        G.resize(n), L.resize(n, -1), R.resize(m, -1), Viz.resize(n, 0);
    }
    void add_edge(int a, int b){ G[a].push_back(b); }
    bool match(int node)
    {
        if(Viz[node]) return 0;
        Viz[node] = 1;
        for(auto vec : G[node]){
            if(R[vec] == -1 || match(R[vec])) {
                L[node] = vec;
                R[vec] = node;
                return 1;
            }
        }
        return 0;
    }
    int Solve()
    {
        bool ok = 1;
        while(ok)
        {
            ok = 0;
            fill(Viz.begin(), Viz.end(), 0);
            for(int i = 0; i < L.size(); i++)
                if(L[i] == -1)
                    ok |= match(i);
        }
        int ret = 0;
        for(int i = 0; i < L.size(); i++)
            ret += (L[i] != -1);
        return ret;
    }
};